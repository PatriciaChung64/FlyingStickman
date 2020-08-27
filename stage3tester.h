#ifndef STAGE3TESTER_H
#define STAGE3TESTER_H

#include "stage3player.h"
#include "stage3obstacle.h"
#include "stage3game.h"
#include "stage3gamefactory.h"
#include "stagememento.h"
#include "stage3pausedialog.h"


class Stage3Tester {
public:
    Stage3Tester(Stage3GameFactory *testFactory);
    bool testLeftCollision();
    bool testRightCollision();
    bool testTopCollision();
    bool testBottomCollision();
    bool testPlayerStateChange();
    bool testRestore();
    bool testShopPurchase();

    ~Stage3Tester();

private:
    Stage3GameFactory *testFactory;
    std::unique_ptr<Stage3Game> testGame;

};

#endif // STAGE3TESTER_H
