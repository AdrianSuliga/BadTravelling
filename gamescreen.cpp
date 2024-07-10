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
    gameProgress = 1;
    enemyType = -1;
    numberOfRounds = 0;
    counterOfLines = 0;
    actionPoints = 0;
    nameToPath["..."] = "";
    nameToPath["???"] = "";
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
    nameToPath["MR BALLSMAN"] = "border-image: url(:/images/images/Level 3 - Kurzelow/MrBallsamn.png) 0 0 0 0 stretch stretch;";
    nameToPath["COOLA MINECRAFT OFFICIAL"] = "border-image: url(:/images/images/Level 3 - Kurzelow/CoolaMinecraftOfficial.png) 0 0 0 0 stretch stretch;";

    nameToPath["MIESZKANIEC OGRODOWEJ"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/MieszkaniecOgrodowej.png) 0 0 0 0 stretch stretch;";
    nameToPath["RZEPON"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/Rzepon.png) 0 0 0 0 stretch stretch;";
    nameToPath["BORÓWA"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/Borowa.png) 0 0 0 0 stretch stretch;";
    nameToPath["POTĘŻNA BORÓWA"] = "border-image: url(:/images/images/Level 4 - Ogrodowa/PoteznaBorowa.png) 0 0 0 0 stretch stretch;";

    nameToPath["POTĘŻNY MATFIZ"] = "border-image: url(:/images/images/Level 5 - Central Square Again/PoteznyMatfiz.png) 0 0 0 0 stretch stretch;";
    nameToPath["TRZECI"] = "border-image: url(:/images/images/Level 5 - Central Square Again/Trzeci.png) 0 0 0 0 stretch stretch;";

    nameToPath["DUCH ŻYDA"] = "border-image: url(:/images/images/Level 6 - Underworld/DuchZyda.png) 0 0 0 0 stretch stretch;";
    nameToPath["DUCHY ŻYDÓW"] = "border-image: url(:/images/images/Level 6 - Underworld/DuchyZydow.png) 0 0 0 0 stretch stretch;";
    nameToPath["JACEK JAWOREK"] = "border-image: url(:/images/images/Level 6 - Underworld/JacekJaworek.png) 0 0 0 0 stretch stretch;";

    nameToPath["ALFA"] = "border-image: url(:/images/images/Level 7 - Wiejska/Alpha.png) 0 0 0 0 stretch stretch;";
    nameToPath["OMEGA"] = "border-image: url(:/images/images/Level 7 - Wiejska/Omega.png) 0 0 0 0 stretch stretch;";
    nameToPath["SEZY"] = "border-image: url(:/images/images/Level 7 - Wiejska/Sezy.png) 0 0 0 0 stretch stretch;";
    nameToPath["JĘDRZEJ"] = "border-image: url(:/images/images/Level 7 - Wiejska/Jedrzej.png) 0 0 0 0 stretch stretch;";
    nameToPath["MIESZKAŃCY WIEJSKIEJ"] = "border-image: url(:/images/images/Level 7 - Wiejska/MieszkancyWiejskiej.png) 0 0 0 0 stretch stretch;";
    nameToPath["REZYDENCI WIEJSKIEJ"] = "border-image: url(:/images/images/Level 7 - Wiejska/MieszkancyWiejskiej_2.png) 0 0 0 0 stretch stretch;";
    nameToPath["SENIOR HISZPANEK"] = "border-image: url(:/images/images/Level 7 - Wiejska/SeniorHiszpanek.png) 0 0 0 0 stretch stretch;";

    nameToPath["DAPO"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Dapo.png) 0 0 0 0 stretch stretch;";
    nameToPath["KSIĄDZ PAWEŁ"] = "border-image: url(:/images/images/Level 8 - Sikorski High/KsiadzPawel.png) 0 0 0 0 stretch stretch;";
    nameToPath["FORBIDDEN LOVERS"] = "border-image: url(:/images/images/Level 8 - Sikorski High/MonikaAndMarczu.png) 0 0 0 0 stretch stretch;";
    nameToPath["PANI DEJA"] = "border-image: url(:/images/images/Level 8 - Sikorski High/PaniDeja.png) 0 0 0 0 stretch stretch;";
    nameToPath["PANI JADZIA"] = "border-image: url(:/images/images/Level 8 - Sikorski High/PaniJadzia.png) 0 0 0 0 stretch stretch;";
    nameToPath["BUSZER Z SIKORSKIEGO"] = "border-image: url(:/images/images/Level 8 - Sikorski High/Tosia.png) 0 0 0 0 stretch stretch;";
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
    bossFightOn = false;

    player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);

    curseRemoved = false;
    sezySpared = false;

    enemyAttack = -1;
    enemyDefense = -1;
    enemyHealth = -1;
    enemyMaxHealth = -1;

    wealth = 150000;

    weaponLevel = 0;
    shieldLevel = 0;
    healthLevel = 0;

    weaponPrice = 100 * weaponLevel * weaponLevel * cbrt(weaponLevel) + 100;
    shieldPrice = 90 * shieldLevel * shieldLevel * cbrt(shieldLevel) + 90;
    healthPrice = 120 * healthLevel * healthLevel * cbrt(healthLevel) + 120;
    blahajPrice = 5000;
    manulPrice = 10000;
    drPieprzerPrice = 20000;

    blahajOwned = false;
    manulOwned = false;
    drPieprzerOwned = false;

    loadVariables();

    connectShop();
    level4PostLevelCleanup();
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

    if (weaponLevel >= 0 && weaponLevel <= 2)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 3 && weaponLevel <= 5)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 6 && weaponLevel <= 8)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 9 && weaponLevel <= 11)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
    if (weaponLevel >= 12)
        ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");

    if (shieldLevel >= 0 && shieldLevel <= 2)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 3 && shieldLevel <= 5)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 6 && shieldLevel <= 8)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 9 && shieldLevel <= 11)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
    if (shieldLevel >= 12)
        ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass5.png) 0 0 0 0 stretch stretch;");

    if (healthLevel >= 0 && healthLevel <= 2)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 3 && healthLevel <= 5)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 6 && healthLevel <= 8)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 9 && healthLevel <= 11)
        ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
    if (healthLevel >= 12)
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
    riDialog = new RecoveredItemDialog(this);
    riDialog->setModal(true);
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
void GameScreen::level1FirstFunction()
{
    srand(time(nullptr));
    showTutorial();
    connect(tutorialWidget, &TutorialInfo::endTutorial, this, [this]() {
        tutorialWidget->hide();
        delete tutorialWidget;
        tutorialWidget = nullptr;
        player->setSource(QUrl("qrc:/other/other/Music/MainAmbient.mp3"));
        player->play();
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
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            player->stop();
            player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
            player->play();
            fight();
            disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        });
    });

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
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
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        ++enemyType;
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
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            deadHero->hideResurectButton();
            player->stop();
            player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
            player->play();
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
    //TRANSITION TO LEVEL 2
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->keychainLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        ui->keyLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        ui->idLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        ui->moneyLabel->setStyleSheet("background-color: rgba(20,20,20,100);");
        fadeAwayAnimation(this, 2000);
        level2FirstFunction();
    });
}

//LEVEL 2 - PILICA RIVER
void GameScreen::level2FirstFunction()
{
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 2 - Pilica River/Level2Background1.png) 0 0 0 0 stretch stretch;"
                          "}");
    deadHero->hide();
    deadHero->showResurectButton();
    ui->enemyLabel->show();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    ui->enemyLabel->setStyleSheet("");
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroMaxHealth);
    ui->infoAboutActionLabel->setText("");
    ui->dialogLabel->setText("");
    gameProgress = 0;
    numberOfRounds = 0;
    spawnEnemy(0, 0, 1, 1);
    gameLevel = 2;
    fadeInAnimation(this, 2000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Jezuuu... ała...";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 2 - Pilica River/MonologPoPrzebudzeniu.txt", 16);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 2 - Pilica River/MonologPoPrzebudzeniu.txt", 16);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(-1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]() {
        if (gameProgress == 2)
        {
            player->stop();
            player->setSource(QUrl("qrc:/other/other/Music/MainAmbient.mp3"));
            player->play();
            fadeAwayAnimation(this, 1000);
            delay(1000);
            level2HelperFunction();
            return;
        }
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(-1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        if (enemyType == 2)
            drawEnemy(2);
        else
            drawEnemy(-1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
}
void GameScreen::level2HelperFunction()
{
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);

    deadEnemy->showBossButton();
    deadEnemy->hide();

    ui->enemyLabel->setStyleSheet("");
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    ui->attackActionButton->setEnabled(false);
    ui->defenseActionButton->setEnabled(false);
    ui->healActionButton->setEnabled(false);

    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 2 - Pilica River/Level2Background2.png) 0 0 0 0 stretch stretch;"
                          "}");
    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Okej";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 2 - Pilica River/MonologWTrakcieWalk.txt", 8);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 2 - Pilica River/MonologWTrakcieWalk.txt", 8);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(-1);
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    });
    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]() {
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(-1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
            numberOfRounds = 0;
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroMaxHealth);
            if (enemyType == 2)
                drawEnemy(2);
            else
                drawEnemy(-1);
            player->stop();
            player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
            player->play();
            fight();
        });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {level2BossFight();});
}
void GameScreen::level2BossFight()
{
    fadeAwayAnimation(this, 1000);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);

    deadHero->showGoBackButton();
    deadEnemy->hide();
    deadEnemy->hideBossButton();
    deadEnemy->hideTransitionButton();

    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 2 - Pilica River/Level2Background3.png) 0 0 0 0 stretch stretch;"
                          "}");

    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "*odgłos intensywnego przedzierania się przez busz*";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 2 - Pilica River/RozmowaZJanemPrzedWalka.txt", 26);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 2 - Pilica River/RozmowaZJanemPrzedWalka.txt", 26);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        numberOfRounds=0;
        drawEnemy(2);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/JezusBattleMusic.mp3"));
        player->play();
        fight();
    });
    connect(this, &GameScreen::enemyKilled, this, [this]() {
        dialogs = new QString[2];
        if (sex == 0)
            dialogs[0] = "PODRÓŻNICZKA";
        if (sex == 1)
            dialogs[0] = "PODRÓŻNIK";
        dialogs[1] = "Takiego!";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 2 - Pilica River/RozmowaZJanemPoWalce.txt", 32);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 2 - Pilica River/RozmowaZJanemPoWalce.txt", 32);
        connect(this, &GameScreen::sceneEnded, this, &GameScreen::level2PostLevelCleanup);
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        if (enemyType == 2)
            drawEnemy(2);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/JezusBattleMusic.mp3"));
        player->play();
        fight();
    });
    connect(deadHero, &DeadHeroWidget::goBackToFighting, this, [this](){
        level2RetreatFromBossFunction();
        return;
    });
}
void GameScreen::level2RetreatFromBossFunction()
{
    fadeAwayAnimation(this, 1000);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);

    deadEnemy->showBossButton();
    deadEnemy->showTransitionButton();
    deadEnemy->hide();
    deadHero->hide();
    numberOfRounds = 0;
    heroHealth=heroMaxHealth;
    ui->heroHealthBar->setValue(heroMaxHealth);

    ui->enemyLabel->setStyleSheet("");
    ui->attackActionButton->setEnabled(false);
    ui->defenseActionButton->setEnabled(false);
    ui->healActionButton->setEnabled(false);

    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 2 - Pilica River/Level2Background2.png) 0 0 0 0 stretch stretch;"
                          "}");
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    drawEnemy(-1);
    fadeInAnimation(this, 1000);
    player->stop();
    player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
    player->play();
    fight();

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]() {
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(-1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {level2BossFight();});
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
            numberOfRounds = 0;
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroMaxHealth);
            if (enemyType == 2)
                drawEnemy(2);
            else
                drawEnemy(-1);
            player->stop();
            player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
            player->play();
            fight();
        });
}
void GameScreen::level2PostLevelCleanup()
{
    fadeAwayAnimation(this, 2000);

    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::heroKilled, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::fightBoss, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::goBackToFighting, nullptr, nullptr);

    deadEnemy->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    ui->enemyLabel->setStyleSheet("");
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroMaxHealth);
    ui->infoAboutActionLabel->setText("");
    ui->dialogLabel->setText("");
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    gameProgress = 0;
    numberOfRounds = 0;
    spawnEnemy(0, 0, 1, 1);
    actionPoints = 0;
    updateActionPointsButtons();
    gameLevel = 3;

    level3FirstFunction();
}

//LEVEL 3 - KURZELÓW
void GameScreen::level3FirstFunction()
{
    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 3 - Kurzelow/Level3Background1.png) 0 0 0 0 stretch stretch;"
                          "}");
    deadEnemy->showTransitionButton();
    fadeInAnimation(this, 2000);
    changeMusic("qrc:/other/other/Music/MainAmbient.mp3");

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "WOW!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/MonologPoPrzybyciu.txt", 12);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/MonologPoPrzybyciu.txt", 12);

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
        numberOfRounds = 0;
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(0);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });

    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/MonologPoPrzybyciu_2.txt", 16);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/MonologPoPrzybyciu_2.txt", 16);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            drawEnemy(0);
            player->stop();
            player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
            player->play();
            fight();
            connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]() {
                numberOfRounds = 0;
                heroHealth = heroMaxHealth;
                ui->heroHealthBar->setValue(heroHealth);
                deadEnemy->hide();
                ui->enemyLabel->show();
                ui->enemyStatWidget->show();
                ui->enemyHealthBar->show();
                drawEnemy(0);
                player->stop();
                player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
                player->play();
                fight();
            });
            connect(this, &GameScreen::enemyKilled, this, [this]() {
                if (gameProgress == 3)
                {
                    fadeAwayAnimation(this, 1000);
                    this->setStyleSheet("#GameScreen {"
                                        "border-image: url(:/images/images/Level 3 - Kurzelow/Level3Background2.png) 0 0 0 0 stretch stretch;"
                                        "}");
                    fadeInAnimation(this, 1000);
                    dialogs = new QString[2];
                    if (sex == 0)
                        dialogs[0] = "PODRÓŻNICZKA";
                    if (sex == 1)
                        dialogs[0] = "PODRÓŻNIK";
                    dialogs[1] = "Nie ma im końca...";
                    showOneDialog(2);
                    delete[] dialogs;
                    dialogs = nullptr;

                }
                if (gameProgress == 6)
                {
                    deadEnemy->hide();
                    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
                    deadEnemy->hideTransitionButton();
                    level3HelperFunction();
                    return;
                }
            });
        });
    });
}
void GameScreen::level3HelperFunction()
{
    fadeAwayAnimation(this, 1000);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 3 - Kurzelow/Level3Background3.png) 0 0 0 0 stretch stretch;"
                        "}");
    fadeInAnimation(this, 1000);
    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Ile tu bydła...";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/RozmowaZBrozkiemPoZabiciuKrow.txt", 54);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/RozmowaZBrozkiemPoZabiciuKrow.txt", 54);

    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            dialogs = new QString[2];
            dialogs[0] = "JAN BROŻEK";
            dialogs[1] = "Nareszcie... spokój... jebać Kurzelów";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/RozmowaZAdamemPrzedWalka.txt", 22);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/RozmowaZAdamemPrzedWalka.txt", 22);
            connect(this, &GameScreen::sceneEnded, this, &GameScreen::level3BossFight);
        });
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(1);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
}
void GameScreen::level3BossFight()
{
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    gameProgress = 2;
    bossFightOn = true;

    deadHero->showGoBackButton();
    deadEnemy->hideBossButton();
    deadEnemy->hideTransitionButton();

    deadEnemy->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    numberOfRounds = 0;
    drawEnemy(2);
    changeMusic("qrc:/other/other/Music/AdamBattleMusic.mp3");
    fight();

    connect(this, &GameScreen::enemyKilled, this, [this] {
        switch(gameProgress)
        {
        case 3:
            dialogs = new QString[2];
            if (sex == 0)
                dialogs[0] = "PODRÓŻNICZKA";
            if (sex == 1)
                dialogs[0] = "PODRÓŻNIK";
            dialogs[1] = "Załatwiony!";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/PrzejscieDoAdamaCzarnego.txt", 8);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/PrzejscieDoAdamaCzarnego.txt", 8);
            break;
        case 4:
            dialogs = new QString[2];
            dialogs[0] = "ADAM CZARNY";
            dialogs[1] = "Czymże jest życie bez odrobiny ryzyka... *umiera*";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/PrzejscieDoMrBallsmana.txt", 12);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/PrzejscieDoMrBallsmana.txt", 12);
            break;
        case 5:
            dialogs = new QString[2];
            if (sex == 0)
                dialogs[0] = "PODRÓŻNICZKA";
            if (sex == 1)
                dialogs[0] = "PODRÓŻNIK";
            dialogs[1] = "To jeszcze nie koniec... czuję to";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/PrzejscieDoCoolaMinecraftOfficial.txt", 8);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/PrzejscieDoCoolaMinecraftOfficial.txt", 8);
            break;
        case 6:
            dialogs = new QString[2];
            if (sex == 0)
                dialogs[0] = "PODRÓŻNICZKA";
            if (sex == 1)
                dialogs[0] = "PODRÓŻNIK";
            dialogs[1] = "Nie wierzę...";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 3 - Kurzelow/RozmowaZAdamemPoWalce.txt", 40);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 3 - Kurzelow/RozmowaZAdamemPoWalce.txt", 40);
        }
    });
    connect(this, &GameScreen::sceneEnded, this, [this] {
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        switch(gameProgress)
        {
        case 3:
        case 4:
        case 5:
            drawEnemy(gameProgress);
            break;
        case 6:
            player->stop();
            riDialog->show();
            riDialog->setIcon(0);
            ui->enemyLabel->setStyleSheet("");
            ui->enemyStatWidget->hide();
            ui->enemyHealthBar->hide();
            ui->keychainLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/keychain.png) 0 0 0 0 stretch stretch;");
            connect(riDialog, &RecoveredItemDialog::acceptMessage, this, &GameScreen::level3PostLevelCleanup);
            return;
        }
        fight();
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this] {
        numberOfRounds = 0;
        gameProgress = 2;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(gameProgress);
        fight();
    });
    connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level3RetreatFromBossFunction);
}
void GameScreen::level3RetreatFromBossFunction()
{
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);

    fadeAwayAnimation(this, 1000);
    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 3 - Kurzelow/Level3Background1.png) 0 0 0 0 stretch stretch;"
                        "}");
    ui->enemyLabel->setStyleSheet("");
    ui->enemyHealthBar->setValue(enemyMaxHealth);
    deadHero->hide();
    fadeInAnimation(this, 1000);
    numberOfRounds = 0;
    deadEnemy->showBossButton();
    deadEnemy->showTransitionButton();
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    drawEnemy(0);
    player->stop();
    player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
    player->play();
    fight();

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(0);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {
        fadeAwayAnimation(this, 1000);
        this->setStyleSheet("#GameScreen {"
                            "border-image: url(:/images/images/Level 3 - Kurzelow/Level3Background3.png) 0 0 0 0 stretch stretch;"
                            "}");
        deadEnemy->hide();
        fadeInAnimation(this, 1000);
        level3BossFight();
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(0);
        player->stop();
        player->setSource(QUrl("qrc:/other/other/Music/MainBattleMusic.mp3"));
        player->play();
        fight();
    });
}
void GameScreen::level3PostLevelCleanup()
{
    riDialog->hide();
    fadeAwayAnimation(this, 2000);

    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::heroKilled, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(riDialog, &RecoveredItemDialog::acceptMessage, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::fightBoss, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::goBackToFighting, nullptr, nullptr);
    deadEnemy->hideBossButton();
    deadEnemy->showTransitionButton();
    deadHero->hideGoBackButton();

    this->setStyleSheet("#GameScreen {"
                        "border-image: url() 0 0 0 0 stretch stretch;"
                        "}");
    changeMusic("qrc:/other/other/Music/MainAmbient.mp3");

    bossFightOn = false;
    gameProgress = 0;
    gameLevel = 4;
    heroHealth = heroMaxHealth;
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    deadEnemy->hide();
    ui->heroHealthBar->setValue(heroHealth);
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    ui->dialogLabel->setText("");

    level4FirstFunction();
}

//LEVEL 4 - OGRODOWA
void GameScreen::level4FirstFunction()
{
    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 4 - Ogrodowa/Level4Background_1.png) 0 0 0 0 stretch stretch;"
                        "}");
    fadeInAnimation(this, 2000);
    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "*odgłosy przedzierania się przez las*";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 4 - Ogrodowa/MonologPoPrzybyciu.txt", 34);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 4 - Ogrodowa/MonologPoPrzybyciu.txt", 34);

    connect(this, &GameScreen::sceneEnded, this, [this]{
        numberOfRounds = 0;
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->enemyHealthBar->show();
        ui->enemyStatWidget->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(0);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(0);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        fight();
    });
    connect(this, &GameScreen::enemyKilled, this, [this]{
        if (gameProgress == 4)
        {
            disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
            disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
            disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
            disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
            level4SecondFunction();
        }
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(0);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        fight();
    });
}
void GameScreen::level4SecondFunction()
{
    fadeAwayAnimation(this, 2000);

    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 4 - Ogrodowa/Level4Background_2.png) 0 0 0 0 stretch stretch;"
                          "}");
    deadEnemy->hide();
    gameProgress = 0;

    fadeInAnimation(this, 2000);

    dialogs = new QString[2];
    dialogs[0] = "MIESZKANIEC OGRODOWEJ";
    dialogs[1] = "Wracaj tu! Młodzież jebana, zdegenerowana!!!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 4 - Ogrodowa/MonologPoPokonaniuOgrodowian.txt", 20);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 4 - Ogrodowa/MonologPoPokonaniuOgrodowian.txt", 20);

    connect(this, &GameScreen::sceneEnded, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(1);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            fight();

        connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(1);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            fight();
        });

        connect(this, &GameScreen::enemyKilled, this, [this]{
            if (gameProgress == 5)
            {
                deadEnemy->showBossButton();
                connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]{
                    fadeAwayAnimation(this, 1000);
                    this -> setStyleSheet("#GameScreen {"
                                          "border-image: url(:/images/images/Level 4 - Ogrodowa/Level3Background_3.png) 0 0 0 0 stretch stretch;"
                                          "}");
                    deadEnemy->hide();
                    deadEnemy->hideTransitionButton();
                    deadHero->showGoBackButton();
                    fadeInAnimation(this, 1000);
                    level4BossFight();
                });
            }
        });

        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(1);
            fight();
        });
    });
}
void GameScreen::level4BossFight()
{
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    gameProgress = 0;
    deadEnemy->hideBossButton();
    deadEnemy->hideTransitionButton();
    bossFightOn = true;

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Jakie zajadłe bestie!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 4 - Ogrodowa/RozmowaZBorowaPrzedWalka.txt", 34);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 4 - Ogrodowa/RozmowaZBorowaPrzedWalka.txt", 34);

    connect(this, &GameScreen::sceneEnded, this, [this]{
        switch(gameProgress)
        {
        case 0:
            numberOfRounds = 0;
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadEnemy->hide();
            drawEnemy(2);
            changeMusic("qrc:/other/other/Music/JagodaBattleMusic.mp3");
            fight();
            break;
        case 1:
            numberOfRounds = 0;
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            deadEnemy->hide();
            drawEnemy(3);
            fight();
            break;
        case 2:
            delay(1000);
            changeMusic("qrc:/other/other/Music/MainAmbient.mp3");
            riDialog->setIcon(1);
            riDialog->show();
            connect(riDialog, &RecoveredItemDialog::acceptMessage, this, [this]{
                riDialog->hide();
                ui->keyLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/kays.png) 0 0 0 0 stretch stretch;");
                level4PostLevelCleanup();
            });
            break;
        }
    });

    connect(this, &GameScreen::enemyKilled, this, [this]{
        switch(gameProgress)
        {
        case 1:
            dialogs = new QString[2];
            if (sex == 0)
                dialogs[0] = "PODRÓŻNICZKA";
            if (sex == 1)
                dialogs[0] = "PODRÓŻNIK";
            dialogs[1] = "*dyszy*";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 4 - Ogrodowa/PrzejscieDoPoteznejBorowy.txt", 12);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 4 - Ogrodowa/PrzejscieDoPoteznejBorowy.txt", 12);
            break;
        case 2:
            dialogs = new QString[2];
            dialogs[0] = "BORÓWA";
            dialogs[1] = "Aaaa!";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 4 - Ogrodowa/RozmowaKoncowa.txt", 50);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 4 - Ogrodowa/RozmowaKoncowa.txt", 50);
            break;
        }
    });
    connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level4RetreatFunction);
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        gameProgress = 0;
        numberOfRounds = 0;
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        deadHero->hide();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(2);
        fight();
    });
}
void GameScreen::level4RetreatFunction()
{
    deadHero->hide();
    deadHero->hideGoBackButton();
    deadEnemy->showTransitionButton();
    deadEnemy->showBossButton();
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);

    fadeAwayAnimation(this, 1000);
    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 4 - Ogrodowa/Level4Background_2.png) 0 0 0 0 stretch stretch;"
                        "}");

    numberOfRounds = 0;
    ui->enemyLabel->show();
    ui->enemyHealthBar->show();
    ui->enemyStatWidget->show();
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    drawEnemy(1);
    fadeInAnimation(this, 1000);
    changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
    fight();

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(1);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]{
        fadeAwayAnimation(this, 1000);
        this->setStyleSheet("#GameScreen {"
                            "border-image: url(:/images/images/Level 4 - Ogrodowa/Level3Background_3.png) 0 0 0 0 stretch stretch;"
                            "}");
        deadEnemy->hideBossButton();
        deadEnemy->hideTransitionButton();
        deadHero->showGoBackButton();
        fadeInAnimation(this, 1000);
        level4BossFight();
    });

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        drawEnemy(1);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        fight();
    });
}
void GameScreen::level4PostLevelCleanup()
{
    fadeAwayAnimation(this, 1000);

    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(riDialog, &RecoveredItemDialog::acceptMessage, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    deadHero->hideGoBackButton();
    deadEnemy->showTransitionButton();

    this -> setStyleSheet("#GameScreen {"
                          "border-image: url(:/images/images/Level 5 - Central Square Again/Level5Background_1.png) 0 0 0 0 stretch stretch;"
                          "}");

    gameLevel = 5;
    gameProgress = 0;
    numberOfRounds = 0;
    heroHealth = heroMaxHealth;
    deadEnemy->hide();
    deadEnemy->hideBossButton();
    ui->heroHealthBar->setValue(heroHealth);
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    ui->dialogLabel->setText("");

    fadeInAnimation(this, 1000);
    level5FirstFunction();
}

//LEVEL 5 - CENTRAL SQUARE AGAIN
void GameScreen::level5FirstFunction()
{
    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Podróżowanie po Włoszczowie idzie mi coraz lepiej";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 5 - Central Square Again/MonologPoPrzybyciu.txt", 22);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 5 - Central Square Again/MonologPoPrzybyciu.txt", 22);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(0);
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            if (gameProgress == 4)
                level5SecondFunction();
        });
        connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
            numberOfRounds = 0;
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(0);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(0);
            fight();
        });
    });
}
void GameScreen::level5SecondFunction()
{

    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);
    deadEnemy->hide();

    fadeAwayAnimation(this, 1000);

    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 5 - Central Square Again/Level5Background_2.png) 0 0 0 0 stretch stretch;"
                        "}");
    gameProgress = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);

    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "HAHAHAHAHAHA";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 5 - Central Square Again/PrzejscieDoDresow.txt", 42);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 5 - Central Square Again/PrzejscieDoDresow.txt", 42);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(1);
        fight();

        connect(this, &GameScreen::enemyKilled, this, [this]{
            if (gameProgress == 5)
            {
                deadEnemy->showBossButton();
                connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, &GameScreen::level5BossFight);
            }
        });
        connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
            numberOfRounds = 0;
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(1);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(1);
            fight();
        });
    });
}
void GameScreen::level5BossFight()
{
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    deadEnemy->hideBossButton();
    deadEnemy->hideTransitionButton();
    deadEnemy->hide();
    deadHero->showGoBackButton();

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Nawet nie wiecie jakie to satysfakcjonujące!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 5 - Central Square Again/PrzejscieDoKacpra.txt", 56);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 5 - Central Square Again/PrzejscieDoKacpra.txt", 56);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/PoteznyMatfizBattleMusic.mp3");
        drawEnemy(2);
        fight();

        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            deadHero->hide();
            changeMusic("qrc:/other/other/Music/PoteznyMatfizBattleMusic.mp3");
            drawEnemy(2);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level5RetreatFunction);

        connect(this, &GameScreen::enemyKilled, this, [this]{
            dialogs = new QString[2];
            dialogs[0] = "POTĘŻNY MATFIZ";
            dialogs[1] = "Jebać Legnicęęęęę...ęęęę...";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (manulOwned == true && sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 5 - Central Square Again/RozmowaGdyMaszManula.txt", 44);
            if (manulOwned == true && sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 5 - Central Square Again/RozmowaGdyMaszManula.txt", 44);
            if (manulOwned == false && sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 5 - Central Square Again/RozmowaGdyNieMaszManula.txt", 20);
            if (manulOwned == false && sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 5 - Central Square Again/RozmowaGdyNieMaszManula.txt", 20);
            connect(this, &GameScreen::sceneEnded, this, [this]{
                level5PostLevelCleanup();
                if (manulOwned)
                    level6FirstFunction();
                else
                    level7FirstFunction();
            });
        });
    });
}
void GameScreen::level5RetreatFunction()
{
    fadeAwayAnimation(this, 1000);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    deadEnemy->showBossButton();
    deadEnemy->showTransitionButton();
    deadHero->hideGoBackButton();
    gameProgress = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    deadHero->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    fadeInAnimation(this, 1000);

    changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
    drawEnemy(1);
    fight();

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(1);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, &GameScreen::level5BossFight);

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(1);
        fight();
    });

}
void GameScreen::level5PostLevelCleanup()
{
    fadeAwayAnimation(this, 1000);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    deadEnemy->hideBossButton();
    deadEnemy->showTransitionButton();
    deadEnemy->hide();
    deadHero->hideGoBackButton();

    gameProgress = 0;
    numberOfRounds = 0;

    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    ui->dialogLabel->setText("");
}

//LEVEL 6 - UNDERWORLD
void GameScreen::level6FirstFunction()
{
    gameLevel = 6;
    this->setStyleSheet("#GameScreen {"
                        "border-image: url(:/images/images/Level 6 - Underworld/Level6Background.png) 0 0 0 0 stretch stretch;"
                        "}");
    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Brrrrr!!!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 6 - Underworld/MonologPoczatkowy.txt", 18);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 6 - Underworld/MonologPoczatkowy.txt", 18);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        deadEnemy -> hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(0);
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            if (gameProgress == 2)
            {
                deadEnemy->hideTransitionButton();
                level6SecondFunction();
            }
        });
    });
    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(0);
        fight();
    });
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(0);
        fight();
    });
}
void GameScreen::level6SecondFunction()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    disconnect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, nullptr, nullptr);

    gameProgress = 0;
    numberOfRounds = 0;

    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Zaraza!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 6 - Underworld/DialogZWyjasnieniem.txt", 86);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 6 - Underworld/DialogZWyjasnieniem.txt", 86);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        deadEnemy -> hide();
        deadEnemy->showTransitionButton();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(0);
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            if (gameProgress == 2)
            {
                deadEnemy->showBossButton();
                connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, &GameScreen::level6BossFight);
            }
        });
        connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
            numberOfRounds = 0;
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(1);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
            drawEnemy(1);
            fight();
        });
    });
}
void GameScreen::level6BossFight()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    deadEnemy->hide();
    deadHero->showGoBackButton();
    deadEnemy->hideBossButton();
    deadEnemy->hideTransitionButton();

    dialogs = new QString[2];
    dialogs[0] = "DUCHY ŻYDÓW";
    dialogs[1] = "AAAAAAAAAAA!!!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 6 - Underworld/PrzejscieDoJackaJaworka.txt", 24);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 6 - Underworld/PrzejscieDoJackaJaworka.txt", 24);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        changeMusic("qrc:/other/other/Music/JaworekBattleMusic.mp3");
        drawEnemy(2);
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            dialogs = new QString[2];
            dialogs[0] = "JACEK JAWOREK";
            dialogs[1] = "Nieeeeeeee!!!";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 6 - Underworld/MonologPoPokonaniuJaworka.txt", 8);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 6 - Underworld/MonologPoPokonaniuJaworka.txt", 8);
            connect(this, &GameScreen::sceneEnded, this, [this]{
                disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
                fadeAwayAnimation(this, 1000);
                this->setStyleSheet("#GameScreen {"
                                    "border-image: url(:/images/images/Level 5 - Central Square Again/Level5Background_2_Fixed.png) 0 0 0 0 stretch stretch;"
                                    "}");
                deadEnemy->hide();
                fadeInAnimation(this, 1000);
                dialogs = new QString[2];
                if (sex == 0)
                    dialogs[0] = "PODRÓŻNICZKA";
                if (sex == 1)
                    dialogs[0] = "PODRÓŻNIK";
                dialogs[1] = "Wow!";
                showOneDialog(2);
                delete[] dialogs;
                dialogs = nullptr;
                if (sex == 0)
                    loadScene(":/dialogs/dialogs/female/Level 6 - Underworld/MonologPoWyjsciuNaPowierzchnie.txt", 14);
                if (sex == 1)
                    loadScene(":/dialogs/dialogs/male/Level 6 - Underworld/MonologPoWyjsciuNaPowierzchnie.txt", 14);
                connect(this, &GameScreen::sceneEnded, this, [this]{
                    level6PostLevelCleanup();
                    level7FirstFunction();
                });
            });
        });
        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            changeMusic("qrc:/other/other/Music/JaworekBattleMusic.mp3");
            drawEnemy(2);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level6RetreatFunction);
    });
}
void GameScreen::level6RetreatFunction()
{
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    deadEnemy->showBossButton();
    deadEnemy->showTransitionButton();
    deadHero->hideGoBackButton();
    gameProgress = 0;
    numberOfRounds = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    deadHero->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
    drawEnemy(1);
    fight();

    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(1);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, &GameScreen::level6BossFight);

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        changeMusic("qrc:/other/other/Music/MainBattleMusic.mp3");
        drawEnemy(1);
        fight();
    });
}
void GameScreen::level6PostLevelCleanup()
{
    fadeAwayAnimation(this, 1000);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    deadEnemy->hideBossButton();
    deadEnemy->showTransitionButton();
    deadEnemy->hide();
    deadHero->hideGoBackButton();

    gameProgress = 0;
    numberOfRounds = 0;
    curseRemoved = true;

    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    ui->dialogLabel->setText("");
}

//LEVEL 7 - WIEJSKA
void GameScreen::level7FirstFunction()
{
    gameLevel = 7;
    if (curseRemoved)
    {
        this -> setStyleSheet("#GameScreen {"
                              "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_1_Fixed.png) 0 0 0 0 stretch stretch;"
                              "}");
    }
    else
    {
        this -> setStyleSheet("#GameScreen {"
                              "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_1.png) 0 0 0 0 stretch stretch;"
                              "}");
    }
    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Ach Wiejska";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialog_01.txt", 12);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialog_01.txt", 12);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(0);
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            if (gameProgress == 3)
            {
                deadEnemy->showBossButton();
                connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]{
                    deadEnemy->hideBossButton();
                    deadEnemy->hideTransitionButton();
                    dialogs = new QString[2];
                    if (sex == 0)
                        dialogs[0] = "PODRÓŻNICZKA";
                    if (sex == 1)
                        dialogs[0] = "PODRÓŻNIK";
                    dialogs[1] = "Ufff";
                    showOneDialog(2);
                    delete[] dialogs;
                    dialogs = nullptr;
                    if (sex == 0)
                        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialog_02.txt", 16);
                    if (sex == 1)
                        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialog_02.txt", 16);
                    connect(this, &GameScreen::sceneEnded, this, &GameScreen::level7SecondFunction);
                });
            }
        });
        connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(0);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(0);
            fight();
        });
    });
}
void GameScreen::level7SecondFunction()
{
    fadeAwayAnimation(this, 1000);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    gameProgress = 0;
    deadEnemy->hideTransitionButton();
    deadEnemy->hide();
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    numberOfRounds = 0;
    deadHero->showGoBackButton();
    if (curseRemoved)
    {
        this->setStyleSheet("#GameScreen {"
                            "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_2_Fixed.png) 0 0 0 0 stretch stretch;"
                            "}");
    }
    else
    {
        this->setStyleSheet("#GameScreen {"
                            "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_2.png) 0 0 0 0 stretch stretch;"
                            "}");
    }
    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Ale jatka";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialog_03.txt", 22);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialog_03.txt", 22);
    connect(deadHero, &DeadHeroWidget::goBackToFighting, this, [this]{
        level7RetreatFunction();
    });
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(2);
        fight();

        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(2);
            fight();
        });
        connect(this, &GameScreen::enemyKilled, this, [this]{
            dialogs = new QString[2];
            dialogs[0] = "OMEGA";
            dialogs[1] = "Nieee";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0)
                loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialog_04.txt", 44);
            if (sex == 1)
                loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialog_04.txt", 44);
            connect(this, &GameScreen::sceneEnded, this, [this]{
                fadeAwayAnimation(this, 1000);
                deadEnemy->hide();
                fadeInAnimation(this, 1000);
                level7ThirdFunction();
            });
        });
    });
}
void GameScreen::level7ThirdFunction()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, &DeadHeroWidget::resurrectYourself, nullptr, nullptr);
    gameProgress = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    numberOfRounds = 0;

    dialogs = new QString[2];
    dialogs[0] = "SEZY";
    if (sex == 0)
        dialogs[1] = "Nieznajoma!";
    if (sex == 1)
        dialogs[1] = "Nieznajomy!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0 && drPieprzerOwned == true)
        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_05_DrOwned.txt", 56);
    if (sex == 0 && drPieprzerOwned == false)
        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_05_DrNotOwned.txt", 28);
    if (sex == 1 && drPieprzerOwned == true)
        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_05_DrOwned.txt", 56);
    if (sex == 1 && drPieprzerOwned == false)
        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_05_DrNotOwned.txt", 28);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        if (drPieprzerOwned)
        {
            sezySpared = true;
            level7BossFight();
        }
        else
        {
            numberOfRounds = 0;
            deadEnemy->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(3);
            fight();
            connect(this, &GameScreen::enemyKilled, this, [this]{
                dialogs = new QString[2];
                dialogs[0] = "SEZY";
                dialogs[1] = "Kurwa...";
                showOneDialog(2);
                delete[] dialogs;
                dialogs = nullptr;
                if (sex == 0)
                    loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_05_AfterSezyFight.txt", 6);
                if (sex == 1)
                    loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_05_AfterSezyFight.txt", 6);
                connect(this, &GameScreen::sceneEnded, this, &GameScreen::level7BossFight);
            });
            connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
                numberOfRounds = 0;
                deadHero->hide();
                ui->enemyLabel->show();
                ui->enemyStatWidget->show();
                ui->enemyHealthBar->show();
                heroHealth = heroMaxHealth;
                ui->heroHealthBar->setValue(heroHealth);
                drawEnemy(3);
                fight();
            });
        }
    });
}
void GameScreen::level7BossFight()
{
    fadeAwayAnimation(this, 1000);
    if (curseRemoved)
    {
        this -> setStyleSheet("#GameScreen {"
                              "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_3_Fixed.png) 0 0 0 0 stretch stretch;"
                              "}");
    }
    else
    {
        this -> setStyleSheet("#GameScreen {"
                              "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_3.png) 0 0 0 0 stretch stretch;"
                              "}");
    }
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    numberOfRounds = 0;
    gameProgress = 0;
    heroHealth = heroMaxHealth;
    if (deadEnemy->isVisible())
        deadEnemy->hide();
    if (deadHero->isVisible())
        deadHero->hide();
    ui->heroHealthBar->setValue(heroHealth);
    ui->dialogLabel->setText("");
    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "*dyszy*";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0 && drPieprzerOwned == true)
        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_06_DrOwned.txt", 34);
    if (sex == 0 && drPieprzerOwned == false)
        loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_06_DrNotOwned.txt", 32);
    if (sex == 1 && drPieprzerOwned == true)
        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_06_DrOwned.txt", 34);
    if (sex == 1 && drPieprzerOwned == false)
        loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_06_DrNotOwned.txt", 32);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        numberOfRounds = 0;
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(4);
        fight();
        connect(this, &GameScreen::enemyKilled, this, [this]{
            disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
            dialogs = new QString[2];
            dialogs[0] = "ALFA";
            dialogs[1] = "Nie mam na was czasu!";
            showOneDialog(2);
            delete[] dialogs;
            dialogs = nullptr;
            if (sex == 0 && drPieprzerOwned == true)
                loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_07_DrOwned.txt", 52);
            if (sex == 0 && drPieprzerOwned == false)
                loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_07_DrNotOwned.txt", 52);
            if (sex == 1 && drPieprzerOwned == true)
                loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_07_DrOwned.txt", 52);
            if (sex == 1 && drPieprzerOwned == false)
                loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_07_DrNotOwned.txt", 52);
            connect(this, &GameScreen::sceneEnded, this, &GameScreen::level7AlfaFight);
        });
        connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            deadHero->hide();
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            drawEnemy(4);
            fight();
        });
        connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level7RetreatFunction);
    });
}
void GameScreen::level7AlfaFight()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    numberOfRounds = 0;
    gameProgress = 0;
    deadEnemy->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();

    drawEnemy(5);
    fight();

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, &GameScreen::level7BossFight);
    connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level7RetreatFunction);
    connect(this, &GameScreen::enemyKilled, this, [this]{
        dialogs = new QString[2];
        dialogs[0] = "SENIOR HISZPANEK";
        dialogs[1] = "Nieeee!!!";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0 && drPieprzerOwned == true)
            loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_08_DrOwned.txt", 52);
        if (sex == 0 && drPieprzerOwned == false)
            loadScene(":/dialogs/dialogs/female/Level 7 - Wiejska/Dialogs_08_DrNotOwned.txt", 36);
        if (sex == 1 && drPieprzerOwned == true)
            loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_08_DrOwned.txt", 52);
        if (sex == 1 && drPieprzerOwned == false)
            loadScene(":/dialogs/dialogs/male/Level 7 - Wiejska/Dialogs_08_DrNotOwned.txt", 36);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            riDialog->show();
            riDialog->setIcon(2);
            connect(riDialog, &RecoveredItemDialog::acceptMessage, this, &GameScreen::level7PostLevelCleanup);
        });
    });
}
void GameScreen::level7RetreatFunction()
{
    fadeAwayAnimation(this, 1000);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);

    deadEnemy->showBossButton();
    deadEnemy->showTransitionButton();
    deadHero->hideGoBackButton();
    gameProgress = 0;
    numberOfRounds = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    deadHero->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    ui->enemyLabel->setStyleSheet("");
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    if (curseRemoved)
    {
        this->setStyleSheet("#GameScreen {"
                            "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_1_Fixed.png) 0 0 0 0 stretch stretch;"
                            "}");
    }
    else
    {
        this->setStyleSheet("#GameScreen {"
                            "border-image: url(:/images/images/Level 7 - Wiejska/Level7Background_1.png) 0 0 0 0 stretch stretch;"
                            "}");
    }
    fadeInAnimation(this, 1000);
    drawEnemy(0);
    fight();

    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]{
        numberOfRounds = 0;
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(0);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::transitionToNextPhase, this, [this]{
        numberOfRounds = 0;
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        deadEnemy->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(0);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]{
        deadEnemy->hideBossButton();
        level7SecondFunction();
    });
}
void GameScreen::level7PostLevelCleanup()
{
    riDialog->hide();
    ui->idLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/id.png) 0 0 0 0 stretch stretch;");
    fadeAwayAnimation(this, 1000);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(riDialog, nullptr, nullptr, nullptr);

    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    deadEnemy->hide();
    deadEnemy->showBossButton();
    deadEnemy->hideTransitionButton();
    deadHero->showResurectButton();
    deadHero->hideGoBackButton();

    this->setStyleSheet("#GameScreen {"
                        ""
                        "}");

    numberOfRounds = 0;
    gameProgress = 0;
    gameLevel = 8;

    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
    ui->dialogLabel->setText("");

    level8DapoFunction();
}

//LEVEL 8 - SIKORSKI HIGH
void GameScreen::level8DapoFunction()
{
    if (curseRemoved)
    {
        this->setStyleSheet("GameScreen {"
                            "border-image: url(:/images/images/Level 8 - Sikorski High/Level8Background_1_Fixed.png) 0 0 0 0 stretch stretch;"
                            "}");
    }
    else
    {
        this->setStyleSheet("GameScreen {"
                            "border-image: url(:/images/images/Level 8 - Sikorski High/Level8Background_1.png) 0 0 0 0 stretch stretch;"
                            "}");
    }
    fadeInAnimation(this, 1000);

    dialogs = new QString[2];
    dialogs[0] = "...";
    dialogs[1] = "Po całym tym czasie";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_01_BeforeDapoFight.txt", 32);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_01_BeforeDapoFight.txt", 32);
    connect(this, &GameScreen::sceneEnded, this, [this](){
        ui->enemyHealthBar->show();
        ui->enemyStatWidget->show();
        ui->enemyLabel->show();
        drawEnemy(0);
        fight();
    });
    connect(deadHero, &DeadHeroWidget::goBackToFighting, this, &GameScreen::level8RetreatFunction);
    connect(deadHero, &DeadHeroWidget::resurrectYourself, this, [this]() {
        numberOfRounds = 0;
        deadHero->hide();
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        heroHealth=heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        drawEnemy(gameProgress);
        fight();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
        disconnect(deadEnemy, nullptr, nullptr, nullptr);
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroMaxHealth);
        numberOfRounds = 0;
        deadEnemy->hideBossButton();
        deadEnemy->hide();
        level8PawelFunction();
    });
}
void GameScreen::level8PawelFunction()
{
    dialogs = new QString[2];
    dialogs[0] = "DAPO";
    dialogs[1] = "Aaaaa!";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_02_AfterDapoFightBeforePawelFight.txt", 36);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_02_AfterDapoFightBeforePawelFight.txt", 36);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(1);
        fight();
    });
    connect(this, &GameScreen::enemyKilled, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        dialogs = new QString[2];
        dialogs[0] = "KSIĄDZ PAWEŁ";
        dialogs[1] = "PRZEKLINAM CIĘ!!!";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_03_AfterPawelFight.txt", 6);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_03_AfterPawelFight.txt", 6);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            delay(1000);
            disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
            disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
            disconnect(deadEnemy, nullptr, nullptr, nullptr);
            numberOfRounds = 0;
            deadEnemy->hide();
            fadeAwayAnimation(this, 1000);
            ui->speakerLabel->setStyleSheet("");
            ui->nameLabel->setText("");
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroMaxHealth);
            this->setStyleSheet("#GameScreen {"
                                "border-image: url(:/images/images/Level 8 - Sikorski High/level8Background_2.png) 0 0 0 0 stretch stretch;"
                                "}");
            fadeInAnimation(this, 1000);
            level8MonikaMarczuFunction();
        });
    });
}
void GameScreen::level8MonikaMarczuFunction()
{
    dialogs = new QString[2];
    dialogs[0] = "...";
    dialogs[1] = "Oto Sikorski High";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_04_BeforeLoversFight.txt", 14);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_04_BeforeLoversFight.txt", 14);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        deadEnemy->showBossButton();
        drawEnemy(2);
        fight();
    });
    connect(this, &GameScreen::enemyKilled, this, [this]() {
        ui->speakerLabel->setStyleSheet("");
        ui->nameLabel->setText("");
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {
        deadEnemy->hide();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        dialogs = new QString[2];
        if (sex == 0)
            dialogs[0] = "PODRÓŻNICZKA";
        if (sex == 1)
            dialogs[0] = "PODRÓŻNIK";
        dialogs[1] = "Okropne miejsce";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_05_AfterLoversFightBeforeTosiaFight.txt", 38);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_05_AfterLoversFightBeforeTosiaFight.txt", 38);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            level8TosiaFunction();
        });
    });
}
void GameScreen::level8TosiaFunction()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    ui->nameLabel->setText("");
    ui->speakerLabel->setStyleSheet("");
    numberOfRounds=0;
    drawEnemy(3);
    fight();
    connect(this, &GameScreen::enemyKilled, this, [this]() {
        ui->enemyLabel->hide();
        ui->enemyStatWidget->hide();
        ui->enemyHealthBar->hide();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {
        numberOfRounds = 0;
        deadEnemy->hide();
        heroHealth = heroMaxHealth;
        ui->heroHealthBar->setValue(heroHealth);
        level8DejaFunction();
    });
}
void GameScreen::level8DejaFunction()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    dialogs = new QString[2];
    dialogs[0] = "...";
    dialogs[1] = "Jaka tragiczna historia";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_06_AfterTosiaFightBeforeDejaFight.txt", 26);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_06_AfterTosiaFightBeforeDejaFight.txt", 26);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        ui->enemyLabel->show();
        drawEnemy(4);
        fight();
    });
    connect(this, &GameScreen::enemyKilled, this, [this]() {
        numberOfRounds=0;
        ui->enemyLabel->hide();
        ui->enemyHealthBar->hide();
        ui->enemyStatWidget->hide();
    });
    connect(deadEnemy, &DeadEnemyWidget::fightBoss, this, [this]() {
        deadEnemy->hide();
        ui->enemyLabel->hide();
        ui->enemyStatWidget->hide();
        ui->enemyHealthBar->hide();
        dialogs = new QString[2];
        dialogs[0] = "...";
        dialogs[1] = "Nieźle, nieźle";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_07_AfterDejaFight.txt", 12);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_07_AfterDejaFight.txt", 12);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            delay(1000);
            fadeAwayAnimation(this, 1000);
            this->setStyleSheet("#GameScreen {"
                                "border-image: url(:/images/images/Level 8 - Sikorski High/level8Background_3.png) 0 0 0 0 stretch stretch;"
                                "}");
            heroHealth=heroMaxHealth;
            ui->heroHealthBar->setValue(heroMaxHealth);
            ui->nameLabel->setText("");
            ui->speakerLabel->setStyleSheet("");
            fadeInAnimation(this, 1000);
            level8JadziaFunction();
        });
    });
}
void GameScreen::level8JadziaFunction()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŹNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Okej... chyba już mi lepiej";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_08_BeforeJadziaFight.txt", 34);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_08_BeforeJadziaFight.txt", 34);
    connect(this, &GameScreen::sceneEnded, this, [this]() {
        disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
        ui->enemyLabel->show();
        ui->enemyStatWidget->show();
        ui->enemyHealthBar->show();
        drawEnemy(5);
        fight();
    });
    connect(this, &GameScreen::enemyKilled, this, [this]() {
        deadEnemy->hideBossButton();
        dialogs = new QString[2];
        dialogs[0] = "PANI JADZIA";
        dialogs[1] = "Zawiodłam się na tobie...";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_09_AfterJadziaBeforeBozenka.txt", 40);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_09_AfterJadziaBeforeBozenka.txt", 40);
        connect(this, &GameScreen::sceneEnded, this, [this]() {
            level8BozenkaFunction();
        });
    });
}
void GameScreen::level8BozenkaFunction()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    deadEnemy->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    deadEnemy->hideBossButton();
    numberOfRounds = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroMaxHealth);
    drawEnemy(6);
    fight();
    connect(this, &GameScreen::enemyKilled, this, [this]{
        disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
        deadEnemy->hide();
        dialogs = new QString[2];
        dialogs[0] = "BOŻENKA";
        dialogs[1] = "Ach!";
        showOneDialog(2);
        delete[] dialogs;
        dialogs = nullptr;
        if (sex == 0)
            loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_10_TransitionBozenka.txt", 32);
        if (sex == 1)
            loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_10_TransitionBozenka.txt", 32);
        connect(this, &GameScreen::sceneEnded, this, [this]{
            ui->enemyLabel->show();
            ui->enemyStatWidget->show();
            ui->enemyHealthBar->show();
            deadEnemy->hideBossButton();
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroMaxHealth);
            drawEnemy(7);
            fight();
            connect(this, &GameScreen::enemyKilled, this, [this]{
                level8PostLevelCleanup();
            });
        });
    });
}
void GameScreen::level8RetreatFunction()
{
    fadeAwayAnimation(this, 1000);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);
    disconnect(deadHero, nullptr, nullptr, nullptr);
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);

    deadEnemy->showBossButton();
    deadEnemy->showTransitionButton();
    deadHero->hideGoBackButton();
    gameProgress = 0;
    numberOfRounds = 0;
    heroHealth = heroMaxHealth;
    ui->heroHealthBar->setValue(heroHealth);
    deadHero->hide();
    ui->enemyLabel->show();
    ui->enemyStatWidget->show();
    ui->enemyHealthBar->show();
    ui->enemyLabel->setStyleSheet("");
    ui->speakerLabel->setStyleSheet("");
    ui->nameLabel->setText("");
}
void GameScreen::level8PostLevelCleanup()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);
    disconnect(this, &GameScreen::enemyKilled, nullptr, nullptr);
    disconnect(deadEnemy, nullptr, nullptr, nullptr);

    dialogs = new QString[2];
    if (sex == 0)
        dialogs[0] = "PODRÓŻNICZKA";
    if (sex == 1)
        dialogs[0] = "PODRÓŻNIK";
    dialogs[1] = "Nie masz szans";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 8 - Sikorski High/Dialog_11_AfterBozenkaFight.txt", 30);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 8 - Sikorski High/Dialog_11_AfterBozenkaFight.txt", 30);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        riDialog->show();
        riDialog->setIcon(3);
        connect(riDialog, &RecoveredItemDialog::acceptMessage, this, [this]{
            ui->moneyLabel->setStyleSheet("border-image: url(:/images/images/AppScreenArt/wallet.png) 0 0 0 0 stretch stretch;");
            riDialog->hide();
            numberOfRounds = 0;
            heroHealth = heroMaxHealth;
            ui->heroHealthBar->setValue(heroHealth);
            ui->dialogLabel->setText("");
            ui->nameLabel->setText("");
            ui->speakerLabel->setStyleSheet("");
            ui->enemyHealthBar->hide();
            ui->enemyStatWidget->hide();
            deadEnemy->hide();
            fadeAwayAnimation(this, 1000);
            if (curseRemoved)
            {
                this->setStyleSheet("#GameScreen {"
                                    "border-image: url(:/images/images/Level 5 - Central Square Again/Level5Background_2.png) 0 0 0 0 stretch stretch;"
                                    "}");
            }
            else
            {
                this->setStyleSheet("#GameScreen {"
                                    "border-image: url(:/images/images/Level 5 - Central Square Again/Level5Background_2_Fixed.png) 0 0 0 0 stretch stretch;"
                                    "}");
            }
            fadeInAnimation(this, 1000);
            if (curseRemoved && sezySpared)
                good_end_function();
            else
                bad_end_function();
        });
    });
}

//END FUNCTIONS
void GameScreen::good_end_function()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);

    dialogs = new QString[2];
    dialogs[0] = "...";
    dialogs[1] = "A więc nareszcie... nadszedł czas";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 9 - Ending/Ending_Dialog_Good.txt", 32);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 9 - Ending/Ending_Dialog_Good.txt", 32);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        emit gameEnded();
    });
}
void GameScreen::bad_end_function()
{
    disconnect(this, &GameScreen::sceneEnded, nullptr, nullptr);

    dialogs = new QString[2];
    dialogs[0] = "...";
    dialogs[1] = "A więc nareszcie... nadszedł czas";
    showOneDialog(2);
    delete[] dialogs;
    dialogs = nullptr;
    if (sex == 0)
        loadScene(":/dialogs/dialogs/female/Level 9 - Ending/Ending_Dialog_Bad.txt", 10);
    if (sex == 1)
        loadScene(":/dialogs/dialogs/male/Level 9 - Ending/Ending_Dialog_Bad.txt", 10);
    connect(this, &GameScreen::sceneEnded, this, [this]{
        emit gameEnded();
    });
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
        if (weaponLevel >= 0 && weaponLevel <= 2)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 3 && weaponLevel <= 5)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 6 && weaponLevel <= 8)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass3.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 9 && weaponLevel <= 11)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass4.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 12)
            ui->weaponShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass5.png) 0 0 0 0 stretch stretch;");

        if (weaponLevel > 0 && weaponLevel <= 3)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass1.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 4 && weaponLevel <= 6)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass2.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 7 && weaponLevel <= 9)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass3.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 10 && weaponLevel <= 12)
            ui->attackActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/WeaponClass4.png) 0 0 0 0 stretch stretch;");
        if (weaponLevel >= 13)
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
        if (shieldLevel >= 0 && shieldLevel <= 2)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 3 && shieldLevel <= 5)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 6 && shieldLevel <= 8)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 9 && shieldLevel <= 11)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 12)
            ui->shieldShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass5.png) 0 0 0 0 stretch stretch;");

        if (shieldLevel > 0 && shieldLevel <= 3)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass1.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 4 && shieldLevel <= 6)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass2.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 7 && shieldLevel <= 9)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass3.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 10 && shieldLevel <= 12)
            ui->defenseActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/ShieldClass4.png) 0 0 0 0 stretch stretch;");
        if (shieldLevel >= 13)
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
            heroMaxHealth += healthLevel * 25;
        if (sex == 1)
            heroMaxHealth += healthLevel * 18;
        if (healthLevel * 3 <= 75)
            heroHealRate = 3 * healthLevel;
        else if (healthLevel * 3 > 75)
            heroHealRate = 75;
        healthPrice = 120 * healthLevel * healthLevel * cbrt(healthLevel) + 120;

        ui->amountOfMoneyLabel->setText(QString::number(wealth));
        ui->heroHealthPointsLabel->setText(QString::number(heroMaxHealth));
        ui->healthShopPriceLabel->setText(QString::number(healthPrice));
        if (healthLevel >= 0 && healthLevel <= 2)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 3 && healthLevel <= 5)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 6 && healthLevel <= 8)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 9 && healthLevel <= 11)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 12)
            ui->healthShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass5.png) 0 0 0 0 stretch stretch;");

        if (healthLevel > 0 && healthLevel <= 3)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass1.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 4 && healthLevel <= 6)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass2.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 7 && healthLevel <= 9)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass3.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 10 && healthLevel <= 12)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass4.png) 0 0 0 0 stretch stretch;");
        if (healthLevel >= 13)
            ui->healActionButton->setStyleSheet("border-image: url(:/images/images/Shop - Normal/HealthClass5.png) 0 0 0 0 stretch stretch;");

        ui->heroHealthBar->setMaximum(heroMaxHealth);
        heroHealth = heroMaxHealth;
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
    int eBaseAtt = 0, eBaseDef = 0, eBaseHp = 0;
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
            eBaseAtt = drawStat(10);
            eBaseDef = drawStat(40);
            eBaseHp = drawStat(80);
        }
        if (enemyType == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Dresiarz.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(30);
            eBaseDef = drawStat(40);
            eBaseHp = drawStat(100);
        }
        break;
    case 2:
        if (whatToDraw == -1)
            enemyType = rand() % 2;
        else if (whatToDraw == 2)
            enemyType = 2;

        if (enemyType == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 2 - Pilica River/WscieklyPies.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(10);
            eBaseDef = drawStat(20);
            eBaseHp = drawStat(150);
        }
        if (enemyType == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 2 - Pilica River/WscieklyOgar.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(15);
            eBaseDef = drawStat(25);
            eBaseHp = drawStat(100);
        }
        if (enemyType == 2)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 2 - Pilica River/Jezus.png) 0 0 0 0 stretch stretch;");
            enemyAttack = 20;
            enemyDefense = 30;
            enemyHealth = 300;
            spawnEnemy(enemyAttack, enemyDefense, enemyHealth, enemyHealth);
            return;
        }
        break;
    case 3:
        if (whatToDraw == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 3 - Kurzelow/BydleceSilyZbrojne.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(20);
            eBaseDef = drawStat(35);
            eBaseHp = drawStat(200);
        }
        if (whatToDraw == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 3 - Kurzelow/JanBrozek.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 24;
            eBaseDef = 30;
            eBaseHp = 240;
        }
        if (whatToDraw == 2)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 3 - Kurzelow/AdamZKurzelowa.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 26;
            eBaseDef = 30;
            eBaseHp = 250;
        }
        if (whatToDraw == 3)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 3 - Kurzelow/AdamCzarny.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 24;
            eBaseDef = 35;
            eBaseHp = 300;
        }
        if (whatToDraw == 4)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 3 - Kurzelow/MrBallsamn.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 40;
            eBaseDef = 20;
            eBaseHp = 150;
        }
        if (whatToDraw == 5)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 3 - Kurzelow/CoolaMinecraftOfficial.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 10;
            eBaseDef = 30;
            eBaseHp = 1000;
        }
        enemyType = whatToDraw;
        break;
    case 4:
        if (whatToDraw == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 4 - Ogrodowa/MieszkaniecOgrodowej.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(35);
            eBaseDef = drawStat(40);
            eBaseHp = drawStat(500);
            enemyType = 0;
        }
        if (whatToDraw == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 4 - Ogrodowa/Rzepon.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(35);
            eBaseDef = drawStat(50);
            eBaseHp = drawStat(800);
            enemyType = 1;
        }
        if (whatToDraw == 2)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 4 - Ogrodowa/Borowa.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 45;
            eBaseDef = 50;
            eBaseHp = 1000;
            enemyType = 2;
        }
        if (whatToDraw == 3)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 4 - Ogrodowa/PoteznaBorowa.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 50;
            eBaseDef = 60;
            eBaseHp = 1250;
            enemyType = 3;
        }
        break;
    case 5:
        if (whatToDraw == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Bezdomny.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(40);
            eBaseDef = drawStat(40);
            eBaseHp = drawStat(1000);
        }
        if (whatToDraw == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 1 - Central Square/Dresiarz.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(50);
            eBaseDef = drawStat(50);
            eBaseHp = drawStat(1500);
        }
        if (whatToDraw == 2)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 5 - Central Square Again/PoteznyMatfiz.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(60);
            eBaseDef = drawStat(60);
            eBaseHp = drawStat(2000);
        }
        enemyType = whatToDraw;
        break;
    case 6:
        enemyType = rand() % 2;
        if (whatToDraw == 2)
            enemyType = 2;

        if (enemyType == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 6 - Underworld/DuchZyda.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(60);
            eBaseDef = drawStat(60);
            eBaseHp = drawStat(1700);
        }
        if (enemyType == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 6 - Underworld/DuchyZydow.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(55);
            eBaseDef = drawStat(55);
            eBaseHp = drawStat(1800);
        }
        if (enemyType == 2)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 6 - Underworld/JacekJaworek.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(80);
            eBaseDef = drawStat(60);
            eBaseHp = drawStat(2500);
        }
        break;
    case 7:
        if (whatToDraw == 0)
            enemyType = rand() % 2;
        else
            enemyType = whatToDraw;

        if (enemyType == 0)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 7 - Wiejska/MieszkancyWiejskiej.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(90);
            eBaseDef = drawStat(120);
            eBaseHp = drawStat(2000);
        }
        if (enemyType == 1)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 7 - Wiejska/MieszkancyWiejskiej_2.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(90);
            eBaseDef = drawStat(130);
            eBaseHp = drawStat(2000);
        }
        if (enemyType == 2)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 7 - Wiejska/Omega.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 100;
            eBaseDef = 150;
            eBaseHp = 3000;
        }
        if (enemyType == 3)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 7 - Wiejska/Sezy.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = drawStat(120);
            eBaseDef = drawStat(140);
            eBaseHp = drawStat(3000);
        }
        if (enemyType == 4)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 7 - Wiejska/Alpha.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 140;
            eBaseDef = 150;
            eBaseHp = 3500;
        }
        if (enemyType == 5)
        {
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 7 - Wiejska/SeniorHiszpanek.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 150;
            eBaseDef = 150;
            eBaseHp = 4000;
        }
        break;
    case 8:
        switch (whatToDraw)
        {
        case 0:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/Dapo.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 175;
            eBaseDef = 200;
            eBaseHp = 5000;
            break;
        case 1:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/KsiadzPawel.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 200;
            eBaseDef = 225;
            eBaseHp = 6500;
            break;
        case 2:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/MonikaAndMarczu.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 225;
            eBaseDef = 250;
            eBaseHp = 7250;
            break;
        case 3:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/Tosia.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 230;
            eBaseDef = 260;
            eBaseHp = 7500;
            break;
        case 4:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/PaniDeja.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 250;
            eBaseDef = 300;
            eBaseHp = 8000;
            break;
        case 5:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/PaniJadzia.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 300;
            eBaseDef = 300;
            eBaseHp = 8000;
            break;
        case 6:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/Bozenka.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 420;
            eBaseDef = 500;
            eBaseHp = 10000;
            break;
        case 7:
            ui->enemyLabel->setStyleSheet("border-image: url(:/images/images/Level 8 - Sikorski High/Bozenkus.png) 0 0 0 0 stretch stretch;");
            eBaseAtt = 450;
            eBaseDef = 500;
            eBaseHp = 20000;
            break;
        }
        break;
    default:
        qDebug() << "WRONG GAME LEVEL IN SPAWNING FUNCTION!";
        break;
    }
    enemyAttack = eBaseAtt;
    enemyDefense = eBaseDef;
    enemyMaxHealth = eBaseHp;
    enemyHealth = enemyMaxHealth;
    spawnEnemy(enemyAttack, enemyDefense, enemyHealth, enemyMaxHealth);
}
void GameScreen::spawnEnemy(int att, int def, int hp, int mhp)
{
    ui->enemyAttackPointsLabel->setText(QString::number(att));
    ui->enemyDefensePointsLabel->setText(QString::number(def));
    ui->enemyHealthPointsLabel->setText(QString::number(mhp));
    ui->enemyHealthBar->setMinimum(0);
    ui->enemyHealthBar->setMaximum(mhp);
    ui->enemyHealthBar->setValue(hp);
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
        enemyBaseDamage = floor(0.5 * static_cast<double>(enemyAttack) *
                                (1 + static_cast<double>(enemyAttack) / static_cast<double>(heroDefense)));

        int enemyRealDamage = rand() % static_cast<int>(0.4*enemyBaseDamage + 1) + static_cast<int>(0.8*enemyBaseDamage);

        if (shieldOn == true && heroShield > enemyRealDamage)
        {
            heroShield -= enemyRealDamage;
            ui->heroHealthBar->setValue(heroShield);
            int rVal = rand() % 100 + 1;
            if (rVal <= heroReflectionRate && enemyHealth >= enemyRealDamage * 0.25)
            {
                enemyHealth -= enemyRealDamage * 0.25;
                ui->enemyHealthBar->setValue(enemyHealth);
            }
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
                if (blahajOwned == true)
                {
                    delay(500);
                    heroHealth += heroMaxHealth / 2;
                    ui->heroHealthBar->setValue(heroHealth);
                    blahajOwned = false;
                    ui->blahajSlotLabel->setStyleSheet("");
                    ui->blahajShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Special/Blahaj.png) 0 0 0 0 stretch stretch;");
                    ui->blahajShopPriceLabel->setText("5000");
                    ui->blahajShopLabel->setText("");
                    numberOfRounds++;
                    fight();
                    return;
                }
                else
                {
                    heroIsDead();
                    emit heroKilled();
                }
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
            if (blahajOwned == true)
            {
                delay(500);
                heroHealth += heroMaxHealth / 2;
                ui->heroHealthBar->setValue(heroHealth);
                blahajOwned = false;
                ui->blahajSlotLabel->setStyleSheet("");
                ui->blahajShopLabel->setStyleSheet("border-image: url(:/images/images/Shop - Special/Blahaj.png) 0 0 0 0 stretch stretch;");
                ui->blahajShopPriceLabel->setText("5000");
                ui->blahajShopLabel->setText("");
                numberOfRounds++;
                fight();
                return;
            }
            else
            {
                heroIsDead();
                emit heroKilled();
                return;
            }
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
int GameScreen::drawStat(int base)
{
    int result = rand() % static_cast<int>(0.4*base + 1) + static_cast<int>(0.8*base);
    if (gameLevel == 7)
        result = rand() % static_cast<int>(0.2*base + 1) + static_cast<int>(0.9*base);
    return result;
}

void GameScreen::heroIsDead()
{
    ui->enemyLabel->hide();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    deadHero->show();
    player->stop();
    player->setSource(QUrl("qrc:/other/other/Music/MainAmbient.mp3"));
    player->play();
    double loss = 0.1 * static_cast<double>(wealth);
    wealth -= static_cast<int>(loss);
    ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
    ui->amountOfMoneyLabel->setStyleSheet("color: rgb(170,0,0); font-size: 20px;");
    delay(500);
    ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    connectShop();
}
void GameScreen::enemyIsDead()
{
    ui->enemyLabel->hide();
    ui->enemyStatWidget->hide();
    ui->enemyHealthBar->hide();
    deadEnemy->show();
    if ((gameLevel == 3 || gameLevel == 4) && bossFightOn)
    {

    }
    else
    {
        changeMusic("qrc:/other/other/Music/MainAmbient.mp3");
    }
    if (shieldOn)
        takeOffShield();
    gameProgress++;
    int loot = calculateLoot(gameLevel, enemyType);
    wealth += loot;
    ui->amountOfMoneyLabel->setText(QString::number(wealth, 10));
    ui->amountOfMoneyLabel->setStyleSheet("color: rgb(10,150,0); font-size: 20px;");
    delay(500);
    ui->amountOfMoneyLabel->setStyleSheet("color: rgb(180,180,180); font-size: 20px;");
    connectShop();
}
void GameScreen::takeOffShield()
{
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
}
int GameScreen::calculateLoot(int level, int enemyType)
{
    int loot = 0;
    switch(level)
    {
    case 1:
        loot = (enemyType + 1) * 25;
        break;
    case 2:
        loot = 35;
        break;
    case 3:
        if (enemyType == 0)
            loot = 150;
        else if (enemyType == 1)
            loot = 400;
        else if (enemyType == 5)
            loot = 2000;
        break;
    case 4:
        if (enemyType == 0)
            loot = 500;
        if (enemyType == 1)
            loot = 750;
        if (enemyType == 3)
            loot = 5000;
        break;
    case 5:
        if (enemyType == 0)
            loot = 1000;
        if (enemyType == 1)
            loot = 1250;
        if (enemyType == 2)
            loot = 7500;
        break;
    case 6:
        if (enemyType == 0 || enemyType == 1)
            loot = 500;
        if (enemyType == 2)
            loot = 10000;
        break;
    case 7:
        if (enemyType == 0 || enemyType == 1)
            loot = 2500;
        if (enemyType == 2)
            loot = 10000;
        if (enemyType == 3)
            loot = 10000;
        if (enemyType == 5)
            loot = 25000;
        break;
    case 8:
        if (gameProgress <= 2)
            loot = 25000;
        if (gameProgress >= 3 && gameProgress <= 4)
            loot = 60000;
        if (gameProgress >= 5)
            loot = 100000;
        break;
    default:
        loot = 0;
        qDebug() << "WTF DUDE?!";
        break;
    }
    return loot;
}

void GameScreen::on_attackActionButton_clicked()
{
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroDefends);
    disconnect(ui->confirmButton, &QPushButton::clicked, this, &GameScreen::heroHealsHimself);

    int baseDamage = floor(0.5 * static_cast<double>(heroAttack) * (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));

    ui->infoAboutActionLabel->setText("Atak (poz. " + QString::number(weaponLevel) + ")\nObrażenia: " +
                                      QString::number(static_cast<int>(0.8 * baseDamage)) + " - " +
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

    ui->infoAboutActionLabel->setText("Tarcza (poz. " + QString::number(shieldLevel) + ")\nUzyskiwana tarcza: " +
                                      QString::number(heroDefense) + " - " + QString::number(heroDefense*2) + "\nSzansa na odbicie: " +
                                      QString::number(heroReflectionRate) + "%");
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

    int baseDamage = floor(0.5 * static_cast<double>(heroAttack) * (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));

    ui->infoAboutActionLabel->setText("Leczenie (poz. " + QString::number(healthLevel) + ")\nObrażenia: " +
                                      QString::number(static_cast<int>(1.2*baseDamage)) + " - " +
                                      QString::number(static_cast<int>(1.8*baseDamage)) + '\n' + "Odzyskane życie: " +
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

    int baseDamage = floor(0.5 * static_cast<double>(heroAttack) * (1 + static_cast<double>(heroAttack) / static_cast<double>(enemyDefense)));
    int realDamage = rand() % static_cast<int>(0.4*baseDamage + 1) + static_cast<int>(0.8*baseDamage);

    if (rand() % 100 + 1 < heroCritRate)
        realDamage *= 1.5;

    ui->infoAboutActionLabel->setText("");
    ui->confirmButton->hide();
    delay(150);
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
        emit enemyKilled();
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

    heroShield = rand() % static_cast<int>(0.8 * heroDefense + 1) + static_cast<int>(heroDefense);
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

    int baseDamage = floor(0.5 * static_cast<double>(heroAttack) * 1.5 *
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
    delay(500);
    if (enemyHealth == 0)
    {
        enemyIsDead();
        emit enemyKilled();
        return;
    }
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

//OTHER
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
void GameScreen::changeMusic(QString path)
{
    player->stop();
    player->setSource(QUrl(path));
    player->play();
}

//DIALOGS
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
    connectionHub(true, numOfLines);
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
        delay(10);
    }
    counterOfLines += 2;
    if (counterOfLines == totalNumOfLines)
    {
        counterOfLines = 0;
        ui->continueButton->setEnabled(false);
        if (totalNumOfLines != 2)
            connectionHub(false, 0);
        if ((gameLevel >= 3 && gameLevel <= 8) && totalNumOfLines == 2)
            return;
        emit sceneEnded();
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
