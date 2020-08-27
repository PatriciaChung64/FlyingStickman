#ifndef GIANTPLAYERSTATE_H
#define GIANTPLAYERSTATE_H

#include <vector>
#include "playerstate.h"

//player state when size = "giant"
//all collision effects are nullified

class GiantPlayerState : public PlayerState {
public:
    GiantPlayerState(Stage3Player *player);

    void leftCollisionEffect(Stage3Player *player) override;
    void rightCollisionEffect(Stage3Player *player) override;
    void topCollisionEffect(Stage3Player *player) override;
    void bottomCollisionEffect(Stage3Player *player) override;
};

#endif // GIANTPLAYERSTATE_H
