#include "obstaclevelocityupdatevisitor.h"
#include "compositeentity.h"
#include "leafentity.h"
#include "entity.h"

ObstacleVelocityUpdateVisitor::ObstacleVelocityUpdateVisitor() {

}

//visit all children and update its velocity
void ObstacleVelocityUpdateVisitor::visit(CompositeEntity *parent, double velocity) {
    std::vector<Entity *> toUpdate = parent->getChildren();
    for (auto it = toUpdate.begin(); it != toUpdate.end(); ++it) {
        LeafEntity *leaf = dynamic_cast<LeafEntity *>(*it);
        leaf->setVelocity(velocity);
    }
}

void ObstacleVelocityUpdateVisitor::visit(Entity *parent, double velocity) {
    std::vector<Entity *> toUpdate = parent->getChildren();
    for (auto it = toUpdate.begin(); it != toUpdate.end(); ++it) {
        LeafEntity *leaf = dynamic_cast<LeafEntity *>(*it);
        leaf->setVelocity(velocity);
    }
}
