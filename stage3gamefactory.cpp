#include <sstream>

#include "stage3gamefactory.h"
#include "stage3player.h"
#include "emptyentity.h"
#include "stage3obstacle.h"
#include "stagegoal.h"
#include "stage3game.h"
#include "obstaclevelocityupdatevisitor.h"

Stage3GameFactory::Stage3GameFactory(Stage3Config *config):
    stage2config(new ExtendedConfig(*Config::config())),
    stage3config(config), maxStage(1) {
}

GameDialog *Stage3GameFactory::createGame() {
    std::shared_ptr<GameObserver> gameObserver(new GameObserver());
    if (!stage3config->getCurrencyToggle()) {
        return new Stage3Game(createStickman(gameObserver), createBackground(),
                              createObstacleRoot(stage3config->getBaseObstaclesPerStage(), stage3config->getStageClearRequirementIncrementRate()),
                              createPowerUpFactory(stage3config->getPowerUpWidth(), stage3config->getPowerUpHeight()), maxStage, gameObserver);

    }
    else {
        return new Stage3Game(createStickman(gameObserver), createBackground(),
                              createObstacleRoot(stage3config->getBaseObstaclesPerStage(), stage3config->getStageClearRequirementIncrementRate()),
                              createPowerUpFactory(stage3config->getPowerUpWidth(), stage3config->getPowerUpHeight()), maxStage, gameObserver,
                              std::shared_ptr<CurrencyFactory>(new CurrencyFactory(new QPixmap("coin.png"), 30, 30)));

    }
}

//divide the read obstacles by stages, baseObstaclesPerStage in stage3config define a basic amount of obstacles in each stage
//incrementRate also in stage3config means for each stage, the number of obstacles in the next stage increment by this rate
//if not enough obstacles, just put goal at the end of the last obstacle
std::shared_ptr<CompositeEntity> Stage3GameFactory::createObstacleRoot(int base, int incrementRate) {
    int obstaclesPerStage = base;

    std::shared_ptr<CompositeEntity> root(new EmptyEntity(nullptr, "root"));

    unsigned int world_width = Config::config()->getWorldWidth();
    unsigned int world_height = Config::config()->getWorldHeight();

    int stageObstacleCount = 0;
    int x_offset = Config::config()->getStickman()->getXPosition();
    EmptyEntity *stageParent = nullptr;
    std::vector<ObstacleConfig *> obstacle_data = stage2config->getObstacleData();
    for (unsigned int i = 0; i < obstacle_data.size(); i++) {
        if (stageObstacleCount == 0) {
            stageParent = new EmptyEntity(nullptr, std::to_string(maxStage));
            root->addChild(stageParent);
        }
        ObstacleConfig *current_data = obstacle_data.at(i);
        x_offset += current_data->offset_x;
        std::stringstream name;
        name << "obstacle_" << stageObstacleCount;
        Coordinate *position = new Coordinate(x_offset, current_data->position_y, world_height, world_width);
        LeafEntity *obstacle = new Stage3Obstacle(position, name.str(),
            QColor(current_data->colour_red, current_data->colour_green, current_data->colour_blue),
            current_data->width, current_data->height, stageParent);
        stageParent->addChild(obstacle);
        stageObstacleCount++;

        if (stageObstacleCount == obstaclesPerStage && i < obstacle_data.size()-1) {
            obstaclesPerStage += incrementRate;
            stageObstacleCount = 0;
            maxStage++;

            LeafEntity *goal = new StageGoal(new Coordinate(x_offset + current_data->width + 200, 0, world_width, world_height));
            stageParent->addChild(goal);

            x_offset = Config::config()->getStickman()->getXPosition();
        }

        if (i == obstacle_data.size() - 1) {
            LeafEntity *goal = new StageGoal(new Coordinate(x_offset + current_data->width + 200, 0, world_width, world_height));
            stageParent->addChild(goal);
        }
    }

    return root;
}

std::shared_ptr<Stage3Player> Stage3GameFactory::createStickman(std::shared_ptr<GameObserver> gameObserver) {
    return std::shared_ptr<Stage3Player>(new Stage3Player(stage3config->getLives(), gameObserver));
}

std::shared_ptr<Background> Stage3GameFactory::createBackground() {
    return std::shared_ptr<Background>(new Stage3Background(Coordinate(0, Config::config()->getWorldHeight(), Config::config()->getWorldHeight(), Config::config()->getWorldWidth())));
}

std::shared_ptr<PowerUpFactory> Stage3GameFactory::createPowerUpFactory(int width, int height) {
    std::vector<QPixmap *>resources;
    resources.push_back(new QPixmap("tinyPowerUp.png"));
    resources.push_back(new QPixmap("normalPowerUp.png"));
    resources.push_back(new QPixmap("largePowerUp.png"));
    resources.push_back(new QPixmap("giantPowerUp.png"));

    return std::shared_ptr<PowerUpFactory>(new PowerUpFactory(resources, stage3config->getScoreWorth(), width, height));
}

Stage3GameFactory::~Stage3GameFactory() {
}
