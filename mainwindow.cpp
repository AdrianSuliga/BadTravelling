#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowFullScreen);
    setWindowTitle("NIEFORTUNNA PODRÓŻ");
    setTitleScreen();
    ui->centralwidget->layout()->setContentsMargins(0, 0, 0, 0);
    ui->centralwidget->layout()->setSpacing(0);

    sex = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::maximizeIt()
{
    setWindowState(Qt::WindowFullScreen);
    disconnect(tB, &TitleBar::maximise, this, &MainWindow::maximizeIt);
    connect(tB, &TitleBar::maximise, this, &MainWindow::unmaximizeIt);
}
void MainWindow::unmaximizeIt()
{
    setWindowState(Qt::WindowNoState);
    disconnect(tB, &TitleBar::maximise, this, &MainWindow::unmaximizeIt);
    connect(tB, &TitleBar::maximise, this, &MainWindow::maximizeIt);
}

void MainWindow::setTitleScreen()
{
    tS = new TitleScreen();
    tB = new TitleBar();
    tB -> setFixedHeight(30);

    mainLayout = new QVBoxLayout(ui->centralwidget);
    mainLayout -> insertWidget(0, tB);
    mainLayout -> insertWidget(1, tS);

    //connect(tS, &TitleScreen::continueClicked, this, );
    connect(tS, &TitleScreen::newgameClicked, this, &MainWindow::transitionToSexScreen);
    //connect(tS, &TitleScreen::aboutClicked, this );
    connect(tS, &TitleScreen::exitClicked, this, &MainWindow::close);

    connect(tB, &TitleBar::minimise, this, &MainWindow::showMinimized);
    connect(tB, &TitleBar::maximise, this, &MainWindow::unmaximizeIt);
    connect(tB, &TitleBar::userWantsToExit, this, &MainWindow::close);
}

void MainWindow::transitionToSexScreen()
{
    fadeAwayAnimation(tS);
    delay(1000);
    delete tS;
    setSexScreen();
}

void MainWindow::setSexScreen()
{
    sS = new SexScreen();

    mainLayout -> insertWidget(1, sS);
    sS -> animateText();
}

void MainWindow::fadeAwayAnimation(QWidget *widget)
{
    QGraphicsOpacityEffect *fadeAwayEffect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(fadeAwayEffect);
    QPropertyAnimation *fadeAwayAnimation = new QPropertyAnimation(fadeAwayEffect, "opacity");
    fadeAwayAnimation -> setDuration(1000);
    fadeAwayAnimation -> setStartValue(1);
    fadeAwayAnimation -> setEndValue(0);
    fadeAwayAnimation -> setEasingCurve(QEasingCurve::OutBack);
    fadeAwayAnimation -> start(QPropertyAnimation::DeleteWhenStopped);
}
void MainWindow::delay(int miliseconds)
{
    QTime dieTime = QTime::currentTime().addMSecs(miliseconds);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

