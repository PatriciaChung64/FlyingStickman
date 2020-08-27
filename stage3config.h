#ifndef STAGE3CONFIG_H
#define STAGE3CONFIG_H

#include "extendedconfig.h"
#include <memory>

//config reader class for stage3config, ensure stage 3 config file
//is located IN THE BUILD FOLDER and NAME = "stage3config.txt",
//reference README for format

class Stage3Config {
public:
    explicit Stage3Config(Config *config);

    int getLives() { return lives; }
    int getBaseObstaclesPerStage() { return baseObstaclesPerStage; }
    int getStageClearRequirementIncrementRate() { return stageClearRequirementIncrementRate; }
    int getPowerUpWidth() { return powerUpWidth; }
    int getPowerUpHeight() { return powerUpHeight; }
    bool getCurrencyToggle() { return currencyToggle; }
    std::vector<int> getScoreWorth() { return scoreWorth; }

protected:
    void readConfig();

    int lives;
    int baseObstaclesPerStage;
    int stageClearRequirementIncrementRate;
    int powerUpWidth;
    int powerUpHeight;
    bool currencyToggle;
    std::vector<int> scoreWorth;

    std::unique_ptr<ExtendedConfig> stage2Config;
};

#endif // STAGE3CONFIG_H
