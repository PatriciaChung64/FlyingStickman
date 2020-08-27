#include <cmath>

#include "playerstate.h"
#include "stage3player.h"
#include "gameobserver.h"

PlayerState::PlayerState(Stage3Player *player) {
    player->setJumpHeight(80);
    player->setMaxJumpCount(2);
    player->setDestroyOnCollision(false);
}

//default effects, assume size NORMAL

//lose life and reset stage
void PlayerState::leftCollisionEffect(Stage3Player *player) {
    player->decreaseLives();
    player->setResetStage(true);
    player->getGameObserver()->incrementLeftCollisionCounter();
}

//lose life and reset stage
void PlayerState::rightCollisionEffect(Stage3Player *player) {
    player->decreaseLives();
    player->setResetStage(true);
    player->getGameObserver()->incrementRightCollisionCounter();
}

//gets bounced back (y velocity flipped) and starts falling if was jumping
void PlayerState::topCollisionEffect(Stage3Player *player) {
    if (player->getJumping()) {
        player->setYVelocity(-(player->getYVelocity() * 0.8));
        player->setJumping(false);
        player->setJumpCount(0);
        player->setFalling(true);
        player->getGameObserver()->incrementTopCollisionCounter();
    }
}

//stop falling if was falling (stand on the obstacle)
void PlayerState::bottomCollisionEffect(Stage3Player *player) {
    if (player->getFalling()) {
        player->setYVelocity(0);
        player->setFalling(false);
        player->getGameObserver()->incrementBottomCollisionCounter();
    }
}



PlayerState::~PlayerState() { }
