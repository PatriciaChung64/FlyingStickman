#include <iostream>
#include "entity.h"
#include "obstaclevelocityupdatevisitor.h"
#include "coordinate.h"

Entity::Entity()
    : children(std::vector<Entity*>()),
      position(nullptr) {}

Entity::Entity(Coordinate* position, std::string name)
    : children(std::vector<Entity*>()),
      position(position),
      name(name) {}

Entity::~Entity() {
    delete position;
}

Coordinate* Entity::getPosition() {
    return position;
}

void Entity::setPosition(Coordinate* position) {
    this->position = position;
}

void Entity::accept(ObstacleVelocityUpdateVisitor *visitor, double velocity) {
    visitor->visit(this, velocity);
}

void Entity::restoreChildrenState(std::vector<double> childrenMemento) {
    for (unsigned int i = 0; i < childrenMemento.size(); i++) {
        children.at(i)->getPosition()->setXCoorindate(childrenMemento.at(i));
    }
}
