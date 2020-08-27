#include "tinyplayerstate.h"
#include "stage3player.h"

TinyPlayerState::TinyPlayerState(Stage3Player *player):
    PlayerState(player) {
    player->setMaxJumpCount(3);
    player->setJumpHeight(80);
    player->setDestroyOnCollision(false);
}

TinyPlayerState::~TinyPlayerState() { }
