#include <algorithm>

#include "powerup.h"
#include "stage3player.h"
#include "stage3game.h"

PowerUp::PowerUp(Coordinate *position, int powerUpType, QPixmap *sprite,
                 double width, double height, double velocity, int scoreWorth, bool exist):
    position(position), powerUpType(powerUpType), sprite(sprite), width(width),
    height(height), velocity(velocity), scoreWorth(scoreWorth), exist(exist) {
}

bool PowerUp::checkXOverlapCollision(std::shared_ptr<Stage3Player> toCompare) {
    return std::max(position->getXCoordinate(), toCompare->getXPosition()) <=
            std::min(position->getXCoordinate() + width, toCompare->getXPosition() + toCompare->getWidth());
}

bool PowerUp::checkYOverlapCollision(std::shared_ptr<Stage3Player> toCompare) {
    return std::max(position->getYCoordinate() - height, toCompare->getYPosition() - toCompare->getHeight()) <=
            std::min((int)position->getYCoordinate(), (int)toCompare->getYPosition());
}

void PowerUp::applyPowerUpEffect(std::shared_ptr<Stage3Player> player) {
    if (powerUpType == PowerUpTypes::tiny) {
        player->changeSize("tiny");
    }

    else if (powerUpType == PowerUpTypes::normal) {
        player->changeSize("normal");
    }

    else if (powerUpType == PowerUpTypes::large) {
        player->changeSize("large");
    }

    else if (powerUpType == PowerUpTypes::giant) {
        player->changeSize("giant");
    }
}

void PowerUp::update(bool paused, double time_since_last_frame) {
    if (!paused) {
        position->changeInXCoordinate(velocity);
    }
}

void PowerUp::render(QPainter &painter) {
    if (exist) {
        painter.drawPixmap(position->getQtRenderingXCoordinate(), position->getQtRenderingYCoordinate(), width, height, *sprite);
    }
}
