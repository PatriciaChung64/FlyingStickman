#include "stage3pausedialog.h"
#include "ui_stage3pausedialog.h"

#define TINY_PRICE 10
#define NORMAL_PRICE 5
#define LARGE_PRICE 15
#define GIANT_PRICE 20

Stage3PauseDialog::Stage3PauseDialog(std::shared_ptr<Stage3Player> player, Stage3Game *game,
                                     std::shared_ptr<GameObserver> gameObserver, QWidget *parent) :
    QDialog(parent), player(player), game(game), gameObserver(gameObserver),
    ui(new Ui::Stage3PauseDialog)
{
    ui->setupUi(this);

    //render cost based on the above define prices
    QString tiny_price_string("Cost: ");
    tiny_price_string.append(QString::number(TINY_PRICE));
    ui->tiny_price->setText(tiny_price_string);

    QString normal_price_string("Cost: ");
    normal_price_string.append(QString::number(NORMAL_PRICE));
    ui->normal_price->setText(normal_price_string);

    QString large_price_string("Cost: ");
    large_price_string.append(QString::number(LARGE_PRICE));
    ui->large_price->setText(large_price_string);

    QString giant_price_string("Cost: ");
    giant_price_string.append(QString::number(GIANT_PRICE));
    ui->giant_price->setText(giant_price_string);

    //get currency owned by player
    updateCurrencyOwned();

    ui->tinyShopImg->setPixmap(QPixmap("tinyPowerUp.png"));
    ui->normalShopImg->setPixmap(QPixmap("normalPowerUp.png"));
    ui->largeShopImg->setPixmap(QPixmap("largePowerUp.png"));
    ui->giantShopImg->setPixmap(QPixmap("giantPowerUp.png"));

    connect(ui->purchase_tiny, SIGNAL(clicked()), this, SLOT(tinyPurchase()));
    connect(ui->purchase_normal, SIGNAL(clicked()), this, SLOT(normalPurchase()));
    connect(ui->purchase_large, SIGNAL(clicked()), this, SLOT(largePurchase()));
    connect(ui->purchase_giant, SIGNAL(clicked()), this, SLOT(giantPurchase()));
    connect(ui->Continue, SIGNAL(clicked()), this, SLOT(unpause()));
    connect(ui->Quit, SIGNAL(clicked()), this, SLOT(quitGame()));
}

void Stage3PauseDialog::updateCurrencyOwned() {
    int new_currency_owned = player->getCurrency();
    QString currency_display("Currency Owned: ");
    currency_display.append(QString::number(new_currency_owned));
    ui->currency_owned->setText(currency_display);
}

//for all purchase slots, if enough coins to buy,
//decrease the amount of coins by price and change size

void Stage3PauseDialog::tinyPurchase() {
    if (player->getCurrency() >= TINY_PRICE) {
        player->setCurrency(player->getCurrency() - TINY_PRICE);
        player->changeSize("tiny");
        player->updateStickman();
        updateCurrencyOwned();
        gameObserver->incrementShopMenuCounter();
    }
}

void Stage3PauseDialog::normalPurchase() {
    if (player->getCurrency() >= NORMAL_PRICE) {
        player->setCurrency(player->getCurrency() - NORMAL_PRICE);
        player->changeSize("normal");
        player->updateStickman();
        updateCurrencyOwned();
        gameObserver->incrementShopMenuCounter();
    }
}

void Stage3PauseDialog::largePurchase() {
    if (player->getCurrency() >= LARGE_PRICE) {
        player->setCurrency(player->getCurrency() - LARGE_PRICE);
        player->changeSize("large");
        player->updateStickman();
        gameObserver->incrementShopMenuCounter();
    }
}

void Stage3PauseDialog::giantPurchase() {
    if (player->getCurrency() >= GIANT_PRICE) {
        player->setCurrency(player->getCurrency() - GIANT_PRICE);
        player->changeSize("giant");
        player->updateStickman();
        gameObserver->incrementShopMenuCounter();
    }
}

void Stage3PauseDialog::unpause() {
    game->unpause();
    this->close();
}

void Stage3PauseDialog::quitGame() {
    game->close();
    this->close();
}

Stage3PauseDialog::~Stage3PauseDialog()
{
    delete ui;
}
