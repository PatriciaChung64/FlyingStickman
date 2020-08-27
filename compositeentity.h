#pragma once

#include <string>
#include "entity.h"

class ObstacleVelocityUpdateVisitor;

class CompositeEntity : public Entity {
public:
    CompositeEntity(Coordinate* position, std::string name);
    ~CompositeEntity() = default;

    void addChild(Entity* e);
    void removeChild(Entity* e);
    Entity* getChild(Entity* e);

    void renderChildren(QPainter &painter);
    void updateChildren(bool paused, double deltaTimeMilliseconds);

    void accept(ObstacleVelocityUpdateVisitor *visitor, double velocity);
};
