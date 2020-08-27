#include <algorithm>
#include <cmath>
#include <QPainter>

#include "stage3player.h"
#include "tinyplayerstate.h"
#include "largeplayerstate.h"
#include "giantplayerstate.h"
#include "coordinate.h"
#include "stage3obstacle.h"
#include "config.h"

Stage3Player::Stage3Player(int lives, std::shared_ptr<GameObserver> gameObserver):
    Stickman(Config::config()->getStickman()->getSize(), Config::config()->getStickman()->getXPosition(), Config::config()->getStickman()->getMovementVelocity()),
    lives(lives), yVelocity(0), gameObserver(gameObserver),
    animation_update_counter(0), frame_number(1), currency(0),
    jumpHeight(80), gravity(-5), max_jump_count(2),
    jump_count(0), jumping(false), falling(false),
    destroy_On_Collision(false), reset_Stage(false) {
    updateStickman();
    position.reset(new Coordinate(0, height,
        Config::config()->getWorldHeight(), Config::config()->getWorldWidth()));
}

bool Stage3Player::checkGoalCollision(Entity *goal) {
    if (!reset_Stage) {
        reached_Goal = std::max(position->getXCoordinate(), goal->getPosition()->getXCoordinate()) <=
                std::min((position->getXCoordinate() + width), goal->getPosition()->getXCoordinate() + Config::config()->getWorldWidth());

    }
}

bool Stage3Player::checkTopCollision(std::vector<Entity *>obstacles) {
    bool topCollided = false;
    for(auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        if ((*it)->getName().compare("Goal") == 0) {
            checkGoalCollision(*it);
            return false;
        }

        bool xCollide = false;
        bool yCollide = false;

        if ((position->getYCoordinate()) - ((*it)->getPosition()->getYCoordinate() - ((Stage3Obstacle *)(*it))->getHeight()) <=  5.5 &&
                (position->getYCoordinate()) - ((*it)->getPosition()->getYCoordinate() - ((Stage3Obstacle *)(*it))->getHeight()) >= -5.5) {
            yCollide = true;
        }

        if (yCollide) {
           xCollide = std::max(position->getXCoordinate(), (*it)->getPosition()->getXCoordinate()) <=
                   std::min((position->getXCoordinate() + width), ((*it)->getPosition()->getXCoordinate() + ((Stage3Obstacle *)(*it))->getWidth()));
        }

        topCollided = xCollide && yCollide;
        if (topCollided) {
            if (destroy_On_Collision && !reached_Goal){
                ((Stage3Obstacle *)(*it))->deleteSelf();
            }
            else {
                break;
            }
        }
    }
    return topCollided;
}

bool Stage3Player::checkBottomCollision(std::vector<Entity *>obstacles) {
    bool bottomCollided = false;
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        if ((*it)->getName().compare("Goal") == 0) {
            checkGoalCollision(*it);
            return false;
        }

        bool xCollide = false;
        bool yCollide = false;

        if (position->getYCoordinate() - height - ((*it)->getPosition()->getYCoordinate()) <= 5.5 &&
                position->getYCoordinate() - height - ((*it)->getPosition()->getYCoordinate()) >= -5.5) {
            yCollide = true;
        }

        if (yCollide) {
           xCollide = std::max(position->getXCoordinate(), (*it)->getPosition()->getXCoordinate()) <=
                   std::min((position->getXCoordinate() + width), ((*it)->getPosition()->getXCoordinate() + ((Stage3Obstacle *)(*it))->getWidth()));
        }

        bottomCollided = xCollide && yCollide;

        if (bottomCollided) {
            if (destroy_On_Collision && !reached_Goal){
                ((Stage3Obstacle *)(*it))->deleteSelf();
            }
            else {
                break;
            }
        }
    }
    return bottomCollided;
}

bool Stage3Player::checkLeftCollision(std::vector<Entity *>obstacles) {
    bool leftCollided = false;
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        if ((*it)->getName().compare("Goal") == 0) {
            checkGoalCollision(*it);
            return false;
        }

        bool xCollide = false;
        bool yCollide = false;

        if (position->getXCoordinate() - (((Stage3Obstacle *)(*it))->getWidth() + (*it)->getPosition()->getXCoordinate()) <= 5.5 &&
            position->getXCoordinate() - (((Stage3Obstacle *)(*it))->getWidth() + (*it)->getPosition()->getXCoordinate()) >= -5.5) {
            xCollide = true;
        }

        if (xCollide) {
            if ((*it)->getPosition()->getYCoordinate() < ((Stage3Obstacle *)(*it))->getHeight()) {
                yCollide = std::max(position->getYCoordinate() - height, 0.0)<=
                        std::min(position->getYCoordinate(), (*it)->getPosition()->getYCoordinate());
            }
            else {
                yCollide = std::max(position->getYCoordinate() - height, (*it)->getPosition()->getYCoordinate() - ((Stage3Obstacle *)(*it))->getHeight()) <=
                        std::min(position->getYCoordinate(), (*it)->getPosition()->getYCoordinate());
            }
        }

        leftCollided = xCollide && yCollide;

        if (leftCollided) {
            if (destroy_On_Collision && !reached_Goal){
                ((Stage3Obstacle *)(*it))->deleteSelf();
            }
            else {
                break;
            }
        }
    }

    return leftCollided;
}

bool Stage3Player::checkRightCollision(std::vector<Entity *>obstacles) {
    bool rightCollided = false;
    for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
        if ((*it)->getName().compare("Goal") == 0) {
            checkGoalCollision(*it);
            return false;
        }

        bool xCollide = false;
        bool yCollide = false;

        if (position->getXCoordinate() + width - (*it)->getPosition()->getXCoordinate() <= 5.5 &&
                position->getXCoordinate() + width - (*it)->getPosition()->getXCoordinate() >= -5.5) {
            xCollide = true;
        }

        if (xCollide) {
            if ((*it)->getPosition()->getYCoordinate() < ((Stage3Obstacle *)(*it))->getHeight()) {
                yCollide = std::max(position->getYCoordinate() - height, 0.0)<=
                        std::min(position->getYCoordinate(), (*it)->getPosition()->getYCoordinate());
            }
            else {
                yCollide = std::max(position->getYCoordinate() - height, (*it)->getPosition()->getYCoordinate() - ((Stage3Obstacle *)(*it))->getHeight()) <=
                        std::min(position->getYCoordinate(), (*it)->getPosition()->getYCoordinate());
            }
        }

        rightCollided = xCollide && yCollide;

        if (rightCollided) {
            if (destroy_On_Collision && !reached_Goal){
                ((Stage3Obstacle *)(*it))->deleteSelf();
            }
            else {
                break;
            }
        }
    }
    return rightCollided;
}

int Stage3Player::getLives() {
    return lives;
}

void Stage3Player::decreaseLives() {
    lives--;
}

void Stage3Player::jump() {
    if (jump_count < max_jump_count && !falling) {
        jump_count++;
        changeYVelocity(jumpHeight/5);
        jumping = true;
        falling = false;
        gameObserver->incrementJumpCounter();
    }
}

void Stage3Player::update(bool paused, double time_since_last_frame, std::vector<Entity *>obstacles) {
    if (!paused && !reached_Goal) {
        double timestep = time_since_last_frame/1000.0;
        if (jumping || falling) {
            changeYVelocity(gravity * timestep * 5);
        }

        if (getYVelocity() < 0 && jumping) {
            jumping = false;
            falling = true;
            jump_count = 0;
        }

        if (checkTopCollision(obstacles)) {
            currentState->topCollisionEffect(this);
        }

        if (checkLeftCollision(obstacles)) {
            currentState->leftCollisionEffect(this);
        }

        if (checkRightCollision(obstacles)) {
            currentState->rightCollisionEffect(this);
        }

        if (checkBottomCollision(obstacles)) {
            currentState->bottomCollisionEffect(this);
        }
        else {
            //not on floor and no longer standing on an obstacle, start falling
            if (getYPosition() > height && getYVelocity() == 0 && !jumping && !falling) {
                falling = true;
            }
        }

        //if reached floor, stop falling
        if (getYPosition() <= height && falling) {
            changeYVelocity(-getYVelocity());
            position->setYCoordinateToZero(height);
            falling = false;
            jumping = false;
            jump_count = 0;
        }

        updateXPosition(getXVelocity() * 0.2);
        updateYPosition(getYVelocity() * 0.5);
    }

    if (animation_update_counter == 2) {
        frame_number++;
        animation_update_counter = 0;
    }

    //Once the frame is the last, reset
    if (frame_number > 9) {
        frame_number = 1;
    }

    if (!paused) {
        animation_update_counter++;
    }
}

void Stage3Player::render(QPainter &painter){
    if (xVelocity >= 0) {
        painter.drawPixmap(position->getQtRenderingXCoordinate(), position->getQtRenderingYCoordinate(), width, height, getPixmap(frame_number));
    }
    else {
        painter.drawPixmap(position->getQtRenderingXCoordinate(), position->getQtRenderingYCoordinate(), width, height, getPixmap(frame_number).transformed(QTransform().scale(-1, 1)));
    }

    QFont font = painter.font();
    font.setPointSize(20);
    painter.setFont(font);
    QString life_counter("Lives: ");
    life_counter.append(QString::number(lives));
    painter.drawText(50, 50, life_counter);
}

void Stage3Player::updateStickman() {
    setDimensions();
    if (size.compare("large") == 0) {
        currentState.reset(new LargePlayerState(this));
    }
    else if (size.compare("tiny") == 0) {
        currentState.reset(new TinyPlayerState(this));
    }
    else if (size.compare("giant") == 0) {
        currentState.reset(new GiantPlayerState(this));
    }
    else {
        currentState.reset(new PlayerState(this));
    }
}

void Stage3Player::restoreState(std::shared_ptr<Stage3Player> playerMemento) {
    this->xVelocity = 0;
    this->yVelocity = 0;
    this->size = playerMemento->size;
    updateStickman();
    this->position.reset(new Coordinate(playerMemento->startingXPosition,
        height, playerMemento->position->getFrameHeight(),
        playerMemento->position->getFrameWidth()));
    this->reached_Goal = playerMemento->reached_Goal;
    this->jumping = false;
    this->falling = false;
    this->jump_count = 0;
    this->movementVelocity = playerMemento->movementVelocity;
    this->startingXPosition = playerMemento->startingXPosition;
}
