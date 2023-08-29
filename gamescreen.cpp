#include "gamescreen.h"
#include "ui_gamescreen.h"
#include <QPainter>
#include <QStyleOption>
#include <QFontDatabase>
#include <QFile>
#include <QTextStream>
#include <QStyleFactory>
#include <QTime>
#include <cstdlib>
#include <QDebug>
#include <QBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

GameScreen::GameScreen(QWidget *parent, int gender) :
    QWidget(parent),
    ui(new Ui::GameScreen)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    sex = gender;

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
    ui->heroHealthBar->setFont(Girassol);
    ui->heroHealthBar->setStyle(QStyleFactory::create("Fusion"));
    ui->enemyAttackPointsLabel->setFont(Girassol);
    ui->enemyDefensePointsLabel->setFont(Girassol);
    ui->enemyHealthPointsLabel->setFont(Girassol);
    ui->enemyHealthBar->setFont(Girassol);
    ui->enemyHealthBar->setStyle(QStyleFactory::create("Fusion"));

    ui->infoAboutActionLabel->setFont(Girassol);
    ui->confirmButton->setFont(Girassol);

    gameLevel = 1;
    enemyType = -1;
    numberOfRounds = 0;
    counterOfLines = 0;
    actionPoints = 0;
    nameToPath["PODRÓŻNIK"] = "border-image: url(:/images/images/AppScreenArt/Man.png) 0 0 0 0 stretch stretch;";
    nameToPath["PODRÓŻNICZKA"] = "border-image: url(:/images/images/AppScreenArt/Woman.png) 0 0 0 0 stretch stretch;";

    nameToPath["MENEL"] = "border-image: url(:/images/images/Level 1 - Central Square/Bezdomny.png) 0 0 0 0 stretch stretch;";
    nameToPath["RYCERZ ORTALIONU"] = "border-image: url(:/images/images/Level 1 - Central Square/Dresiarz.png) 0 0 0 0 stretch stretch;";

    nameToPath["JEZUS CHYTRUS"] = "border-image: url(:/images/images/Level 2 - Pilica River/Jezus.png) 0 0 0 0 stretch stretch;";
    nameToPath["WŚCIEKŁY PIES"] = "border-image: url(:/images/images/Level 2 - Pilica River/WscieklyPies.png) 0 0 0 0 stretch stretch;";

    nameToPath["BYDLĘCE SIŁY ZBROJNE"] = "border-image: url(:/images/images/Level 3 - Kurzelow/BydleceSilyZbrojne.png) 0 0 0 0 stretch stretch;";
    nameToPath["JAN BROŻEK"] = "border-image: url(:/images/images/Level 3 - Kurzelow/JanBrozek.png) 0 0 0 0 stretch stretch;";
    nameToPath["ADAM Z KURZELOWA"] = "border-image: url(:/images/images/Level 3 - Kurzelow/AdamZKurzelowa.png) 0 0 0 0 stretch stretch;";
    nameToPath["ADAM CZARNY"] = "border-image: url(:/images/images/Level 3 - Kurzelow/AdamCzarny.png) 0 0 0 0 stretch stretch;";
    nameToPath["MR BALLSAMAN"] = "border-image: url(:/images/images/Level 3 - Kurzelow/MrBallsamn.png) 0 0 0 0 stretch stretch;";
    nameToPath["COOLA MINECRAFT OFFICIAL"] = "border-image: url(:/images/images/Level 3 - Kurzelow/CoolaMinecraftOfficial.png) 0 0 0 0 stretch stretch;";

    nameToPath["MIESZKANIEC OGRODOWEJ"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/MieszkaniecOgrodowej.png) 0 0 0 0 stretch stretch;";
    nameToPath["RZEPON"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/Rzepon.png) 0 0 0 0 stretch stretch;";
    nameToPath["BORÓWA"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/Borowa.png) 0 0 0 0 stretch stretch;";
    nameToPath["POTĘŻNA BORÓWA"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/PoteznaBorowa.png) 0 0 0 0 stretch stretch;";

    nameToPath["POTĘŻNY MAT-FIZ"] = "border-image: url(:/images/images/Level 5 - Central Square Again/PoteznyMatfiz.png) 0 0 0 0 stretch stretch;";

    nameToPath["DUCH ŻYDA"] = "border-image: url(:/images/images/Level 6 - Underworld/DuchZyda.png) 0 0 0 0 stretch stretch;";
    nameToPath["DUCHY ŻYDÓW"] = "border-image: url(:/images/images/Level 6 - Underworld/DuchyZydow.png) 0 0 0 0 stretch stretch;";
    nameToPath["JACEK JAWOREK"] = "border-image: url(:/images/images/Level 6 - Underworld/JacekJaworek.png) 0 0 0 0 stretch stretch;";

    nameToPath["ALPHA"] = "border-image: url(:/images/images/Level 7 - Wiejska/Alpha.png) 0 0 0 0 stretch stretch;";
    nameToPath["OMEGA"] = "border-image: url(:/images/images/Level 7 - Wiejska/Omega.png) 0 0 0 0 stretch stretch;";
    nameToPath["JĘDRZEJ"] = "border-image: url(:/images/images/Level 7 - Wiejska/Jedrzej.png) 0 0 0 0 stretch stretch;";
    nameToPath["SEZY"] = "border-image: url(:/images/images/Level 7 - Wiejska/Sezy.png) 0 0 0 0 stretch stretch;";
    nameToPath["MIESZKAŃCY WIEJSKIEJ"] = "border-image: url(:/images/images/Level 7 - Wiejska/MieszkancyWiejskiej.png) 0 0 0 0 stretch stretch;";
    nameToPath["REZYDENCI WIEJSKIEJ"] = "border-image: url(:/images/images/Level 7 - Wiejska/MieszkancyWiejskiej_2.png) 0 0 0 0 stretch stretch;";
    nameToPath["SENIOR HISZPANEK"] = "border-image: url(:/images/images/Level 7 - Wiejska/SeniorHiszpanek.png) 0 0 0 0 stretch stretch;";

    nameToPath["DAPO"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Dapo.png) 0 0 0 0 stretch stretch;";
    nameToPath["KSIĄDZ PAWEŁ"] = "border-image: url(:/images/images/Level 8 - Sikorski High/KsiadzPawel.png) 0 0 0 0 stretch stretch;";
    nameToPath["FORBIDDEN LOVERS"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Monika&Marczu.png) 0 0 0 0 stretch stretch;";
    nameToPath["PANI DEJA"] = "border-image: url(:/images/images/Level 8 - Sikorski High/PaniDeja.png) 0 0 0 0 stretch stretch;";
    nameToPath["PANI JADZIA"] = "border-image: url(:/images/images/Level 8 - Sikorski High/PaniJadzia.png) 0 0 0 0 stretch stretch;";
    nameToPath["BUSZER"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Tosia.png) 0 0 0 0 stretch stretch;";
    nameToPath["BUSZ DRAGON"] = "border-image: url(:/images/images/Level 8 - Sikorski High/BuszDragon.png) 0 0 0 0 stretch stretch;";
    nameToPath["BOŻENKA"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Bozenka.png) 0 0 0 0 stretch stretch;";
    nameToPath["BOŻENKUS"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Bozenkus.png) 0 0 0 0 stretch stretch;";

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
    heroShield = 0;
    heroReflectionRate = 0;
    heroCritRate = 0;
    heroHealRate = 0;
    shieldOn = false;
    shieldBroken = false;

    enemyAttack = -1;
    enemyDefense = -1;
    enemyHealth = -1;
    enemyMaxHealth = -1;

    wealth = 0;

    weaponLevel = 0;
    shieldLevel = 0;
    healthLevel = 0;

    weaponPrice = 100 * weaponLevel * weaponLevel * cbrt(weaponLevel) + 100;
    shieldPrice = 90 * shieldLevel * shieldLevel * cbrt(shieldLevel) + 90;
    healthPrice = 120 * healthLevel * healthLevel * cbrt(healthLevel) + 120;
    blahajPrice = 10000;
    manulPrice = 50000;
    drPieprzerPrice = 100000;

    blahajOwned = false;
    manulOwned = false;
    drPieprzerOwned = false;

    loadVariables();

    connectShop();

    level1MainFunction();
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::loadVariables()
{
    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 1 - Central Square/Level1Background.png) 0 0 0 0 stretch stretch;"
                        "}");
    ui->heroAttackPointsLabel->setText(QString::number(heroAttack, 10));
    ui->heroDefensePointsLabel->setText(QString::number(heroDefense, 10));
    ui->heroHealthPointsLabel->setText(QString::number(heroHealth, 10));
    ui->heroHealthBar->setMaximum(heroMaxHealth);
    ui->heroHealthBar->setValue(heroHealth);

    ui->enemyAttackPointsLabel->setText("-");
    ui->enemyDefensePointsLabel->setText("-");
    ui->enemyHealthPointsLabel->setText("-");
    ui->enemyHealthBar->setMaximum(1);
    ui->enemyHealthBar->setValue(0);

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

    ui->keychainLabel->setStyleSheet("background-color: rgba(20,20,20,100);"
                                     "border-image: url(:/images/images/AppScreenArt/keychain.png) 0 0 0 0 stretch stretch;");
    ui->keyLabel->setStyleSheet("background-color: rgba(20,20,20,100);"
                                "border-image: url(:/images/images/AppScreenArt/kays.png) 0 0 0 0 stretch stretch;");
    ui->idLabel->setStyleSheet("background-color: rgba(20,20,20,100);"
                               "border-image: url(:/images/images/AppScreenArt/id.png) 0 0 0 0 stretch stretch;");
    ui->moneyLabel->setStyleSheet("background-color: rgba(20,20,20,100);"
                                  "border-image: url(:/images/images/AppScreenArt/wallet.png) 0 0 0 0 stretch stretch;");

    ui->firstActionBox->setEnabled(false);
    ui->secondActionBox->setEnabled(false);
    ui->thirdActionBox->setEnabled(false);
    ui->fourthActionBox->setEnabled(false);
    ui->fifthActionBox->setEnabled(false);

    deadEnemy = new DeadEnemyWidget(this);
    deadHero = new DeadHeroWidget(this);
    tutorialWidget = new TutorialInfo(this);
    QVBoxLayout *vertical = qobject_cast<QVBoxLayout*>(ui->enemyWidget->layout());
    vertical->insertWidget(0,deadEnemy,6);
    vertical->insertWidget(1,deadHero,6);
    vertical->insertWidget(2,tutorialWidget,6);
    deadEnemy->hide();
    deadHero->hide();
    tutorialWidget->hide();
    ui->confirmButton->hide();
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
    showTutorial();
    connect(tutorialWidget, &TutorialInfo::endTutorial, this, [this]() {
        tutorialWidget->hide();
        delete tutorialWidget;
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        enemyType = 0;
        drawEnemy(enemyType);
        dialogs = new QString[2];
        if (sex == 0)
            dialogs[0] = "PODRÓŻNICZKA";
        if (sex == 1)
            dialogs[0] = "PODRÓŻNIK";
        dialogs[1] = "???";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 1 - Central Square/RozmowaZMenelem.txt", 10);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 1 - Central Square/RozmowaZMenelem.txt", 10);
        connectionHub(true, 10);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            fight();
            disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        });
    });

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        drawEnemy(enemyType);
        fight();
    });

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]() {
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        enemyType++;
        drawEnemy(enemyType);
        dialogs = new QString[2];
        if (sex == 0)
            dialogs[0] = "PODRÓŻNICZKA";
        if (sex == 1)
            dialogs[0] = "PODRÓŻNIK";
        dialogs[1] = "Hm? Powietrze dziwnie pachnie. Czy to...";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 1 - Central Square/RozmowaZDresem.txt", 16);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 1 - Central Square/RozmowaZDresem.txt", 16);
        connectionHub(true, 16);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            fight();
            disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        });
        connect(this, &GameScreen::heroKilled, this, &GameScreen::endSceneAndPostLevelCleanup);
    });
}

void GameScreen::showTutorial()
{
    ui->attackActionButton->setEnabled(false);
    ui->defenseActionButton->setEnabled(false);
    ui->healActionButton->setEnabled(false);
    ui->continueButton->setEnabled(false);
    ui->infoAboutActionLabel->setText("");
    ui->enemyLabel->hide();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    tutorialWidget->show();
}

void GameScreen::endSceneAndPostLevelCleanup()
{
    //DISCONNECTIONS
    disconnect(tutorialWidget, &TutorialInfo::endTutorial, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(this, &GameScreen::heroKilled, nullptr, nullptr);

    //LOAD END SCENE
    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "AAAAA!!!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 1 - Central Square/RozmowaZDresem_2.txt", 16);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 1 - Central Square/RozmowaZDresem_2.txt", 16);
    connectionHub(true, 16);

    //TRANSITION TO LEVEL 2
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->keychainLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        ui->keyLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        ui->idLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        ui->moneyLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        fadeAwayAnimation(this, 2000);
        gameLevel++;
        level2MainFunction();
    });
}

void GameScreen::level2MainFunction()
{
    //fadeInAnimation(this, 2000);
}

//SHOP
void GameScreen::connectShop()
{
    connect(ui->weaponShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyWeapon);
    connect(ui->shieldShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyShield);
    connect(ui->healthShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyHealth);
    connect(ui->blahajShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyBlahaj);
    connect(ui->manulShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyManul);
    connect(ui->drPieprzerShopWidget, &QClickableWidget::clicked, this, &GameScreen::userWantsToBuyDrPieprzer);
}
void GameScreen::disconnectShop()
{
    disconnect(ui->weaponShopWidget, &QClickableWidget::clicked, nullptr, nullptr);
    disconnect(ui->shieldShopWidget, &QClickableWidget::clicked, nullptr, nullptr);
    disconnect(ui->healthShopWidget, &QClickableWidget::clicked, nullptr, nullptr);
    disconnect(ui->blahajShopWidget, &QClickableWidget::clicked, nullptr, nullptr);
    disconnect(ui->manulShopWidget, &QClickableWidget::clicked, nullptr, nullptr);
    disconnect(ui->drPieprzerShopWidget, &QClickableWidget::clicked, nullptr, nullptr);
}

void GameScreen::userWantsToBuyWeapon()
{
    disconnectShop();
    if (wealth >= weaponPrice)
    {
        wealth -= weaponPrice;
        weaponLevel++;
        if (sex == 0)
            heroAttack += weaponLevel * 5;
        if (sex == 1)
            heroAttack += weaponLevel * 7;
        if (weaponLevel * 3 <= 75)
            heroCritRate = 3 * weaponLevel;
        else if (weaponLevel * 3 > 75)
            heroCritRate = 75;
        weaponPrice = 100 * weaponLevel * weaponLevel * cbrt(weaponLevel) + 100;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
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
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 6 && weaponLevel <= 10)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 11 && weaponLevel <= 15)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass3.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 16 && weaponLevel <= 20)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass4.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 21 && weaponLevel <= 25)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass5.png) 0 0 0 0 stretch stretch;");

        ui->heroAttackPointsLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16px;");

        delay(500);

        ui->heroAttackPointsLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16px;");
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
    connectShop();
}
void GameScreen::userWantsToBuyShield()
{
    disconnectShop();
    if (wealth >= shieldPrice)
    {
        wealth -= shieldPrice;
        shieldLevel++;
        heroDefense += shieldLevel * 5;
        if (shieldLevel * 3 <= 75)
            heroReflectionRate = 3 * shieldLevel;
        else if (shieldLevel * 3 > 75)
            heroReflectionRate = 75;
        shieldPrice = 90 * shieldLevel * shieldLevel * cbrt(shieldLevel) + 90;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
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
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 6 && shieldLevel <= 10)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 11 && shieldLevel <= 15)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 16 && shieldLevel <= 20)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 21 && shieldLevel <= 25)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass5.png) 0 0 0 0 stretch stretch;");

        ui->heroDefensePointsLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16px;");

        delay(500);

        ui->heroDefensePointsLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16px;");
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
    connectShop();
}
void GameScreen::userWantsToBuyHealth()
{
    disconnectShop();
    if (wealth >= healthPrice)
    {
        wealth -= healthPrice;
        healthLevel++;
        if (sex == 0)
            heroMaxHealth += healthLevel * 12;
        if (sex == 1)
            heroMaxHealth += healthLevel * 10;
        heroHealth = heroMaxHealth;
        if (healthLevel * 3 <= 75)
            heroHealRate = 3 * healthLevel;
        else if (healthLevel * 3 > 75)
            heroHealRate = 75;
        healthPrice = 120 * healthLevel * healthLevel * cbrt(healthLevel) + 120;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
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
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 6 && healthLevel <= 10)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 11 && healthLevel <= 15)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 16 && healthLevel <= 20)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 21 && healthLevel <= 25)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass5.png) 0 0 0 0 stretch stretch;");

        ui->heroHealthBar->setMaximum(heroMaxHealth);
        ui->heroHealthBar->setValue(heroMaxHealth);

        ui->heroHealthPointsLabel->setStyleSheet("color: rgb(10,150,0); font-size: 16px;");

        delay(500);

        ui->heroHealthPointsLabel->setStyleSheet("color: rgb(180, 180, 180); font-size: 16px;");
    }
    else
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
    connectShop();
}
void GameScreen::userWantsToBuyBlahaj()
{
    disconnectShop();
    if (wealth >= blahajPrice && blahajOwned == false)
    {
        wealth -= blahajPrice;
        ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
        blahajOwned = true;
        ui->blahajSlotLabel->setStyleSheet("border-image: url(:/images/images/Shop - Special/Blahaj.png) 0 0 0 0 stretch stretch;");
        ui->blahajShopLabel->setText("KUPIONO");
        ui->blahajShopPriceLabel->setText("---");
        ui->blahajShopLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: rgb(180,180,180);");
    }
    else if (wealth < blahajPrice)
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
    connectShop();
}
void GameScreen::userWantsToBuyManul()
{
    disconnectShop();
    if (wealth >= manulPrice && manulOwned == false)
    {
        wealth -= manulPrice;
        ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
        manulOwned = true;
        ui->manulSlotLabel->setStyleSheet("border-image: url(:/images/images/Shop - Special/Manul.png) 0 0 0 0 stretch stretch;");
        ui->manulShopLabel->setText("KUPIONO");
        ui->manulShopPriceLabel->setText("---");
        ui->manulShopLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: rgb(180,180,180);");
    }
    else if (wealth < manulPrice)
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
    connectShop();
}
void GameScreen::userWantsToBuyDrPieprzer()
{
    disconnectShop();
    if (wealth >= drPieprzerPrice && drPieprzerOwned == false)
    {
        wealth -= drPieprzerPrice;
        ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
        drPieprzerOwned = true;
        ui->drPieprzerSlotLabel->setStyleSheet("border-image: url(:/images/images/Shop - Special/DrPieprzer.png) 0 0 0 0 stretch stretch;");
        ui->drPieprzerShopLabel->setText("KUPIONO");
        ui->drPieprzerShopPriceLabel->setText("---");
        ui->drPieprzerShopLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: rgb(180,180,180);");
    }
    else if (wealth < drPieprzerPrice)
    {
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
        delay(500);
        ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    }
    connectShop();
}

//FIGHT
void GameScreen::drawEnemy(int whatToDraw)
{
    switch (gameLevel)
    {
    case 1:
        if (whatToDraw == 0)
            enemyType = 0;
        if (whatToDraw == 1)
            enemyType = 1;
        if (whatToDraw == -1)
            enemyType = rand() % 2;

        if (enemyType == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Bezdomny.png) 0 0 0 0 stretch stretch;");
            enemyAttack = 10;
            enemyDefense = 40;
            enemyHealth = 80;
            enemyMaxHealth = 80;
        }
        if (enemyType == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Dresiarz.png) 0 0 0 0 stretch stretch;");
            enemyAttack = 30;
            enemyDefense = 40;
            enemyHealth = 100;
            enemyMaxHealth = 100;
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
    ui->enemyAttackPointsLabel->setText(QString::number(enemyAttack));
    ui->enemyDefensePointsLabel->setText(QString::number(enemyDefense));
    ui->enemyHealthPointsLabel->setText(QString::number(enemyMaxHealth));
    ui->enemyHealthBar->setMinimum(0);
    ui->enemyHealthBar->setMaximum(enemyMaxHealth);
    ui->enemyHealthBar->setValue(enemyHealth);
}
void GameScreen::fight()
{
    disconnectShop();
    ui->continueButton->hide();
    if (numberOfRounds % 2 == 0)
    {
        ui->infoAboutActionLabel->setText("TWOJA TURA");
        ui->infoAboutActionLabel->setAlignment(Qt::AlignCenter);
        ui->infoAboutActionLabel->setStyleSheet("color: rgb(180,180,180);"
                                                "font-size: 36px;");
        ui->confirmButton->hide();
        ui->attackActionButton->setEnabled(true);
        ui->defenseActionButton->setEnabled(false);
        ui->healActionButton->setEnabled(false);
        if (actionPoints >= 1)
            ui->defenseActionButton->setEnabled(true);
        if (actionPoints >= 3)
            ui->healActionButton->setEnabled(true);
        return;
    }
    if (numberOfRounds % 2 == 1)
    {
        delay(200);
        ui->infoAboutActionLabel->setText("TURA PRZECIWNIKA");
        ui->infoAboutActionLabel->setAlignment(Qt::AlignCenter);
        ui->infoAboutActionLabel->setStyleSheet("color: rgb(180,180,180);"
                                                "font-size: 36px;");
        delay(200);
        int enemyBaseDamage = 0;
        enemyBaseDamage = floor(static_cast<double>(enemyAttack) *
                                (1 + static_cast<double>(enemyAttack) / static_cast<double>(heroDefense)));

        int enemyRealDamage = rand() % static_cast<int>(0.4*enemyBaseDamage + 1) + static_cast<int>(0.8*enemyBaseDamage);

        if (shieldOn == true && heroShield > enemyRealDamage)
        {
            heroShield -= enemyRealDamage;
            ui->heroHealthBar->setValue(heroShield);
        }
        else if (shieldOn == true && heroShield <= enemyRealDamage)
        {
            int remnants = enemyRealDamage - heroShield;
            heroShield = 0;
            ui->heroHealthBar->setValue(0);
            shieldBroken = true;
            delay(150);
            ui->heroHealthBar->setMaximum(heroMaxHealth);
            ui->heroHealthBar->setValue(heroHealth);
            ui->heroHealthBar->setStyleSheet("#heroHealthBar {"
                                             "color: rgb(180,180,180);"
                                             "background-color: rgb(100,200,100);"
                                             "text-align: center;"
                                             "font-size: 24px;"
                                             "}"
                                             "#heroHealthBar::chunk {"
                                             "background-color: rgb(10,150,0);"
                                             "}");
            delay(150);
            if (heroHealth > remnants)
            {
                heroHealth -= remnants;
                ui->heroHealthBar->setValue(heroHealth);
            }
            else if (heroHealth <= remnants)
            {
                heroHealth = 0;
                ui->heroHealthBar->setValue(0);
                heroIsDead();
                emit heroKilled();
            }
        }
        else if (shieldOn == false && heroHealth > enemyRealDamage)
        {
            heroHealth -= enemyRealDamage;
            ui->heroHealthBar->setValue(heroHealth);
        }
        else if (shieldOn == false && heroHealth <= enemyRealDamage)
        {
            heroHealth = 0;
            ui->heroHealthBar->setValue(heroHealth);
            heroIsDead();
            emit heroKilled();
            return;
        }
        delay(200);
        ui->dialogLabel->setText("");
        numberOfRounds++;
        if (shieldBroken == true && heroHealth == 0)
        {
            shieldOn = false;
            shieldBroken = false;
            ui->heroHealthBar->setMaximum(heroMaxHealth);
            ui->heroHealthBar->setValue(heroHealth);
            ui->heroHealthBar->setStyleSheet("#heroHealthBar {"
                                             "color: rgb(180,180,180);"
                                             "background-color: rgb(100,200,100);"
                                             "text-align: center;"
                                             "font-size: 24px;"
                                             "}"
                                             "#heroHealthBar::chunk {"
                                             "background-color: rgb(10,150,0);"
                                             "}");
            return;
        }
        fight();
    }
    if (shieldBroken == true)
    {
        shieldOn = false;
        ui->heroHealthBar->setMaximum(heroMaxHealth);
        ui->heroHealthBar->setValue(heroHealth);
        ui->heroHealthBar->setStyleSheet("#heroHealthBar {"
                                         "color: rgb(180,180,180);"
                                         "background-color: rgb(100,200,100);"
                                         "text-align: center;"
                                         "font-size: 24px;"
                                         "}"
                                         "#heroHealthBar::chunk {"
                                         "background-color: rgb(10,150,0);"
                                         "}");
        return;
    }
}

void GameScreen::heroIsDead()
{
    ui->enemyLabel->hide();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    deadHero->show();
    connectShop();
}
void GameScreen::enemyIsDead()
{
    ui->enemyLabel->hide();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    deadEnemy->show();
    int loot = gameLevel * (enemyType + 1) * 25;
    wealth += loot;
    ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
    ui->amountOfMoneyLabel->setStyleSheet("color: rgb(10,150,0); font-size: 20px;");
    delay(500);
    ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    connectShop();
}

void GameScreen::on_attackActionButton_clicked()
{
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroDefends);
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroHealsHimself);

    int baseDamage = floor(static_cast<double>(heroAttack) * (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));

    ui->infoAboutActionLabel->setText("Obrażenia: " + QString::number(static_cast<int>(0.8 * baseDamage)) + " - " +
                                      QString::number(static_cast<int>(1.2 * baseDamage)) + '\n' + "Szansa na atak krytyczny: " +
                                      QString::number(heroCritRate) + "%");
    ui->infoAboutActionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->infoAboutActionLabel->setStyleSheet("color: rgb(180,180,180);"
                                            "font-size: 20px;");
    ui->confirmButton->show();
    connect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroAttacks);
}
void GameScreen::on_defenseActionButton_clicked()
{
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroAttacks);
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroHealsHimself);

    ui->infoAboutActionLabel->setText("Uzyskiwana tarcza: " + QString::number(heroDefense*1.6) + " - " + QString::number(heroDefense*2.4)
                                      + "\nSzansa na odbicie: " + QString::number(heroReflectionRate) + "%");
    ui->infoAboutActionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->infoAboutActionLabel->setStyleSheet("color: rgb(180,180,180);"
                                            "font-size: 20px;");
    ui->confirmButton->show();
    connect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroDefends);
}
void GameScreen::on_healActionButton_clicked()
{
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroAttacks);
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroDefends);

    int baseDamage = floor(static_cast<double>(heroAttack) * (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));

    ui->infoAboutActionLabel->setText("Obrażenia: " + QString::number(static_cast<int>(1.2*baseDamage)) +
                                      " - " + QString::number(static_cast<int>(1.8*baseDamage)) + '\n' + "Odzyskane życie: " +
                                      QString::number(heroHealRate) + "% obrażeń");
    ui->infoAboutActionLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->infoAboutActionLabel->setStyleSheet("color: rgb(180,180,180);"
                                            "font-size: 20px;");
    ui->confirmButton->show();
    connect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroHealsHimself);
}

void GameScreen::heroAttacks()
{
    numberOfRounds++;
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroAttacks);
    ui->attackActionButton->setEnabled(false);
    ui->defenseActionButton->setEnabled(false);
    ui->healActionButton->setEnabled(false);

    int baseDamage = floor(static_cast<double>(heroAttack) * (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));
    int realDamage = rand() % static_cast<int>(0.4*baseDamage + 1) + static_cast<int>(0.8*baseDamage);
    bool isItCrit = false;

    if (rand() % 100 + 1 < heroCritRate)
    {
        isItCrit = true;
        realDamage *= 1.5;
    }

    ui->infoAboutActionLabel->setText("");
    ui->confirmButton->hide();
    delay(150);
    if (isItCrit == false)
        ui->dialogLabel->setText("ZADAJESZ: " + QString::number(realDamage, 10));
    else if (isItCrit == true)
        ui->dialogLabel->setText("ZADAJESZ: " + QString::number(realDamage, 10) + " OBRAŻEŃ KRYTYCZNYCH");
    if (enemyHealth >= realDamage)
        enemyHealth -= realDamage;
    else if (enemyHealth < realDamage)
        enemyHealth = 0;
    ui->enemyHealthBar->setValue(enemyHealth);
    delay(50);
    if (actionPoints < 5)
    {
        actionPoints++;
        updateActionPointsButtons();
    }
    if (enemyHealth == 0)
    {
        enemyIsDead();
        return;
    }
    fight();
}
void GameScreen::heroDefends()
{
    numberOfRounds++;
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroDefends);
    ui->attackActionButton->setEnabled(false);
    ui->defenseActionButton->setEnabled(false);
    ui->healActionButton->setEnabled(false);

    shieldOn = true;
    shieldBroken = false;
    actionPoints--;
    updateActionPointsButtons();

    ui->infoAboutActionLabel->setText("");
    ui->confirmButton->hide();
    delay(1500);

    heroShield = rand() % static_cast<int>(0.8 * heroDefense + 1) + static_cast<int>(1.6 * heroDefense);
    ui->dialogLabel->setText("OTRZYMUJESZ: " + QString::number(heroShield) + " punktów tarczy.");
    ui->heroHealthBar->setMaximum(heroShield);
    ui->heroHealthBar->setValue(heroShield);
    ui->heroHealthBar->setStyleSheet("#heroHealthBar {"
                                     "color: rgb(180,180,180);"
                                     "background-color: rgb(80, 150, 255);"
                                     "text-align: center;"
                                     "font-size: 24px;"
                                     "}"
                                     "#heroHealthBar::chunk {"
                                     "background-color: rgb(0, 90, 210);"
                                     "}");
    delay(500);
    fight();
}
void GameScreen::heroHealsHimself()
{
    numberOfRounds++;
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroHealsHimself);
    ui->attackActionButton->setEnabled(false);
    ui->defenseActionButton->setEnabled(false);
    ui->healActionButton->setEnabled(false);

    actionPoints -= 3;
    updateActionPointsButtons();

    ui->infoAboutActionLabel->setText("");
    ui->confirmButton->hide();
    delay(1500);

    int baseDamage = floor(static_cast<double>(heroAttack) * 1.5 *
                           (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));
    int realDamage = rand() % static_cast<int>(0.4*baseDamage + 1) + static_cast<int>(0.8*baseDamage);

    int recoveredHP = (static_cast<double>(heroHealRate) / 100) * realDamage;
    if (heroHealth + recoveredHP <= heroMaxHealth)
        heroHealth += recoveredHP;
    else if (heroHealth + recoveredHP > heroMaxHealth)
        heroHealth = heroMaxHealth;

    if (shieldOn == false)
        ui->heroHealthBar->setValue(heroHealth);

    if (enemyHealth >= realDamage)
        enemyHealth -= realDamage;
    else if (enemyHealth < realDamage)
        enemyHealth = 0;

    ui->enemyHealthBar->setValue(enemyHealth);
    ui->dialogLabel->setText("ZADAJESZ: " + QString::number(realDamage) + " obrażeń krytycznych");
    delay(500);
    fight();
}

void GameScreen::updateActionPointsButtons()
{
    switch (actionPoints)
    {
    case 0:
        if (!ui->firstActionBox->isCheckable())
            ui->firstActionBox->setCheckable(true);
        ui->firstActionBox->setChecked(false);

        if (!ui->secondActionBox->isCheckable())
            ui->secondActionBox->setCheckable(true);
        ui->secondActionBox->setChecked(false);

        if (!ui->thirdActionBox->isCheckable())
            ui->thirdActionBox->setCheckable(true);
        ui->thirdActionBox->setChecked(false);

        if (!ui->fourthActionBox->isCheckable())
            ui->fourthActionBox->setCheckable(true);
        ui->fourthActionBox->setChecked(false);

        if (!ui->fifthActionBox->isCheckable())
            ui->fifthActionBox->setCheckable(true);
        ui->fifthActionBox->setChecked(false);
        break;
    case 1:
        if (!ui->firstActionBox->isCheckable())
            ui->firstActionBox->setCheckable(true);
        ui->firstActionBox->setChecked(true);

        if (!ui->secondActionBox->isCheckable())
            ui->secondActionBox->setCheckable(true);
        ui->secondActionBox->setChecked(false);

        if (!ui->thirdActionBox->isCheckable())
            ui->thirdActionBox->setCheckable(true);
        ui->thirdActionBox->setChecked(false);

        if (!ui->fourthActionBox->isCheckable())
            ui->fourthActionBox->setCheckable(true);
        ui->fourthActionBox->setChecked(false);

        if (!ui->fifthActionBox->isCheckable())
            ui->fifthActionBox->setCheckable(true);
        ui->fifthActionBox->setChecked(false);
        break;
    case 2:
        if (!ui->firstActionBox->isCheckable())
            ui->firstActionBox->setCheckable(true);
        ui->firstActionBox->setChecked(true);

        if (!ui->secondActionBox->isCheckable())
            ui->secondActionBox->setCheckable(true);
        ui->secondActionBox->setChecked(true);

        if (!ui->thirdActionBox->isCheckable())
            ui->thirdActionBox->setCheckable(true);
        ui->thirdActionBox->setChecked(false);

        if (!ui->fourthActionBox->isCheckable())
            ui->fourthActionBox->setCheckable(true);
        ui->fourthActionBox->setChecked(false);

        if (!ui->fifthActionBox->isCheckable())
            ui->fifthActionBox->setCheckable(true);
        ui->fifthActionBox->setChecked(false);
        break;
    case 3:
        if (!ui->firstActionBox->isCheckable())
            ui->firstActionBox->setCheckable(true);
        ui->firstActionBox->setChecked(true);

        if (!ui->secondActionBox->isCheckable())
            ui->secondActionBox->setCheckable(true);
        ui->secondActionBox->setChecked(true);

        if (!ui->thirdActionBox->isCheckable())
            ui->thirdActionBox->setCheckable(true);
        ui->thirdActionBox->setChecked(true);

        if (!ui->fourthActionBox->isCheckable())
            ui->fourthActionBox->setCheckable(true);
        ui->fourthActionBox->setChecked(false);

        if (!ui->fifthActionBox->isCheckable())
            ui->fifthActionBox->setCheckable(true);
        ui->fifthActionBox->setChecked(false);
        break;
    case 4:
        if (!ui->firstActionBox->isCheckable())
            ui->firstActionBox->setCheckable(true);
        ui->firstActionBox->setChecked(true);

        if (!ui->secondActionBox->isCheckable())
            ui->secondActionBox->setCheckable(true);
        ui->secondActionBox->setChecked(true);

        if (!ui->thirdActionBox->isCheckable())
            ui->thirdActionBox->setCheckable(true);
        ui->thirdActionBox->setChecked(true);

        if (!ui->fourthActionBox->isCheckable())
            ui->fourthActionBox->setCheckable(true);
        ui->fourthActionBox->setChecked(true);

        if (!ui->fifthActionBox->isCheckable())
            ui->fifthActionBox->setCheckable(true);
        ui->fifthActionBox->setChecked(false);
        break;
    case 5:
        if (!ui->firstActionBox->isCheckable())
            ui->firstActionBox->setCheckable(true);
        ui->firstActionBox->setChecked(true);

        if (!ui->secondActionBox->isCheckable())
            ui->secondActionBox->setCheckable(true);
        ui->secondActionBox->setChecked(true);

        if (!ui->thirdActionBox->isCheckable())
            ui->thirdActionBox->setCheckable(true);
        ui->thirdActionBox->setChecked(true);

        if (!ui->fourthActionBox->isCheckable())
            ui->fourthActionBox->setCheckable(true);
        ui->fourthActionBox->setChecked(true);

        if (!ui->fifthActionBox->isCheckable())
            ui->fifthActionBox->setCheckable(true);
        ui->fifthActionBox->setChecked(true);
        break;
    default:
        qDebug() << "INCORRECT AMOUNT OF ACTION POINTS";
    }
    ui->firstActionBox->setEnabled(false);
    ui->secondActionBox->setEnabled(false);
    ui->thirdActionBox->setEnabled(false);
    ui->fourthActionBox->setEnabled(false);
    ui->fifthActionBox->setEnabled(false);
}

void GameScreen::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void GameScreen::fadeAwayAnimation(QWidget *widget, int ms)
{
    QGraphicsOpacityEffect *fadeAwayEffect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(fadeAwayEffect);
    QPropertyAnimation *fadeAwayAnimation = new QPropertyAnimation(fadeAwayEffect, "opacity");
    fadeAwayAnimation -> setDuration(ms);
    fadeAwayAnimation -> setStartValue(1);
    fadeAwayAnimation -> setEndValue(0);
    fadeAwayAnimation -> setEasingCurve(QEasingCurve::OutBack);
    fadeAwayAnimation -> start(QPropertyAnimation::DeleteWhenStopped);
    delay(ms);
}
void GameScreen::fadeInAnimation(QWidget *widget, int ms)
{
    QGraphicsOpacityEffect *fadeInEffect = new QGraphicsOpacityEffect(widget);
    widget -> setGraphicsEffect(fadeInEffect);
    QPropertyAnimation *fadeInAnimation = new QPropertyAnimation(fadeInEffect, "opacity");
    fadeInAnimation -> setDuration(ms);
    fadeInAnimation -> setStartValue(0);
    fadeInAnimation -> setEndValue(1);
    fadeInAnimation -> setEasingCurve(QEasingCurve::InBack);
    fadeInAnimation -> start(QPropertyAnimation::DeleteWhenStopped);
    delay(ms);
}

void GameScreen::loadScene(QString pathToDialog, int numOfLines)
{
    QFile dialogFile(pathToDialog);
    dialogs = new QString[numOfLines];
    counterOfLines = 0;
    if (dialogFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&dialogFile);
        while (!in.atEnd())
        {
            *dialogs = in.readLine();
            dialogs++;
        }
        dialogs -= numOfLines;
    }
    else
    {
        qDebug() << "COULD NOT OPEN .TXT FILE!";
        return;
    }
    if (ui->continueButton->isHidden())
        ui->continueButton->show();
    ui->continueButton->setEnabled(true);
}
void GameScreen::showOneDialog(int totalNumOfLines)
{
    ui->continueButton->setEnabled(false);
    QString name = dialogs[counterOfLines];
    QString text = dialogs[counterOfLines + 1];
    QString toShow = "";
    ui->nameLabel->setText(name);
    ui->speakerLabel->setStyleSheet(nameToPath[name]);
    for (int i=0; i<text.length(); i++)
    {
        toShow += text[i];
        ui->dialogLabel->setText(toShow);
        delay(50);
    }
    counterOfLines += 2;

    if (counterOfLines == totalNumOfLines)
    {
        counterOfLines = 0;
        ui->continueButton->setEnabled(false);
        emit sceneEnded();
        connectionHub(false, 0);
        return;
    }
    ui->continueButton->setEnabled(true);
}
void GameScreen::connectionHub(bool cORd, int numOfLines)
{
    if (cORd == true)
        connect(ui->continueButton, &QPushButton::clicked, this, [this, numOfLines]() {showOneDialog(numOfLines);});
    else if (cORd == false)
        disconnect(ui->continueButton, &QPushButton::clicked, nullptr, nullptr);
}

