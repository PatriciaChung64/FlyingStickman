#ifndef LARGEPLAYERSTATE_H
#define LARGEPLAYERSTATE_H

#include "playerstate.h"

//player state class for when player size = "large"
//increases provided player's jump height

class LargePlayerState : public PlayerState {
public:
    LargePlayerState(Stage3Player *player);
    ~LargePlayerState();
};

#endif // LARGEPLAYERSTATE_H
