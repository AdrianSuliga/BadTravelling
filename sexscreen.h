#ifndef SEXSCREEN_H
#define SEXSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include "qclickablewidget.h"

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
signals:
    void womanChosen();
    void manChosen();
private:
    Ui::SexScreen *ui;
    QFont Garissol;
};

#endif // SEXSCREEN_H
