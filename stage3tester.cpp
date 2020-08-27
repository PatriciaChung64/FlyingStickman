#include "stage3tester.h"
#include "playerstate.h"
#include "largeplayerstate.h"

Stage3Tester::Stage3Tester(Stage3GameFactory *testFactory)
{
    testGame.reset(dynamic_cast<Stage3Game *>(testFactory->createGame()));

    if (testLeftCollision()) {
        std::cout << "Passed left collision test." << std::endl;
    }
    else {
        std::cout << "Left collision test failed." << std::endl;
    }

    if (testRightCollision()) {
        std::cout << "Passed right collision test." << std::endl;
    }
    else {
        std::cout << "Right collision test failed." << std::endl;
    }

    if (testTopCollision()) {
        std::cout << "Passed top collision test. " << std::endl;
    }
    else {
        std::cout << "Top collision test failed. " << std::endl;
    }

    if (testBottomCollision()) {
        std::cout << "Passed bottom collision test." << std::endl;
    }
    else {
        std::cout << "Bottom collision test failed. " << std::endl;
    }

    if (testPlayerStateChange()) {
        std::cout << "Passed test player state change. " << std::endl;
    }
    else {
        std::cout << "Failed player state change test. " << std::endl;
    }

    if (testRestore()) {
        std::cout << "Passed memento restore test." << std::endl;
    }
    else {
        std::cout << "Failed memento restore test." << std::endl;
    }

    if (testShopPurchase()) {
        std::cout << "Passed shop purchase test." << std::endl;
    }
    else {
        std::cout << "Shop purchase test failed." << std::endl;
    }
}

//test stickman detects left collision with obstacle
bool Stage3Tester::testLeftCollision() {
    std::shared_ptr<Stage3Player> testPlayer = testGame->player;
    testPlayer->position->x_coordinate = 100;
    testPlayer->position->y_coordinate = 100;

    double world_width = testPlayer->position->frame_width;
    double world_height = testPlayer->position->frame_height;

    Entity *testObstacle1 = new Stage3Obstacle(new Coordinate(-200, 200, world_height, world_width),
                                              "test_Obstacle_1", Qt::red, 300, 200, nullptr);
    Entity *testObstacle2 = new Stage3Obstacle(new Coordinate(50, 500, world_height, world_width),
                                               "test_Obstacle_2", Qt::black, 50, 200, nullptr);
    Entity *testObstacle3 = new Stage3Obstacle(new Coordinate(0, 100, world_height, world_width),
                                               "test_Obstacle_3", Qt::blue, 50, 200, nullptr);
    std::vector<Entity *> testObstacles;
    testObstacles.push_back(testObstacle1);
    testObstacles.push_back(testObstacle2);
    testObstacles.push_back(testObstacle3);

    if (testPlayer->checkLeftCollision(testObstacles)) {
        delete testObstacle1;
        delete testObstacle2;
        delete testObstacle3;
        return true;
    }
    delete testObstacle1;
    delete testObstacle2;
    delete testObstacle3;
    return false;
}

//test stickman detects right collision with obstacle
bool Stage3Tester::testRightCollision() {
    std::shared_ptr<Stage3Player> testPlayer = testGame->player;

    testPlayer->position->x_coordinate = 100;
    testPlayer->position->y_coordinate = 100;

    double world_width = testPlayer->position->frame_width;
    double world_height = testPlayer->position->frame_height;

    testPlayer->width = 100;
    Entity *testObstacle1 = new Stage3Obstacle(new Coordinate(300, 200, world_height, world_width),
                                              "test_Obstacle_1", Qt::red, 300, 200, nullptr);
    Entity *testObstacle2 = new Stage3Obstacle(new Coordinate(400, 500, world_height, world_width),
                                               "test_Obstacle_2", Qt::black, 50, 200, nullptr);
    Entity *testObstacle3 = new Stage3Obstacle(new Coordinate(200, 100, world_height, world_width),
                                               "test_Obstacle_3", Qt::blue, 50, 200, nullptr);
    std::vector<Entity *> testObstacles;
    testObstacles.push_back(testObstacle1);
    testObstacles.push_back(testObstacle2);
    testObstacles.push_back(testObstacle3);

    if (testPlayer->checkRightCollision(testObstacles)) {
        delete testObstacle1;
        delete testObstacle2;
        delete testObstacle3;
        return true;
    }
    delete testObstacle1;
    delete testObstacle2;
    delete testObstacle3;
    return false;
}

//test stickman detects top collision
bool Stage3Tester::testTopCollision() {
    std::shared_ptr<Stage3Player> testPlayer = testGame->player;

    testPlayer->position->x_coordinate = 100;
    testPlayer->position->y_coordinate = 200;

    double world_width = testPlayer->position->frame_width;
    double world_height = testPlayer->position->frame_height;

    testPlayer->height = 100;
    testPlayer->width = 100;
    Entity *testObstacle1 = new Stage3Obstacle(new Coordinate(150, 500, world_height, world_width),
                                              "test_Obstacle_1", Qt::red, 300, 300, nullptr);
    Entity *testObstacle2 = new Stage3Obstacle(new Coordinate(400, 400, world_height, world_width),
                                               "test_Obstacle_2", Qt::black, 50, 200, nullptr);
    Entity *testObstacle3 = new Stage3Obstacle(new Coordinate(200, 100, world_height, world_width),
                                               "test_Obstacle_3", Qt::blue, 50, 200, nullptr);
    std::vector<Entity *> testObstacles;
    testObstacles.push_back(testObstacle1);
    testObstacles.push_back(testObstacle2);
    testObstacles.push_back(testObstacle3);

    if (testPlayer->checkTopCollision(testObstacles)) {
        delete testObstacle1;
        delete testObstacle2;
        delete testObstacle3;
        return true;
    }
    delete testObstacle1;
    delete testObstacle2;
    delete testObstacle3;
    return false;
}

//checks stickman detect bottom collision
bool Stage3Tester::testBottomCollision() {
    std::shared_ptr<Stage3Player> testPlayer = testGame->player;

    testPlayer->position->x_coordinate = 100;
    testPlayer->position->y_coordinate = 200;

    double world_width = testPlayer->position->frame_width;
    double world_height = testPlayer->position->frame_height;

    testPlayer->height = 100;
    testPlayer->width = 100;
    Entity *testObstacle1 = new Stage3Obstacle(new Coordinate(150, 500, world_height, world_width),
                                              "test_Obstacle_1", Qt::red, 300, 300, nullptr);
    Entity *testObstacle2 = new Stage3Obstacle(new Coordinate(400, 400, world_height, world_width),
                                               "test_Obstacle_2", Qt::black, 50, 200, nullptr);
    Entity *testObstacle3 = new Stage3Obstacle(new Coordinate(80, 200, world_height, world_width),
                                               "test_Obstacle_3", Qt::blue, 100, 200, nullptr);
    std::vector<Entity *> testObstacles;
    testObstacles.push_back(testObstacle1);
    testObstacles.push_back(testObstacle2);
    testObstacles.push_back(testObstacle3);

    if (!testPlayer->checkBottomCollision(testObstacles)) {
        delete testObstacle1;
        delete testObstacle2;
        delete testObstacle3;
        return true;
    }
    delete testObstacle1;
    delete testObstacle2;
    delete testObstacle3;
    return false;
}

//test currentState object correctly changed class when changing size
//i.e. state pattern properly implemented
bool Stage3Tester::testPlayerStateChange() {
    std::shared_ptr<Stage3Player> testPlayer = testGame->player;
    testPlayer->changeSize("normal");
    if (PlayerState *normalState = dynamic_cast<PlayerState *>(testPlayer->currentState.get())) {
        testPlayer->changeSize("large");
        if (LargePlayerState *largeState = dynamic_cast<LargePlayerState *>(testPlayer->currentState.get())) {
            return true;
        }
        return false;
    }
    return false;
}

//test memento can make correct storage of initial
//& restore state works properly
bool Stage3Tester::testRestore() {
    Entity *testObstacle1 = new Stage3Obstacle(new Coordinate(150, 500, 0, 0),
                                              "test_Obstacle_1", Qt::red, 300, 300, nullptr);
    Entity *testObstacle2 = new Stage3Obstacle(new Coordinate(400, 400, 0, 0),
                                               "test_Obstacle_2", Qt::black, 50, 200, nullptr);
    Entity *testObstacle3 = new Stage3Obstacle(new Coordinate(80, 200, 0, 0),
                                               "test_Obstacle_3", Qt::blue, 100, 200, nullptr);
    std::vector<Entity *> testObstacles;
    testObstacles.push_back(testObstacle1);
    testObstacles.push_back(testObstacle2);
    testObstacles.push_back(testObstacle3);

    StageMemento *testMemento = new StageMemento();
    testMemento->storeObstalces(testObstacles);

    testObstacle1->position->x_coordinate = 1000;
    testObstacle2->position->x_coordinate = -300;
    testObstacle3->position->x_coordinate = 0;

    std::unique_ptr<EmptyEntity>testParent(new EmptyEntity(new Coordinate(0, 0, 0, 0), "testParent"));
    testParent->addChild(testObstacle1);
    testParent->addChild(testObstacle2);
    testParent->addChild(testObstacle3);

    testParent->restoreChildrenState(testMemento->getStoredObstaclesCoordintes());
    bool allPassed = true;

    if (testObstacle1->position->x_coordinate != 150) {
        allPassed = false;
        delete testObstacle1;
    }
    if (testObstacle2->position->x_coordinate != 400) {
        allPassed = false;
        delete testObstacle2;
    }
    if (testObstacle3->position->x_coordinate != 80) {
        allPassed = false;
        delete testObstacle3;
    }
    delete testMemento;
    return allPassed;
}

//test shop purchase menu only correctly decrease currency when
//purchase is successful
bool Stage3Tester::testShopPurchase() {
    std::shared_ptr<Stage3Player> testPlayer = testGame->player;
    std::unique_ptr<Stage3PauseDialog> testPauseDialog(new Stage3PauseDialog(testPlayer, nullptr, testGame->gameObserver));
    testPlayer->currency = 9;
    testPauseDialog->tinyPurchase();
    if (testPlayer->currency != 9) {
        return false;
    }
    else {
        testPlayer->currency = 20;
        testPauseDialog->tinyPurchase();
        if (testPlayer->currency == 10) {
            return true;
        }
        return false;
    }
}

Stage3Tester::~Stage3Tester() {
}
