#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>

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
    //void enemyAttacked();
    //SHOP
    void userWantsToBuyWeapon();
    void userWantsToBuyShield();
    void userWantsToBuyHealth();
    void userWantsToBuyBlahaj();
    void userWantsToBuyManul();
    void userWantsToBuyDrPieprzer();
    //void userWantsToHeal();
    //OTHER
    void delay(int ms);
    void drawEnemy();
    void fight();

private:
    Ui::GameScreen *ui;
    int sex;
    bool blahajOwned, manulOwned, drPieprzerOwned;
    int heroAttack, heroDefense, heroHealth, heroMaxHealth, enemyAttack, enemyDefense, enemyHealth, enemyMaxHealth;
    int wealth, weaponPrice, shieldPrice, healthPrice, blahajPrice, manulPrice, drPieprzerPrice, healingPrice;
    short weaponLevel, shieldLevel, healthLevel, gameLevel;
};

#endif // GAMESCREEN_H
