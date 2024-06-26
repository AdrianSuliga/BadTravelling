#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QMediaPlayer>
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
    setWindowIcon(QIcon(QPixmap(":/images/images/AppScreenArt/TitleIcon.png")));
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
    tB = new TitleBar(this);
    tB -> setFixedHeight(30);

    mainLayout = new QVBoxLayout(ui->centralwidget);
    mainLayout -> insertWidget(0, tB);
    mainLayout -> insertWidget(1, tS);

    //connect(tS, &TitleScreen::continueClicked, this, );
    connect(tS, &TitleScreen::newgameClicked, this, &MainWindow::setSexScreen);
    //connect(tS, &TitleScreen::aboutClicked, this );
    connect(tS, &TitleScreen::exitClicked, this, &MainWindow::close);

    connect(tB, &TitleBar::minimise, this, &MainWindow::showMinimized);
    connect(tB, &TitleBar::maximise, this, &MainWindow::unmaximizeIt);
    connect(tB, &TitleBar::userWantsToExit, this, &MainWindow::close);

    player = new QMediaPlayer();
    audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl("qrc:/other/other/Music/TitleScreenBackgroundMusic.mp3"));
    audioOutput->setVolume(50);
    player->play();
}

void MainWindow::setSexScreen()
{
    fadeAwayAnimation(tS, 500);
    player->stop();
    delete tS;
    tS = nullptr;

    sS = new SexScreen();
    mainLayout -> insertWidget(1, sS);
    fadeInAnimation(sS, 500);

    //connect(sS, &SexScreen::manChosen, this, [this]() {sex = 1; setPrologueScreen();});
    //connect(sS, &SexScreen::womanChosen, this, [this]() {sex = 0; setPrologueScreen();});
    connect(sS, &SexScreen::manChosen, this, [this]() {sex = 1; setGameScreen();});
    connect(sS, &SexScreen::womanChosen, this, [this]() {sex = 0; setGameScreen();});
}

void MainWindow::setPrologueScreen()
{
    fadeAwayAnimation(sS, 500);
    delete sS;
    sS = nullptr;

    pS = new PrologueScreen(this, sex);
    mainLayout -> insertWidget(1, pS);
    fadeInAnimation(pS, 2000);
    switch (sex)
    {
    case 0:
        animatePrologueText(":/dialogs/dialogs/female/Level 0 - Prologue/PrologWstep.txt");
        break;
    case 1:
        animatePrologueText(":/dialogs/dialogs/male/Level 0 - Prologue/PrologWstep.txt");
        break;
    default:
        QMessageBox::critical(this, "ERROR", "Cannot initialize dialog");
        return;
    }
    setPrologueGameplayScreen();
}
void MainWindow::animatePrologueText(QString path)
{
    QFile textfile(path);
    int lineCount = 1;
    if (textfile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&textfile);
        while (stream.atEnd() == false)
        {
            QString line = stream.readLine();
            if (line == "")
            {
                pS->animateText("");
                delay(1000);
            }
            else if (lineCount == 4 || lineCount == 7 || lineCount == 9 || lineCount == 10)
            {
                pS->animateText(line);
                fadeInAnimation(pS, 3000);
                delay(5000);
                fadeAwayAnimation(pS, 1000);
            }
            else
            {
                pS->animateText(line);
                fadeInAnimation(pS, 3000);
                delay(2000);
                fadeAwayAnimation(pS, 1000);
            }
            lineCount++;
        }
    }
}

void MainWindow::setPrologueGameplayScreen()
{
    pG = new PrologueGameplay(this, sex);
    delete pS;
    pS = nullptr;
    mainLayout -> insertWidget(1, pG);
    fadeInAnimation(pG, 2000);

    connect(pG, &PrologueGameplay::prologueEnded, this, &MainWindow::setGameScreen);
}

void MainWindow::setGameScreen()
{
    fadeAwayAnimation(sS, 500);
    delete sS;
    sS = nullptr;

    gS = new GameScreen(this, sex);
    mainLayout -> insertWidget(1, gS);
    fadeInAnimation(gS, 2000);

    connect(gS, &GameScreen::gameEnded, this, &MainWindow::end_credits);
}

void MainWindow::end_credits()
{
    fadeAwayAnimation(gS, 2000);
    delete gS;
    gS = nullptr;

    pS = new PrologueScreen(this, sex);
    mainLayout -> insertWidget(1, pS);
    fadeInAnimation(pS, 2000);
    animatePrologueText(":/dialogs/dialogs/male/Level 9 - Ending/Credits.txt");
    delete pS;
    delete tB;
    delete mainLayout;
    delete player;
    delete audioOutput;
    pS = nullptr;
    tB = nullptr;
    mainLayout = nullptr;
    player = nullptr;
    audioOutput = nullptr;

    settings.clear();
    setTitleScreen();
}

void MainWindow::fadeAwayAnimation(QWidget *widget, int ms)
{
    QGraphicsOpacityEffect *fadeAwayEffect = new QGraphicsOpacityEffect(widget);
    widget->setGraphicsEffect(fadeAwayEffect);
    QPropertyAnimation *fadeAwayAnimation = new QPropertyAnimation(fadeAwayEffect, "opacity");
    fadeAwayAnimation -> setDuration(ms);
    fadeAwayAnimation -> setStartValue(1);
    fadeAwayAnimation -> setEndValue(0);
    fadeAwayAnimation -> setEasingCurve(QEasingCurve::OutBack);
    fadeAwayAnimation -> start(QPropertyAnimation::DeleteWhenStopped);
    delay(ms);
}
void MainWindow::fadeInAnimation(QWidget *widget, int ms)
{
    QGraphicsOpacityEffect *fadeInEffect = new QGraphicsOpacityEffect(widget);
    widget -> setGraphicsEffect(fadeInEffect);
    QPropertyAnimation *fadeInAnimation = new QPropertyAnimation(fadeInEffect, "opacity");
    fadeInAnimation -> setDuration(ms);
    fadeInAnimation -> setStartValue(0);
    fadeInAnimation -> setEndValue(1);
    fadeInAnimation -> setEasingCurve(QEasingCurve::InBack);
    fadeInAnimation -> start(QPropertyAnimation::DeleteWhenStopped);
    delay(ms);
}
void MainWindow::delay(int miliseconds)
{
    QTime dieTime = QTime::currentTime().addMSecs(miliseconds);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

