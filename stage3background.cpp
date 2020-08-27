#include "stage3background.h"
#include "config.h"

Stage3Background::Stage3Background(Coordinate main_coordinate):
    Background(main_coordinate) {
}

void Stage3Background::updatePosition() {
    first_coordinate.changeInXCoordinate(backgroundVelocity * 0.2);
    if (Config::config()->getBackgroundNumber() == 2) {
        second_coordinate.changeInXCoordinate(abs(backgroundVelocity * 0.5));
    }
    else {
        second_coordinate.changeInXCoordinate(backgroundVelocity * 0.3);
    }
    third_coordinate.changeInXCoordinate(backgroundVelocity);
}
