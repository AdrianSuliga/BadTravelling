#ifndef ENEMYATTACKCONTROLLER_H
#define ENEMYATTACKCONTROLLER_H

#include <QObject>

class EnemyAttackController : public QObject
{
    Q_OBJECT
public:
    explicit EnemyAttackController(QWidget *parent = nullptr, int heroCurrentHealth = -1, int damage = -1);
    ~EnemyAttackController();
    void attackController();
private slots:
    void delay();
signals:
    void attack();
    void heroKilled();
private:
    int buffer, dmg;
};

#endif // ENEMYATTACKCONTROLLER_H
