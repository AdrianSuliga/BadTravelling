#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <QWidget>
#include <QFont>

namespace Ui {
class TitleScreen;
}

class TitleScreen : public QWidget
{
    Q_OBJECT

public:
    explicit TitleScreen(QWidget *parent = nullptr);
    ~TitleScreen();
    void paintEvent(QPaintEvent *event);
    void activate_continue_button();
    void deactivate_continue_button();
signals:
    void continueClicked();
    void newgameClicked();
    void aboutClicked();
    void exitClicked();
private slots:
    void on_exitButton_clicked();
    void on_aboutButton_clicked();
    void on_newgameButton_clicked();
    void on_continueButton_clicked();

private:
    Ui::TitleScreen *ui;
    QFont Girassol;
};

#endif // TITLESCREEN_H
