#include "enemyattackcontroller.h"
#include <QTime>
#include <QCoreApplication>
#include <QDebug>

EnemyAttackController::EnemyAttackController(QWidget *parent, int heroCurrentHealth, int damage)
{
    buffer = heroCurrentHealth;
    dmg = damage;
}

EnemyAttackController::~EnemyAttackController() {}

void EnemyAttackController::attackController()
{
    while (buffer > 0)
    {
        emit attack();
        buffer -= dmg;
        delay();
    } //THIS DOES NOT STOP! - FIX THAT
    emit heroKilled();
}

void EnemyAttackController::delay()
{
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while (dieTime > QTime::currentTime())
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
