#include "currency.h"
#include "stage3player.h"

Currency::Currency(Coordinate *position, int powerUpType,
                   QPixmap *sprite, double width, double height,
                   double velocity, bool exist, int scoreWorth):
    PowerUp(position, powerUpType, sprite, width, height, velocity, scoreWorth, exist)
{
}

void Currency::applyPowerUpEffect(std::shared_ptr<Stage3Player> player) {
    player->incrementCurrency();
    //player's current currency count increases when colliding with a currency item
}
