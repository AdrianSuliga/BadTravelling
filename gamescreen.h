#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QHash>
#include <deadenemywidget.h>
#include <deadherowidget.h>
#include <tutorialinfo.h>
#include <recovereditemdialog.h>

namespace Ui {
class GameScreen;
}

class GameScreen : public QWidget
{
    Q_OBJECT

public:
    explicit GameScreen(QWidget *parent = nullptr, int gender = -1);
    ~GameScreen();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    //SETUP
    void loadVariables();
    //LEVEL 1
    void level1FirstFunction();
    void showTutorial();
    void endSceneAndPostLevelCleanup();
    //LEVEL 2
    void level2FirstFunction();
    void level2HelperFunction();
    void level2BossFight();
    void level2RetreatFromBossFunction();
    void level2PostLevelCleanup();
    //LEVEL 3
    void level3FirstFunction();
    void level3HelperFunction();
    void level3BossFight();
    void level3RetreatFromBossFunction();
    void level3PostLevelCleanup();
    //LEVEL 4
    void level4FirstFunction();
    void level4SecondFunction();
    void level4BossFight();
    void level4RetreatFunction();
    void level4PostLevelCleanup();
    //LEVEL 5
    void level5FirstFunction();
    void level5SecondFunction();
    void level5BossFight();
    void level5RetreatFunction();
    void level5PostLevelCleanup();
    //LEVEL 6
    void level6FirstFunction();
    void level6SecondFunction();
    void level6BossFight();
    void level6RetreatFunction();
    void level6PostLevelCleanup();
    //LEVEL 7
    void level7FirstFunction();
    void level7SecondFunction();
    void level7ThirdFunction();
    void level7BossFight();
    void level7AlfaFight();
    void level7RetreatFunction();
    void level7PostLevelCleanup();
    //LEVEL 8
    void level8DapoFunction();
    void level8PawelFunction();
    void level8MonikaMarczuFunction();
    void level8TosiaFunction();
    void level8DejaFunction();
    void level8JadziaFunction();
    void level8BozenkaFunction();
    void level8RetreatFunction();
    //SHOP
    void connectShop();
    void disconnectShop();
    void userWantsToBuyWeapon();
    void userWantsToBuyShield();
    void userWantsToBuyHealth();
    void userWantsToBuyBlahaj();
    void userWantsToBuyManul();
    void userWantsToBuyDrPieprzer();
    //OTHER
    void delay(int ms);
    void fadeAwayAnimation(QWidget* widget, int ms);
    void fadeInAnimation(QWidget* widget, int ms);
    //DIALOGS
    void loadScene(QString pathToDialog, int numOfLines);
    void showOneDialog(int totalNumOfLines);
    void connectionHub(bool cORd, int numOfLines);
    //FIGHT
    void drawEnemy(int whatToDraw);
    void spawnEnemy(int att, int def, int hp, int mhp);
    void fight();
    void heroIsDead();
    void enemyIsDead();
    void takeOffShield();
    int calculateLoot(int level, int enemyType);
    int drawStat(int base);
    void on_attackActionButton_clicked();
    void on_defenseActionButton_clicked();
    void on_healActionButton_clicked();
    void updateActionPointsButtons();
    void heroAttacks();
    void heroDefends();
    void heroHealsHimself();
signals:
    void heroKilled();
    void enemyKilled();
    void sceneEnded();
private:
    Ui::GameScreen *ui;
    int sex;
    bool blahajOwned, manulOwned, drPieprzerOwned, shieldOn, shieldBroken, curseRemoved;
    int heroAttack, heroCritRate, heroDefense, heroShield, heroReflectionRate, heroHealth, heroMaxHealth, heroHealRate,
        enemyAttack, enemyDefense, enemyHealth, enemyMaxHealth;
    int wealth, weaponPrice, shieldPrice, healthPrice, blahajPrice, manulPrice, drPieprzerPrice;
    short weaponLevel, shieldLevel, healthLevel, gameLevel, gameProgress, enemyType, actionPoints, numberOfRounds, counterOfLines;
    QString* dialogs;
    QHash<QString, QString> nameToPath;
    DeadEnemyWidget *deadEnemy;
    DeadHeroWidget *deadHero;
    TutorialInfo *tutorialWidget;
    RecoveredItemDialog *riDialog;
};

#endif // GAMESCREEN_H
