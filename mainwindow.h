#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "titlescreen.h"
#include "titlebar.h"
#include "sexscreen.h"
#include "prologuescreen.h"

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
    void setSexScreen();
    //PROLOGUE SCREEN
    void setPrologueScreen();
    void animatePrologueText(QString path);
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
    PrologueScreen *pS;

    QVBoxLayout *mainLayout;
};
#endif // MAINWINDOW_H
