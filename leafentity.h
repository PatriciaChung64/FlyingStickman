#pragma once

#include <iostream>
#include "entity.h"

class Coordinate;

class LeafEntity : public Entity {

public:
    LeafEntity(Coordinate* position, std::string name);

    void setVelocity(double new_velocity) {
        velocity = new_velocity;
    }


protected:
    double velocity;
};

