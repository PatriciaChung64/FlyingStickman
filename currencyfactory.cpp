#include <algorithm>
#include <random>
#include "currencyfactory.h"
#include "config.h"

CurrencyFactory::CurrencyFactory(QPixmap *sprite, double width, double height):
    sprite(sprite), velocity(0), width(width), height(height) {
}

//returns the stored states in Currency * form stored in a vector for rendering by stage3game
std::vector<Currency *> CurrencyFactory::createCurrency() {
    std::vector<Currency *> products;
    for (unsigned int i = 0; i < currencyLocations.size(); i++) {
        products.push_back(new Currency(currencyLocations.at(i), -1,
            sprite, width, height, velocity, currencyStatus.at(i)));
    }
    return products;
}

//randomly generate a new set of currency locations based on the stage's obstacles
void CurrencyFactory::generateCurrency(std::vector<Entity *> obstacles) {
    //the x-range we want our currencies to fall in
    double range = ((*(obstacles.end() - 1))->getPosition()->getXCoordinate() - 100) - 200;
    //range/width to get the max number of currencies items that can fit in this stage,
    //decreased by a random amount to simulate randomness
    double numOfCurrencies = range/width - rand()%10;

    //ensure previous set of currencies are cleared
    currencyLocations.clear();
    currencyStatus.clear();

    //generate x, y for each currency to create, check for collision and adjust accordingly
    double x_offset = Config::config()->getStickman()->getXPosition();
    double world_width = (*obstacles.begin())->getPosition()->getFrameWidth();
    double world_height = (*obstacles.begin())->getPosition()->getFrameHeight();
    for (unsigned int i = 0; i < numOfCurrencies; i++) {
        double x = x_offset;
        double y = rand()%(int)(world_height-height) + height;
        for (auto it = obstacles.begin(); it != (obstacles.end()-1); ++it) {
            bool xOverlap = std::max(x, (*it)->getPosition()->getXCoordinate()) <=
                    std::min(x+width, (*it)->getPosition()->getXCoordinate() + ((Stage3Obstacle *)(*it))->getWidth());
            if (xOverlap) {
                double yOverlap = std::min(y, (*it)->getPosition()->getYCoordinate())
                        - std::max(y-height, (*it)->getPosition()->getYCoordinate() - ((Stage3Obstacle *)(*it))->getHeight());
                if (yOverlap > 0) {
                    y += yOverlap;
                }
            }
        }
        currencyLocations.push_back(new Coordinate(x, y, world_height, world_width));
        currencyStatus.push_back(true);
        x_offset += width + rand()%100;
    }
}

//restore position of currency items on the stage
void CurrencyFactory::restoreState(std::vector<double> currencyMemento) {
    for (unsigned int i = 0; i < currencyMemento.size(); i++) {
        currencyLocations.at(i)->setXCoorindate(currencyMemento.at(i));
    }
}

