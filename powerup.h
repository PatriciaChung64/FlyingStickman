#ifndef POWERUP_H
#define POWERUP_H

#include <memory>
#include <QPainter>
#include "coordinate.h"

//power up class, flyweight product,
//its intrinsic and extrinsic attributes are both managed by powerUpFactory
//due to its role to randomly generate extrinsic attributes per stage

class Stage3Player;
class Stage3Game;

enum PowerUpTypes{
    tiny,
    normal,
    large,
    giant,
    NUM_POWERUPS = 4
};

class PowerUp {
public:
    PowerUp(Coordinate *position, int powerUpType,
            QPixmap *sprite, double width, double height,
            double velocity, int scoreWorth, bool exist);

    int getPowerUpType() { return powerUpType; }
    int getScoreWorth() { return scoreWorth; }

    bool checkXOverlapCollision(std::shared_ptr<Stage3Player> toCompare);
    bool checkYOverlapCollision(std::shared_ptr<Stage3Player> toCompare);

    virtual void applyPowerUpEffect(std::shared_ptr<Stage3Player> player);

    void update(bool paused, double time_since_last_frame);
    void render(QPainter &painter);

protected:
    bool exist;
    int powerUpType;
    int scoreWorth;
    double width;
    double height;
    double velocity;
    QPixmap *sprite;
    Coordinate *position;
};

#endif // POWERUP_H
