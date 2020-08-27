#include "largeplayerstate.h"
#include "stage3player.h"

LargePlayerState::LargePlayerState(Stage3Player *player):
    PlayerState(player){
    //revert possible changes made by previous states and increase jumpHeight
    player->setJumpHeight(110);
    player->setDestroyOnCollision(false);
    player->setMaxJumpCount(2);
}

LargePlayerState::~LargePlayerState() { }
