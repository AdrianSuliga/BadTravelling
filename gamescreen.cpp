#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QPainter>
#include <QStyleOption>
#include <QFontDatabase>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <cstdlib>

GameScreen::GameScreen(QWidget *parent, int gender) :
    QWidget(parent),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    sex = gender;

    ui->weaponLevelLabel->setFont(Girassol);
    ui->shieldLevelLabel->setFont(Girassol);
    ui->healthLevelLabel->setFont(Girassol);

    ui->dialogLabel->setFont(Girassol);
    ui->nameLabel->setFont(Girassol);

    ui->majatekLabel->setFont(Girassol);
    ui->amountOfMoneyLabel->setFont(Girassol);
    ui->shopLabel->setFont(Girassol);
    ui->weaponShopPriceLabel->setFont(Girassol);
    ui->shieldShopPriceLabel->setFont(Girassol);
    ui->healthShopPriceLabel->setFont(Girassol);
    ui->blahajShopPriceLabel->setFont(Girassol);
    ui->manulShopPriceLabel->setFont(Girassol);
    ui->drPieprzerShopPriceLabel->setFont(Girassol);
    ui->blahajShopLabel->setFont(Girassol);
    ui->manulShopLabel->setFont(Girassol);
    ui->drPieprzerShopLabel->setFont(Girassol);

    ui->heroAttackPointsLabel->setFont(Girassol);
    ui->heroDefensePointsLabel->setFont(Girassol);
    ui->heroHealthPointsLabel->setFont(Girassol);
    ui->enemyAttackPointsLabel->setFont(Girassol);
    ui->enemyDefensePointsLabel->setFont(Girassol);
    ui->enemyHealthPointsLabel->setFont(Girassol);

    gameLevel = 1;

    if (sex == 0)
    {
        ui->heroLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/Woman.png) 0 0 0 0 stretch stretch;");
        ui->speakerLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/Woman.png) 0 0 0 0 stretch stretch;");
        ui->nameLabel->setText("PODRÓŻNICZKA");
        heroAttack = 10;
        heroDefense = 15;
        heroHealth = 100;
        heroMaxHealth = 100;
    }
    if (sex == 1)
    {
        ui->heroLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/Man.png) 0 0 0 0 stretch stretch;");
        ui->speakerLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/Man.png) 0 0 0 0 stretch stretch;");
        ui->nameLabel->setText("PODRÓŻNIK");
        heroAttack = 20;
        heroDefense = 15;
        heroHealth = 50;
        heroMaxHealth = 50;
    }
    enemyAttack = -1;
    enemyDefense = -1;
    enemyHealth = -1;
    enemyMaxHealth = -1;

    wealth = 21000000;

    weaponLevel = 0;
    shieldLevel = 0;
    healthLevel = 0;

    weaponPrice = 100 * weaponLevel * weaponLevel * cbrt(weaponLevel) + 100;
    shieldPrice = 90 * shieldLevel * shieldLevel * cbrt(shieldLevel) + 90;
    healthPrice = 120 * healthLevel * healthLevel * cbrt(healthLevel) + 120;
    blahajPrice = 10000;
    manulPrice = 50000;
    drPieprzerPrice = 100000;
    healingPrice = -1;

    blahajOwned = false;
    manulOwned = false;
    drPieprzerOwned = false;

    loadVariables();

    connect(ui->weaponShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyWeapon);
    connect(ui->shieldShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyShield);
    connect(ui->healthShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyHealth);
    connect(ui->blahajShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyBlahaj);
    connect(ui->manulShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyManul);
    connect(ui->drPieprzerShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyDrPieprzer);

    connect(ui->continueButton, &QPushButton::clicked, this, &GameScreen::drawEnemy);

    level1MainFunction();
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::loadVariables()
{
    ui->weaponLevelLabel->setText("POZIOM " + QString::number(weaponLevel));
    ui->shieldLevelLabel->setText("POZIOM " + QString::number(shieldLevel));
    ui->healthLevelLabel->setText("POZIOM " + QString::number(healthLevel));

    ui->heroAttackPointsLabel->setText(QString::number(heroAttack, 10));
    ui->heroDefensePointsLabel->setText(QString::number(heroDefense, 10));
    ui->heroHealthPointsLabel->setText(QString::number(heroHealth, 10));

    ui->enemyAttackPointsLabel->setText("-");
    ui->enemyDefensePointsLabel->setText("-");
    ui->enemyHealthPointsLabel->setText("-");

    if (weaponLevel >= 0 && weaponLevel <= 4)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 5 && weaponLevel <= 9)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 10 && weaponLevel <= 14)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 15 && weaponLevel <= 19)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 20 && weaponLevel <= 24)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");

    if (shieldLevel >= 0 && shieldLevel <= 4)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 5 && shieldLevel <= 9)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 10 && shieldLevel <= 14)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 15 && shieldLevel <= 19)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 20 && shieldLevel <= 24)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass5.png) 0 0 0 0 stretch stretch;");

    if (healthLevel >= 0 && healthLevel <= 4)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 5 && healthLevel <= 9)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 10 && healthLevel <= 14)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 15 && healthLevel <= 19)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 20 && healthLevel <= 24)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass5.png) 0 0 0 0 stretch stretch;");

    ui->weaponShopPriceLabel->setText(QString::number(weaponPrice));
    ui->shieldShopPriceLabel->setText(QString::number(shieldPrice));
    ui->healthShopPriceLabel->setText(QString::number(healthPrice));
    ui->blahajShopPriceLabel->setText(QString::number(blahajPrice));
    ui->manulShopPriceLabel->setText(QString::number(manulPrice));
    ui->drPieprzerShopPriceLabel->setText(QString::number(drPieprzerPrice));

    ui->amountOfMoneyLabel->setText(QString::number(wealth));
}
void GameScreen::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

//LEVEL 1 - CENTRAL SQUARE
void GameScreen::level1MainFunction()
{
    srand(time(nullptr));
    drawEnemy();
    fight();
}

//SHOP
void GameScreen::userWantsToBuyWeapon()
{
    if (wealth >= weaponPrice)
    {
        wealth -= weaponPrice;
        weaponLevel++;
        if (sex == 0)
            heroAttack += weaponLevel * 5;
        if (sex == 1)
            heroAttack += weaponLevel * 7;
        weaponPrice = 100 * weaponLevel * weaponLevel * cbrt(weaponLevel) + 100;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
        ui->weaponLevelLabel->setText("LEVEL " + QString::number(weaponLevel));
        ui->heroAttackPointsLabel->setText(QString::number(heroAttack));
        ui->weaponShopPriceLabel->setText(QString::number(weaponPrice));
        if (weaponLevel >= 0 && weaponLevel <= 4)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 5 && weaponLevel <= 9)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 10 && weaponLevel <= 14)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass3.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 15 && weaponLevel <= 19)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass4.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 20 && weaponLevel <= 24)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass5.png) 0 0 0 0 stretch stretch;");

        if (weaponLevel > 0 && weaponLevel <= 5)
            ui->weaponLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 6 && weaponLevel <= 10)
            ui->weaponLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 11 && weaponLevel <= 15)
            ui->weaponLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass3.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 16 && weaponLevel <= 20)
            ui->weaponLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass4.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 21 && weaponLevel <= 25)
            ui->weaponLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass5.png) 0 0 0 0 stretch stretch;");

        ui->weaponLevelLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16pt;");
        ui->heroAttackPointsLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16px;");

        delay(500);

        ui->weaponLevelLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16pt;");
        ui->heroAttackPointsLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16px;");
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
}
void GameScreen::userWantsToBuyShield()
{
    if (wealth >= shieldPrice)
    {
        wealth -= shieldPrice;
        shieldLevel++;
        heroDefense += shieldLevel * 5;
        shieldPrice = 100 * shieldLevel * shieldLevel * cbrt(shieldLevel) + 100;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
        ui->shieldLevelLabel->setText("LEVEL " + QString::number(shieldLevel));
        ui->heroDefensePointsLabel->setText(QString::number(heroDefense));
        ui->shieldShopPriceLabel->setText(QString::number(shieldPrice));
        if (shieldLevel >= 0 && shieldLevel <= 4)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 5 && shieldLevel <= 9)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 10 && shieldLevel <= 14)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 15 && shieldLevel <= 19)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 20 && shieldLevel <= 24)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass5.png) 0 0 0 0 stretch stretch;");

        if (shieldLevel > 0 && shieldLevel <= 5)
            ui->shieldLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 6 && shieldLevel <= 10)
            ui->shieldLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 11 && shieldLevel <= 15)
            ui->shieldLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 16 && shieldLevel <= 20)
            ui->shieldLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 21 && shieldLevel <= 25)
            ui->shieldLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass5.png) 0 0 0 0 stretch stretch;");

        ui->shieldLevelLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16pt;");
        ui->heroDefensePointsLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16px;");

        delay(500);

        ui->shieldLevelLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16pt;");
        ui->heroDefensePointsLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16px;");
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
}
void GameScreen::userWantsToBuyHealth()
{
    if (wealth >= healthPrice)
    {
        wealth -= healthPrice;
        healthLevel++;
        if (sex == 0)
            heroMaxHealth += healthLevel * 12;
        if (sex == 1)
            heroMaxHealth += healthLevel * 10;
        healthPrice = 100 * healthLevel * healthLevel * cbrt(healthLevel) + 100;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
        ui->healthLevelLabel->setText("LEVEL " + QString::number(healthLevel));
        ui->heroHealthPointsLabel->setText(QString::number(heroMaxHealth));
        ui->healthShopPriceLabel->setText(QString::number(healthPrice));
        if (healthLevel >= 0 && healthLevel <= 4)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 5 && healthLevel <= 9)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 10 && healthLevel <= 14)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 15 && healthLevel <= 19)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 20 && healthLevel <= 24)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass5.png) 0 0 0 0 stretch stretch;");

        if (healthLevel > 0 && healthLevel <= 5)
            ui->healthLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 6 && healthLevel <= 10)
            ui->healthLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 11 && healthLevel <= 15)
            ui->healthLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 16 && healthLevel <= 20)
            ui->healthLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 21 && healthLevel <= 25)
            ui->healthLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass5.png) 0 0 0 0 stretch stretch;");

        ui->healthLevelLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16pt;");
        ui->heroHealthPointsLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16px;");

        delay(500);

        ui->healthLevelLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16pt;");
        ui->heroHealthPointsLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16px;");
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
}
void GameScreen::userWantsToBuyBlahaj()
{
    if (wealth >= ui->blahajShopPriceLabel->text().toInt(nullptr, 10))
    {
        wealth -= ui->blahajShopPriceLabel->text().toInt(nullptr, 10);
        ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
        blahajOwned = true;
        ui->blahajShopLabel->setText("KUPIONO");
        ui->blahajShopPriceLabel->setText("---");
        ui->blahajShopLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: rgb(180,180,180);");
        disconnect(ui->blahajShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyBlahaj);
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
}
void GameScreen::userWantsToBuyManul()
{
    if (wealth >= ui->manulShopPriceLabel->text().toInt(nullptr, 10))
    {
        wealth -= ui->manulShopPriceLabel->text().toInt(nullptr, 10);
        ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
        manulOwned = true;
        ui->manulShopLabel->setText("KUPIONO");
        ui->manulShopPriceLabel->setText("---");
        ui->manulShopLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: rgb(180,180,180);");
        disconnect(ui->manulShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyManul);
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
}
void GameScreen::userWantsToBuyDrPieprzer()
{
    if (wealth >= ui->drPieprzerShopPriceLabel->text().toInt(nullptr, 10))
    {
        wealth -= ui->drPieprzerShopPriceLabel->text().toInt(nullptr, 10);
        ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
        drPieprzerOwned = true;
        ui->drPieprzerShopLabel->setText("KUPIONO");
        ui->drPieprzerShopPriceLabel->setText("---");
        ui->drPieprzerShopLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: rgb(180,180,180);");
        disconnect(ui->drPieprzerShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyDrPieprzer);
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
}

void GameScreen::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameScreen::drawEnemy()
{
    switch (gameLevel)
    {
    case 1:
        int enemyType = rand() % 2;
        if (enemyType == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Bezdomny.png) 0 0 0 0 stretch stretch;");
            enemyAttack = 20;
            enemyDefense = 40;
            enemyHealth = 80;
            ui->enemyAttackPointsLabel->setText("20");
            ui->enemyDefensePointsLabel->setText("40");
            ui->enemyHealthPointsLabel->setText("80");
            ui->enemyHealthBar->setMaximum(0);
            ui->enemyHealthBar->setMaximum(80);
            ui->enemyHealthBar->setValue(80);
        }
        if (enemyType == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Dresiarz.png) 0 0 0 0 stretch stretch;");
            enemyAttack = 40;
            enemyDefense = 20;
            enemyHealth = 50;
            ui->enemyAttackPointsLabel->setText("40");
            ui->enemyDefensePointsLabel->setText("20");
            ui->enemyHealthPointsLabel->setText("50");
            ui->enemyHealthBar->setMaximum(0);
            ui->enemyHealthBar->setMaximum(50);
            ui->enemyHealthBar->setValue(50);
        }
        break;
    /*case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;*/
    }
}

void GameScreen::fight()
{
    connect(ui->enemyLabel, &QClickableLabel::clicked, this, [this]() {
        double damage = floor(0.2 * static_cast<double>(heroAttack) *
                              (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));
        if (enemyHealth - static_cast<int>(damage) >= 0)
        {
            enemyHealth -= static_cast<int>(damage);
            ui->enemyHealthBar->setValue(enemyHealth);
        }
        else if (enemyHealth - static_cast<int>(damage) < 0)
        {
            enemyHealth = 0;
            ui->enemyHealthBar->setValue(0);
        }
    } );
    QThread enemyAttackThread;
}

void GameScreen::attack()
{
    double damage = floor(0.2 * static_cast<double>(enemyAttack) *
                          (1 + static_cast<double>(enemyAttack) / static_cast<double>(heroDefense)));
    while (enemyHealth > 0)
    {
        if (heroHealth - static_cast<int>(damage) >= 0)
        {
            heroHealth -= static_cast<int>(damage);
            ui->heroHealthBar->setValue(heroHealth);
        }
        else if (heroHealth - static_cast<int>(damage) < 0)
        {
            heroHealth = 0;
            ui->heroHealthBar->setValue(0);
        }
        delay(1000);
    }
}

