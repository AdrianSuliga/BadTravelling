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
    void showGoBackButton();
    void showResurectButton();
    void hideGoBackButton();
    void hideResurectButton();
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void resurrectYourself();
    void goBackToFighting();
private slots:
    void on_pushButton_clicked();
private:
    Ui::DeadHeroWidget *ui;
};

#endif // DEADHEROWIDGET_H
