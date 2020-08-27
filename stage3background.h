#ifndef STAGE3BACKGROUND_H
#define STAGE3BACKGROUND_H

#include "background.h"

//stage3background that overwrites the position update behaviour of the background
//such that it is affected by velocity rather than hard-corded like stage 1

class Stage3Background : public Background {
public:
    Stage3Background(Coordinate main_coordinate);

    void updatePosition() override;

};

#endif // STAGE3BACKGROUND_H
