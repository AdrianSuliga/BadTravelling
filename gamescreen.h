#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QHash>
#include <deadenemywidget.h>
#include <deadherowidget.h>
#include <tutorialinfo.h>

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
    void level1MainFunction();
    void showTutorial();
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
    void loadScene(QString pathToDialog, int numOfLines);
    void showOneDialog(QString* dialogs, int totalNumOfLines);
    //FIGHT
    void drawEnemy(int whatToDraw);
    void fight();
    void heroIsDead();
    void enemyIsDead();
    void on_attackActionButton_clicked();
    void on_defenseActionButton_clicked();
    void on_healActionButton_clicked();
    void updateActionPointsButtons();
    void heroAttacks();
    void heroDefends();
    void heroHealsHimself();
signals:
    void enemyKilled();
    void heroKilled();
    void sceneEnded();
private:
    Ui::GameScreen *ui;
    int sex;
    bool blahajOwned, manulOwned, drPieprzerOwned, shieldOn, shieldBroken;
    int heroAttack, heroCritRate, heroDefense, heroShield, heroHealth, heroMaxHealth,
        enemyAttack, enemyDefense, enemyHealth, enemyMaxHealth;
    int wealth, weaponPrice, shieldPrice, healthPrice, blahajPrice, manulPrice, drPieprzerPrice;
    short weaponLevel, shieldLevel, healthLevel, gameLevel, actionPoints, numberOfRounds, counterOfLines;
    QHash<QString, QString> nameToPath;
    DeadEnemyWidget *deadEnemy;
    DeadHeroWidget *deadHero;
    TutorialInfo *tutorialWidget;
};

#endif // GAMESCREEN_H
