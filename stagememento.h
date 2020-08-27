#ifndef STAGEMEMENTO_H
#define STAGEMEMENTO_H

#include <vector>
#include <memory>

//makes a copy of player,background,obstacle,powerup,currency state when requested
//stores this memento and returns them on request

//NOTE: obstacle, powerup and currency are only stored by initial x-coordinate & existence state for some,
//this is because only x-coordinate and existence state is subject to change in a game
//(obstacles don't move up and down)

class Stage3Player;
class Background;
class Entity;
class Coordinate;

class StageMemento {
public:
    StageMemento();

    void storePlayer(Stage3Player *player);
    void storeBackground(Background *background);
    void storeObstalces(std::vector<Entity *> obstacles);
    void storePowerUps(std::vector<Coordinate *> powerUpLocations);
    void storeCurrency(std::vector<Coordinate *> currencyLocations);

    std::shared_ptr<Stage3Player> getStoredPlayer() { return player; }
    std::shared_ptr<Background> getStoredBackground() { return background; }
    std::vector<double> getStoredObstaclesCoordintes() { return obstacles; }
    std::vector<double> getStoredPowerUpCoordinates() { return powerUps; }
    std::vector<double> getStoredCurrencyCoordinate() { return currency; }

private:
    std::shared_ptr<Stage3Player> player;
    std::shared_ptr<Background> background;
    std::vector<double> obstacles;
    std::vector<double> powerUps;
    std::vector<double> currency;
};

#endif // STAGEMEMENTO_H
