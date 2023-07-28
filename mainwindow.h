#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "titlescreen.h"
#include "titlebar.h"

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

private:
    Ui::MainWindow *ui;
    TitleScreen *tS;
    TitleBar *tB;

    QVBoxLayout *mainLayout;
};
#endif // MAINWINDOW_H
