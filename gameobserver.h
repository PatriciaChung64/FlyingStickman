#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

//an observer that keeps track of important game stat changes throughout the game,
//these counters are used for the result screen after finishing the game
class GameObserver {
public:
    GameObserver();

    int getJumpCounter() { return jumpCounter; }
    int getPowerUpCounter() { return powerUpCounter; }
    int getCurrencyCounter() { return currencyCounter; }
    int getShopMenuCounter() { return shopMenuCounter; }
    int getLeftCollisionCounter() { return leftCollisionCounter; }
    int getRightCollisionCounter() { return rightCollisionCounter; }
    int getTopCollisionCounter() { return topCollisionCounter; }
    int getBottomCollisionCounter() { return bottomCollisionCounter; }

    void incrementJumpCounter() { jumpCounter += 1; }
    void incrementPowerUpCounter() { powerUpCounter += 1; }
    void incrementCurrencyCounter() { currencyCounter += 1; }
    void incrementShopMenuCounter() { shopMenuCounter += 1; }
    void incrementLeftCollisionCounter() { leftCollisionCounter += 1; }
    void incrementRightCollisionCounter() { rightCollisionCounter += 1; }
    void incrementTopCollisionCounter() { topCollisionCounter += 1; }
    void incrementBottomCollisionCounter() { bottomCollisionCounter += 1; }

protected:
    int jumpCounter;
    int powerUpCounter;
    int currencyCounter;
    int shopMenuCounter;
    int leftCollisionCounter;
    int rightCollisionCounter;
    int topCollisionCounter;
    int bottomCollisionCounter;
};

#endif // GAMEOBSERVER_H
