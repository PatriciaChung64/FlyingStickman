#ifndef STAGE3GAMEFACTORY_H
#define STAGE3GAMEFACTORY_H

#include "gamefactory.h"
#include "gamedialog.h"
#include "stage3config.h"
#include "stage3background.h"
#include "stage3player.h"
#include "compositeentity.h"
#include "powerupfactory.h"
#include "gameobserver.h"

//factory that creates stage3game based on config and stage3config

class Stage3GameFactory : public GameFactory {
public:
    explicit Stage3GameFactory(Stage3Config *config);
    GameDialog* createGame() override;

    std::shared_ptr<Stage3Player> createStickman(std::shared_ptr<GameObserver> gameObserver);
    std::shared_ptr<Background> createBackground();
    std::shared_ptr<CompositeEntity> createObstacleRoot(int base, int incrementRate);
    std::shared_ptr<PowerUpFactory> createPowerUpFactory(int width, int height);

    ~Stage3GameFactory() override;

private:
    std::unique_ptr<ExtendedConfig> stage2config;
    std::unique_ptr<Stage3Config> stage3config;

    int maxStage;
};

#endif // STAGE3GAMEFACTORY_H
