#include "giantplayerstate.h"
#include "stage3player.h"
#include "obstacle.h"

GiantPlayerState::GiantPlayerState(Stage3Player *player):
    PlayerState(player) {
    //revert possible changes made by previous states
    //set all collision effects to destroying the obstacle collided with
    player->setDestroyOnCollision(true);
    player->setJumpHeight(80);
    player->setMaxJumpCount(2);
}

void GiantPlayerState::leftCollisionEffect(Stage3Player *player) {
    //no effect on stickman
}

void GiantPlayerState::rightCollisionEffect(Stage3Player *player) {
    //no effect on stickman
}

void GiantPlayerState::topCollisionEffect(Stage3Player *player) {
    //no effect on stickman
}

void GiantPlayerState::bottomCollisionEffect(Stage3Player *player) {
    //no effect on stickman
}
