#include "leafentity.h"


LeafEntity::LeafEntity(Coordinate* position, std::string name)
    : Entity(position, name), velocity(0) {}
