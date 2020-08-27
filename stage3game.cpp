#include <QTimer>

#include "stage3game.h"
#include "stage3player.h"
#include "stage3background.h"
#include "emptyentity.h"
#include "obstaclevelocityupdatevisitor.h"
#include "config.h"
#include "stage3pausedialog.h"

Stage3Game::Stage3Game(std::shared_ptr<Stage3Player> player,
                       std::shared_ptr<Background> background,
                       std::shared_ptr<Entity> obstacleRoot,
                       std::shared_ptr<PowerUpFactory> powerUpFacotry,
                       int maxStage, std::shared_ptr<GameObserver> gameObserver,
                       std::shared_ptr<CurrencyFactory> currencyFactory):
    GameDialog(), memento(new StageMemento()), gameOver(false), resultScreen(false),
    player(player), background(background), obstacleRoot(obstacleRoot), currencyFactory(currencyFactory),
    powerUpFactory(powerUpFacotry), score(0), gameObserver(gameObserver),
    maxStage(maxStage), currentStage(1), stageCleared(false), timeBonus(2000.0) {
    this->setFixedSize(Config::config()->getWorldWidth(), Config::config()->getWorldHeight());

    if (Config::config()->getBackgroundNumber() == 2) {
        this->setStyleSheet("background-color: #002855;"); //Dark Blue
    } else {
        this->setStyleSheet("background-color: #14ACF6;"); //Light Blue
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(32);

    memento->storePlayer(player->makeMemento());
    memento->storeBackground(background->makeMemento());
    nextStage();
}

Stage3Game::~Stage3Game() {
    delete timer;
}

void Stage3Game::pause() {
    paused = true;
    timer->stop();
}

void Stage3Game::unpause() {
    paused = false;
    timer->start();
}

//proceed to next stage by restriving the current stage parent,
//reset background and stickman positions
//generate new set of curerncy items and power ups
void Stage3Game::nextStage() {
    player->setReachedGoal(false);
    if (currentStage > 1) {
        score += 200 * (currentObstacles->getChildren().size() - 1);
    }
    std::vector<Entity*> stages = obstacleRoot->getChildren();
    for (auto it = stages.begin(); it != stages.end(); ++it) {
        if ((*it)->getName().compare(std::to_string(currentStage)) == 0) {
            currentObstacles.reset((*it));
            break;
        }
    }
    timeBonus = 2000;
    powerUpFactory->generatePowerUps(currentObstacles->getChildren());
    memento->storePowerUps(powerUpFactory->getPowerUpLocations());
    memento->storeObstalces(currentObstacles->getChildren());
    if (currencyFactory != nullptr) {
        currencyFactory->generateCurrency(currentObstacles->getChildren());
        memento->storeCurrency(currencyFactory->getCurrencyLocations());
    }
    player->restoreState(memento->getStoredPlayer());
    background->restoreState(memento->getStoredBackground());
}

void Stage3Game::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    if (resultScreen) {
        renderFinalScreen(painter);
        return;
    }
    std::vector<PowerUp *> powerUps = powerUpFactory->createPowerUps();
    std::vector<Currency *> currency;
    if (currencyFactory != nullptr) {
        currency = currencyFactory->createCurrency();
    }

    //if not on stge transition or game over screen
    if (!stageCleared && !gameOver) {
        background->render(painter, paused);
        //render, update & check for collisions with powerups
        for (unsigned int i = 0; i < powerUps.size(); i++) {
            powerUps.at(i)->render(painter);
            powerUps.at(i)->update(paused, 32);
            if (powerUps.at(i)->checkXOverlapCollision(player) && powerUps.at(i)->checkYOverlapCollision(player)) {
                //only collide with powerups that still exist (haven't been picked up yet)
                if (powerUpFactory->getStatus(i)) {
                    powerUps.at(i)->applyPowerUpEffect(player);
                    powerUpFactory->setStatus(i, false);
                    score += powerUps.at(i)->getScoreWorth();
                    gameObserver->incrementPowerUpCounter();
                }
            }
        }
        //render, update & check for collision with currency items
        if (currencyFactory != nullptr) {
            for (unsigned int i = 0; i < currency.size(); i++) {
                currency.at(i)->render(painter);
                currency.at(i)->update(paused, 32);
                if (currency.at(i)->checkXOverlapCollision(player) && currency.at(i)->checkYOverlapCollision(player)) {
                    //same logic as with power ups
                    if (currencyFactory->getStatus(i)) {
                        currency.at(i)->applyPowerUpEffect(player);
                        currencyFactory->setStatus(i, false);
                        score += currency.at(i)->getScoreWorth();
                        gameObserver->incrementCurrencyCounter();
                    }
                }
            }
        }
        currentObstacles->render(painter);
        player->render(painter);
        player->update(paused, 32, currentObstacles->getChildren());
        renderScore(painter);
        //if collision occurred trigger restore on player, background, powerup, currency items and obstacles
        if (player->getResetStage() && player->getLives() > 0) {
            background->restoreState(memento->getStoredBackground());
            player->restoreState(memento->getStoredPlayer());
            currentObstacles->restoreChildrenState(memento->getStoredObstaclesCoordintes());
            powerUpFactory->restoreState(memento->getStoredPowerUpCoordinates());
            if (currencyFactory != nullptr) {
                currencyFactory->restoreState(memento->getStoredCurrencyCoordinate());
            }
            score -= 100;
            player->setResetStage(false);
        }
        currentObstacles->update(paused, 32);
        //check if gameover
        if (player->getLives() == 0) {
            gameOver = true;
        }
        //check if reahed goal
        if (player->getReachedGoal()) {
            stageCleared = true;
        }
        //lower time bonus the more time spent in the stage
        if (!paused) {
            timeBonus -= (10/32);
        }
    }

    else if (stageCleared && !gameOver) {
        background->render(painter, true);
        currentObstacles->render(painter);
        for (auto it = powerUps.begin(); it != powerUps.end(); ++it) {
            (*it)->render(painter);
        }
        if (currencyFactory != nullptr) {
            for (auto it = currency.begin(); it != currency.end(); ++ it) {
                (*it)->render(painter);
            }
        }
        player->render(painter);
        renderScore(painter);

        painter.setOpacity(0.5);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);
        painter.drawRect(0, 0, Config::config()->getWorldWidth(), Config::config()->getWorldHeight());

        QFont font = painter.font();
        font.setPointSize(30);
        painter.setFont(font);
        painter.setOpacity(1.0);
        painter.setPen(Qt::white);

        //generate game clear screen
        if (currentStage == maxStage && !gameOver) {
            QString text1("Congratulations!");
            QString text2("You have finished all the stages!");
            QString text3("Press 'N' to enter result screen.");

            painter.drawText(Config::config()->getWorldWidth() * 0.3, Config::config()->getWorldHeight() * 0.3, text1);
            painter.drawText(Config::config()->getWorldWidth() * 0.1, Config::config()->getWorldHeight() * 0.5, text2);
            painter.drawText(Config::config()->getWorldWidth() * 0.1, Config::config()->getWorldHeight() * 0.7, text3);
        }

        //generate stage clear screen
        else if (currentStage < maxStage && !gameOver) {
            QString text1("Congratulations!");
            QString text2("You have cleared Stage ");
            text2.append(QString::number(currentStage));
            text2.append("!");
            QString text3("Press 'N' to start the next stage.");

            painter.drawText(Config::config()->getWorldWidth() * 0.3, Config::config()->getWorldHeight() * 0.3, text1);
            painter.drawText(Config::config()->getWorldWidth() * 0.15, Config::config()->getWorldHeight() * 0.5, text2);
            painter.drawText(Config::config()->getWorldWidth() * 0.1, Config::config()->getWorldHeight() * 0.7, text3);

        }
    }
    //generate game over screen
    else if (gameOver) {
        background->render(painter, true);
        player->render(painter);
        currentObstacles->render(painter);
        renderScore(painter);
        for (auto it = powerUps.begin(); it != powerUps.end(); ++it) {
            (*it)->render(painter);
        }
        if (currencyFactory != nullptr) {
            for (auto it = currency.begin(); it != currency.end(); ++ it) {
                (*it)->render(painter);
            }
        }
        painter.setOpacity(0.5);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);
        painter.drawRect(0, 0, Config::config()->getWorldWidth(), Config::config()->getWorldHeight());

        painter.setOpacity(1.0);
        QFont font = painter.font();
        font.setPointSize(24);
        painter.setFont(font);

        painter.setPen(Qt::red);
        painter.drawText(Config::config()->getWorldWidth() * 0.4, Config::config()->getWorldHeight() * 0.4, QString("YOU DIED"));
        painter.setPen(Qt::white);
        painter.drawText(Config::config()->getWorldWidth() * 0.3, Config::config()->getWorldHeight() * 0.6, QString("Press 'Q' to Quit."));
    }
}

void Stage3Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_P) {
        if (!stageCleared && !gameOver) {
            //create and open pause dialog when paused
            if (!paused) {
                pause();
                Stage3PauseDialog *pause_dialog = new Stage3PauseDialog(player, this, gameObserver);
                pause_dialog->exec();
            }
        }
    }

    if (event->key() == Qt::Key_Space) {
        if (!stageCleared && !gameOver) {
            //initiate jump
            player->jump();
        }
    }

    if (event->key() == Qt::Key_Q) {
        //quit game
        this->close();
    }

    if (event->key() == Qt::Key_N) {
        if (stageCleared && !gameOver) {
            //calculate final score and enter result screen if game finished
            if (currentStage == maxStage && !resultScreen) {
                score += (currentObstacles->getChildren().size() - 1) * 200 + timeBonus;
                resultScreen = true;
            }
            //proceed to next stage
            else if (currentStage < maxStage) {
                currentStage++;
                if (timeBonus > 0) {
                    score += timeBonus;
                }
                nextStage();
                stageCleared = false;
            }
            //close game if result screen already shown
            else if (resultScreen) {
                this->close();
            }
        }
    }

    //stickman moves RIGHT, all world objects move LEFT
    if (event->key() == Qt::Key_Right) {
        if (!paused && !gameOver) {
            player->changeXVelocity(Config::config()->getStickman()->getMovementVelocity());
            background->setBackgroundVelocity(-Config::config()->getStickman()->getMovementVelocity());
            currentObstacles->accept(new ObstacleVelocityUpdateVisitor(), -Config::config()->getStickman()->getMovementVelocity());
            powerUpFactory->setVelocity(-Config::config()->getStickman()->getMovementVelocity());
            if (currencyFactory != nullptr) {
                currencyFactory->setVelocity(-Config::config()->getStickman()->getMovementVelocity());
            }
        }
    }

    //stickman moves LEFT, all world objects move RIGHT
    if (event->key() == Qt::Key_Left) {
        if (!paused && !gameOver) {
            player->changeXVelocity(-Config::config()->getStickman()->getMovementVelocity());
            background->setBackgroundVelocity(Config::config()->getStickman()->getMovementVelocity());
            currentObstacles->accept(new ObstacleVelocityUpdateVisitor(), Config::config()->getStickman()->getMovementVelocity());
            powerUpFactory->setVelocity(Config::config()->getStickman()->getMovementVelocity());
            if (currencyFactory != nullptr) {
                currencyFactory->setVelocity(Config::config()->getStickman()->getMovementVelocity());
            }
        }
    }
}

void Stage3Game::keyReleaseEvent(QKeyEvent *event) {
    //if left or right released, no longer moving
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left) {
        player->changeXVelocity(0);
        background->setBackgroundVelocity(0);
        currentObstacles->accept(new ObstacleVelocityUpdateVisitor(), 0);
        powerUpFactory->setVelocity(0);
        if (currencyFactory != nullptr) {
            currencyFactory->setVelocity(0);
        }
    }
}

//render score
void Stage3Game::renderScore(QPainter &painter) {
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(20);
    painter.setFont(font);

    QString scoreDisplay("Score: ");
    scoreDisplay.append(QString::number(score));
    painter.drawText(300, 50, scoreDisplay);
}

//render final screen using stats kept by game observer
void Stage3Game::renderFinalScreen(QPainter &painter) {
    double world_width = Config::config()->getWorldWidth();
    double world_height = Config::config()->getWorldHeight();

    painter.drawRect(0, world_height, world_width, world_height);
    painter.setPen(Qt::white);
    QFont font = painter.font();
    font.setPointSize(24);
    painter.setFont(font);


    QString final_score("Your final score is ");
    final_score.append(QString::number(score));
    final_score.append(".");
    painter.drawText(world_width * 0.3, world_height * 0.1, final_score);

    //result stats
    font.setPointSize(16);
    painter.setFont(font);

    QString jumps_performed("Number of jumps performed: ");
    jumps_performed.append(QString::number(gameObserver->getJumpCounter()));
    painter.drawText(world_width * 0.25, world_height * 0.2, jumps_performed);

    QString collisions("Number of collisions: L");
    collisions.append(QString::number(gameObserver->getLeftCollisionCounter()));
    collisions.append(" R");
    collisions.append(QString::number(gameObserver->getRightCollisionCounter()));
    collisions.append(" T");
    collisions.append(QString::number(gameObserver->getTopCollisionCounter()));
    collisions.append(" B");
    collisions.append(QString::number(gameObserver->getBottomCollisionCounter()));
    painter.drawText(world_width * 0.25, world_height * 0.3, collisions);

    QString purchases("Number of shop purchases: ");
    purchases.append(QString::number(gameObserver->getShopMenuCounter()));
    painter.drawText(world_width * 0.25, world_height * 0.4, purchases);

    QString powerUps("Number of power-ups obtained: ");
    powerUps.append(QString::number(gameObserver->getPowerUpCounter()));
    painter.drawText(world_width * 0.25, world_height * 0.5, powerUps);

    QString currency("Number of currency collected: ");
    currency.append(QString::number(gameObserver->getCurrencyCounter()));
    painter.drawText(world_width * 0.25, world_height * 0.6, currency);

}

