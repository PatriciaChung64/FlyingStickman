#include "stagememento.h"
#include "coordinate.h"
#include "stage3player.h"
#include "stage3obstacle.h"
#include "stage3background.h"
#include "stagegoal.h"


StageMemento::StageMemento() { }

void StageMemento::storePlayer(Stage3Player *player) {
    this->player.reset(new Stage3Player(player->lives, player->getGameObserver()));
    this->player->size = player->size;
    this->player->startingXPosition = player->startingXPosition;
    this->player->xVelocity = player->xVelocity;
    this->player->movementVelocity = player->movementVelocity;
    this->player->width = player->width;
    this->player->height = player->height;
    this->player->yVelocity = player->yVelocity;
    this->player->updateStickman();
    this->player->reached_Goal = player->reached_Goal;
    this->player->animation_update_counter = player->animation_update_counter;
    this->player->frame_number = player->frame_number;
    this->player->jump_count = player->jump_count;
    this->player->jumping = player->jumping;
    this->player->falling = player->falling;
}

void StageMemento::storeBackground(Background *background) {
    this->background.reset(new Stage3Background(background->main_coordinate));
    this->background->first_coordinate.setXCoordinateToZero(background->first_coordinate.getXCoordinate());
    this->background->first_coordinate.setYCoordinateToZero(background->first_coordinate.getYCoordinate());
    this->background->second_coordinate.setXCoordinateToZero(background->second_coordinate.getXCoordinate());
    this->background->second_coordinate.setYCoordinateToZero(background->second_coordinate.getYCoordinate());
    this->background->third_coordinate.setXCoordinateToZero(background->third_coordinate.getXCoordinate());
    this->background->third_coordinate.setYCoordinateToZero(background->third_coordinate.getYCoordinate());
    this->background->backgroundVelocity = background->backgroundVelocity;
    this->background->first = background->first;
    this->background->second = background->second;
    this->background->third = background->third;
}

void StageMemento::storeObstalces(std::vector<Entity *> obstacles_original) {
    obstacles.clear();
    for (auto it = obstacles_original.begin(); it != obstacles_original.end(); ++it) {
        obstacles.push_back((*it)->getPosition()->getXCoordinate());
    }
}

void StageMemento::storePowerUps(std::vector<Coordinate *> powerUpLocations) {
    powerUps.clear();
    for (auto it = powerUpLocations.begin(); it != powerUpLocations.end(); ++it) {
        powerUps.push_back((*it)->getXCoordinate());
    }
}

void StageMemento::storeCurrency(std::vector<Coordinate *> currencyLocations) {
    currency.clear();
    for (auto it = currencyLocations.begin(); it != currencyLocations.end(); ++it) {
        currency.push_back((*it)->getXCoordinate());
    }
}
