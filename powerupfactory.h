#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include <vector>
#include <QPixmap>

#include "powerup.h"
#include "stage3obstacle.h"

//flyweight factory
//intrinsic state: Qpixmap resource, power up score worth, width, height
//extrinsic state: existence, velocity, location
//this factory keeps both states since it is also responsible for
//GENERATING extrinsic state variables for each new stage (randomized)

class PowerUpFactory {
public:
    PowerUpFactory(std::vector<QPixmap *> powerUpResources,
                   std::vector<int> powerUpScoreWorth, double width, double height);

    std::vector<PowerUp *> createPowerUps();

    std::vector<Coordinate *> getPowerUpLocations() { return powerUpLocations; }
    bool getStatus(int i) { return status.at(i); }

    void setStatus(int index, bool new_status) { status[index] = new_status; }
    void setVelocity(double new_velocity) { velocity = new_velocity; }

    void generatePowerUps(std::vector<Entity *> obstacles);

    void generatePowerUpLocations(std::vector<Entity *> obstacles);
    void generatePowerUpTypes();

    std::vector<Coordinate *> makeMemento() { return this->powerUpLocations; }
    void restoreState(std::vector<double> powerUpMemento);

protected:
    std::vector<QPixmap *> powerUpResources;
    std::vector<int> powerUpScoreWorth;
    std::vector<Coordinate *> powerUpLocations;
    std::vector<int> powerUpTypes;
    std::vector<bool> status;
    double velocity;
    double width;
    double height;
};

#endif // POWERUPFACTORY_H
