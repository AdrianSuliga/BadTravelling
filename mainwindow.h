#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "titlescreen.h"
#include "titlebar.h"
#include "sexscreen.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    //TITLE BAR
    void maximizeIt();
    void unmaximizeIt();
    //TITLE SCREEN
    void setTitleScreen();
    //SEX SCREEN
    void transitionToSexScreen();
    //GLOBAL FUNCTIONALITIES
    void fadeAwayAnimation(QWidget *widget, int ms);
    void fadeInAnimation(QWidget *widget, int ms);
    void delay(int miliseconds);

private:
    Ui::MainWindow *ui;
    int sex; //0 - woman, 1 - man

    TitleBar *tB;

    TitleScreen *tS;
    SexScreen *sS;

    QVBoxLayout *mainLayout;
};
#endif // MAINWINDOW_H
