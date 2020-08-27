#ifndef STAGE3PAUSEDIALOG_H
#define STAGE3PAUSEDIALOG_H

#include <QDialog>
#include <memory>

#include "stage3player.h"
#include "stage3game.h"

//stage 3 pause dialog
//creates a shop menu that allows players to spend their collected currency to buy power ups
//click "Continue" to unpause and "Quit" to quit the game

namespace Ui {
class Stage3PauseDialog;
}

class Stage3PauseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Stage3PauseDialog(std::shared_ptr<Stage3Player> player, Stage3Game *game,
                               std::shared_ptr<GameObserver> gameObserver, QWidget *parent = nullptr);
    ~Stage3PauseDialog();

protected:
    void updateCurrencyOwned();

public slots:
    void tinyPurchase();
    void normalPurchase();
    void largePurchase();
    void giantPurchase();

    void unpause();
    void quitGame();

private:
    Ui::Stage3PauseDialog *ui;
    std::shared_ptr<Stage3Player> player;
    std::shared_ptr<GameObserver> gameObserver;
    Stage3Game *game;
};

#endif // STAGE3PAUSEDIALOG_H
