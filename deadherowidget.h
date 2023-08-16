#ifndef DEADHEROWIDGET_H
#define DEADHEROWIDGET_H

#include <QWidget>

namespace Ui {
class DeadHeroWidget;
}

class DeadHeroWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeadHeroWidget(QWidget *parent = nullptr);
    ~DeadHeroWidget();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::DeadHeroWidget *ui;
};

#endif // DEADHEROWIDGET_H
