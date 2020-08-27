#ifndef CURRENCYFACTORY_H
#define CURRENCYFACTORY_H

#include <vector>
#include <QPixmap>

#include "currency.h"
#include "stage3obstacle.h"
#include "coordinate.h"

//a flyweight factory for currencies, while also has the responsibility
//to randomly generate currency locations for each stage
class CurrencyFactory {
public:
    CurrencyFactory(QPixmap *sprite, double width, double height);

    std::vector<Currency *> createCurrency();

    void generateCurrency(std::vector<Entity *> obstacles);

    std::vector<Coordinate *> getCurrencyLocations() { return currencyLocations; }
    std::vector<bool> getCurrencyStatus() { return currencyStatus; }
    bool getStatus(int index) { return currencyStatus.at(index); }

    void setVelocity(double new_velocity) { velocity = new_velocity; }
    void setStatus(int index, bool status) { currencyStatus[index] = status; }

    std::vector<Coordinate *> makeMemento() { return currencyLocations; }
    void restoreState(std::vector<double> currencyMemento);

protected:
    QPixmap *sprite;
    std::vector<Coordinate *> currencyLocations;
    std::vector<bool> currencyStatus;
    double velocity;
    double width;
    double height;
};

#endif // CURRENCYFACTORY_H
