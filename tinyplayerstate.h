#ifndef TINYPLAYERSTATE_H
#define TINYPLAYERSTATE_H

#include "playerstate.h"

//player state class for when stickman size = "tiny"
//allows stickman to do maximum of 3 consecutive jumps before falling

class TinyPlayerState : public PlayerState {
public:
    TinyPlayerState(Stage3Player *player);
    ~TinyPlayerState();
};

#endif // TINYPLAYERSTATE_H
