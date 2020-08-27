#pragma once

#include <QList>
#include <QPixmap>
#include <QPainter>
#include <QDialog>
#include <QMediaPlayer>
#include <memory>

#include "coordinate.h"

class StageMemento;

class Background {
    friend class StageMemento;
public:

    Background(Coordinate main_coordinate);
    ~Background() = default;

    //Render the background depending on if it is in a paused state or not
    void render(QPainter &painter, bool paused);
    virtual void updatePosition();

    void setBackgroundVelocity(double new_velocity) { backgroundVelocity = new_velocity; }

    //Getter functions
    Coordinate getCoordinate() { return main_coordinate; }
    QPixmap getFirst() { return first; }
    QPixmap getSecond() { return second; }
    QPixmap getThird() { return third; }

    Background *makeMemento() { return this; }
    void restoreState(std::shared_ptr<Background> backgroundMemento);

protected:
    Coordinate main_coordinate;

    Coordinate first_coordinate;
    Coordinate second_coordinate;
    Coordinate third_coordinate;

    double backgroundVelocity;

    QPixmap first;
    QPixmap second;
    QPixmap third;
};



