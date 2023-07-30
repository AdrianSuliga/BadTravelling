#ifndef PROLOGUESCREEN_H
#define PROLOGUESCREEN_H

#include <QWidget>
#include <QFont>

namespace Ui {
class PrologueScreen;
}

class PrologueScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PrologueScreen(QWidget *parent = nullptr, int sex = -1);
    ~PrologueScreen();
    void animateText(QString text);
private slots:
    void delay(int ms);
private:
    Ui::PrologueScreen *ui;
    QFont Girassol;
};

#endif // PROLOGUESCREEN_H
