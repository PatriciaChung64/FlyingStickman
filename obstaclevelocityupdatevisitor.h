#ifndef OBSTACLEVELOCITYUPDATEVISITOR_H
#define OBSTACLEVELOCITYUPDATEVISITOR_H

//a visitor used to propogate velocity updates to all children,
//while avoiding direct edit of preexisting stage 2 class entity

class CompositeEntity;
class Entity;

class ObstacleVelocityUpdateVisitor {
public:
    ObstacleVelocityUpdateVisitor();
    void visit(CompositeEntity *parent, double velocity);
    void visit(Entity *parent, double velocity);
};

#endif // OBSTACLEVELOCITYUPDATEVISITOR_H
