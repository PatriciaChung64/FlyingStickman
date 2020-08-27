#ifndef STAGE3GAME_H
#define STAGE3GAME_H

#include <memory>
#include "gamedialog.h"
#include "stagememento.h"
#include "powerupfactory.h"
#include "currencyfactory.h"
#include "gameobserver.h"

class Stage3Config;
class Stage3Player;
class Background;
class Entity;

//the dialog class for the stage 3 game, mainly handles responsiblities
//- prepare next stage by commanding random generation of currencies (if toggled on) and power ups
//- issue restore statement and passing memento to player, background, obstacles, powerups and currencies when left/right collision occurs
//- render & update the game components: player, background, composite obstacle tree, powerup, currency, pause dialog
//- notify game observer of game stat changes managed by stage3game

class Stage3Game : public GameDialog {
    friend class Stage3Tester;
public:
    explicit Stage3Game(std::shared_ptr<Stage3Player> player,
                        std::shared_ptr<Background> background,
                        std::shared_ptr<Entity> obstacleRoot,
                        std::shared_ptr<PowerUpFactory> powerUpFactory,
                        int maxStage, std::shared_ptr<GameObserver> gameObserver,
                        std::shared_ptr<CurrencyFactory> currencyFactory = nullptr);
    ~Stage3Game() override;

    void incrementScore(int score_change) { score += score_change; }
    void pause() override;
    void unpause() override;

public slots:
    void closeGame() { this->close(); }

protected:
    void nextStage();

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    void renderScore(QPainter &painter);
    void renderFinalScreen(QPainter &painter);

    std::shared_ptr<Stage3Player> player;
    std::shared_ptr<Background> background;
    std::shared_ptr<Entity> obstacleRoot;
    std::shared_ptr<PowerUpFactory> powerUpFactory;
    std::shared_ptr<CurrencyFactory> currencyFactory;
    std::shared_ptr<GameObserver> gameObserver;

    std::unique_ptr<Entity> currentObstacles;
    std::unique_ptr<StageMemento> memento;

    int currentStage;
    int maxStage;

    bool stageCleared;
    bool gameOver;

    bool resultScreen;

    int score;
    double timeBonus;

    QTimer *timer;
};

#endif // STAGE3GAME_H
