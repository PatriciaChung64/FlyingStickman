#include <random>
#include <algorithm>
#include "powerupfactory.h"
#include "config.h"

//similar logic to currency factory

PowerUpFactory::PowerUpFactory(std::vector<QPixmap *> powerUpResources,
                               std::vector<int> powerUpScoreWorth, double width, double height):
    powerUpResources(powerUpResources), powerUpScoreWorth(powerUpScoreWorth),
    width(width), height(height), velocity(0) {
}

std::vector<PowerUp *> PowerUpFactory::createPowerUps() {
    std::vector<PowerUp *> products;
    for (unsigned int i = 0; i < powerUpLocations.size(); i++) {
        products.push_back(new PowerUp(powerUpLocations.at(i), powerUpTypes.at(i),
                powerUpResources.at(powerUpTypes.at(i)), width, height, velocity,
                powerUpScoreWorth.at(powerUpTypes.at(i)), status.at(i)));
    }
    return products;
}

void PowerUpFactory::generatePowerUps(std::vector<Entity *> obstacles) {
    generatePowerUpLocations(obstacles);
    generatePowerUpTypes();
    status.clear();
    for (unsigned int i = 0; i < powerUpResources.size(); i++) {
        status.push_back(true);
    }
}

void PowerUpFactory::generatePowerUpLocations(std::vector<Entity *> obstacles) {
    int numOfPowerUps = obstacles.size()/3;
    numOfPowerUps += (rand()%2 + 1); //randomize power up number per stage by a fixed range
    double generalXOffset = (obstacles.at(obstacles.size() - 1)->getPosition()->getXCoordinate()
            - obstacles.at(0)->getPosition()->getXCoordinate() - 100) / numOfPowerUps;
    powerUpLocations.clear(); //clear the last set of powerups generated
    int world_height = Config::config()->getWorldHeight();
    int world_width = Config::config()->getWorldWidth();
    double culmulatedXOffset = 0;
    for (unsigned int i = 0; i < numOfPowerUps; i++) {
        double x = culmulatedXOffset + generalXOffset + rand()%51;
        double y = rand()%(int)(world_height * 0.6) + world_height * 0.2;

        bool noOverlap = true;

        for (auto it = obstacles.begin(); it != (obstacles.end()-1); ++it) {
            Stage3Obstacle *currentObstacle = dynamic_cast<Stage3Obstacle *>(*it);
            bool xOverlap = std::max(x, currentObstacle->getPosition()->getXCoordinate()) <=
                    std::min(x+width, currentObstacle->getPosition()->getXCoordinate() + currentObstacle->getWidth());

            bool yOverlap = std::max(y-height, currentObstacle->getPosition()->getYCoordinate() - currentObstacle->getHeight()) <=
                    std::min(y, currentObstacle->getPosition()->getYCoordinate());
            if (xOverlap && yOverlap) {
                noOverlap = false;
                break;
            }
        }

        culmulatedXOffset += x;


        if (noOverlap) {
            powerUpLocations.push_back(new Coordinate(x, y, world_height, world_width));
        }

    }
}

void PowerUpFactory::generatePowerUpTypes() {
    powerUpTypes.clear();
    for(unsigned int i = 0; i < powerUpLocations.size(); i++) {
        powerUpTypes.push_back(rand()%4);
    }
}

void PowerUpFactory::restoreState(std::vector<double> powerUpMemento) {
    for (unsigned int i = 0; i < powerUpMemento.size(); i++) {
        powerUpLocations.at(i)->setXCoorindate(powerUpMemento.at(i));
        setStatus(i, true);
    }
}
