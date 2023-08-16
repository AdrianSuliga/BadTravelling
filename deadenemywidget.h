#ifndef DEADENEMYWIDGET_H
#define DEADENEMYWIDGET_H

#include <QWidget>

namespace Ui {
class DeadEnemyWidget;
}

class DeadEnemyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeadEnemyWidget(QWidget *parent = nullptr);
    ~DeadEnemyWidget();
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void transitionToNextPhase();
private:
    Ui::DeadEnemyWidget *ui;
};

#endif // DEADENEMYWIDGET_H
