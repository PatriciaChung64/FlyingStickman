#ifndef CURRENCY_H
#define CURRENCY_H

#include <QPainter>
#include "coordinate.h"
#include "powerup.h"

//a different type of powerup, currencys don't change stickman size, so
//must overwrite applyPowerUpEffect method
class Currency : public PowerUp {
public:
    Currency(Coordinate *position, int powerUpType,
             QPixmap *sprite, double width, double height,
             double velocity, bool exist, int scoreWorth = 10);

    void applyPowerUpEffect(std::shared_ptr<Stage3Player> player) override;

    virtual ~Currency() { }
};

#endif // CURRENCY_H
