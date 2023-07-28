#ifndef SEXSCREEN_H
#define SEXSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QFont>

namespace Ui {
class SexScreen;
}

class SexScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SexScreen(QWidget *parent = nullptr);
    ~SexScreen();
    void paintEvent(QPaintEvent *event);
    void animateText();
    void delay(int miliseconds);

private:
    Ui::SexScreen *ui;
    QFont Garissol;
};

#endif // SEXSCREEN_H
