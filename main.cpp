#include "config.h"
#include "stage3config.h"
#include "startdialog.h"
#include "stage1gamefactory.h"
#include "stage2gamefactory.h"
#include "stage2gamestatefactory.h"
#include "stage3gamefactory.h"
#include "stage3tester.h"
#include "tester.h"

#include <QApplication>
#include <QSound>

#include <iostream>
#include <memory>


//Allocating and initializing Config static data member. The pointer is being allocated - not the object itself
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //Sets up the config class for all files to use
    Config::config()->setupConfig();

    //Infinite loop of background music
    QSound sound(":sound/background_music.wav");
    sound.setLoops(-1);
    sound.play();

    GameFactory *factory = new Stage1GameFactory();

    if (!Config::config()->getStage3Toggle()) {
        // Create testing interface with a separate game state.
        auto state_factory = std::unique_ptr<GameStateFactory>(new Stage2GameStateFactory());
        Tester tester(state_factory);
        tester.run(2048);

        // Create rendered version of the game
        factory = new Stage2GameFactory();
    }

    else {
        Stage3Config *stage3config = new Stage3Config(Config::config());
        factory = new Stage3GameFactory(stage3config);
        Stage3Tester *tester = new Stage3Tester(new Stage3GameFactory(stage3config));
        delete tester;
    }

    StartDialog start_dialog(factory);
    start_dialog.setWindowTitle("Main Menu");
    start_dialog.show();

    auto exit_code = a.exec();
    return exit_code;
}
