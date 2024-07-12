#include "prologuegameplay.h"
#include "ui_prologuegameplay.h"
#include <QTime>
#include <QFile>
#include <QPainter>
#include <QStyleOption>

PrologueGameplay::PrologueGameplay(QWidget *parent, int sex) :
    QWidget(parent),
    ui(new Ui::PrologueGameplay)
{
    ui->setupUi(this);
    dialogCount = 0;
    if (sex == 0)
        readDialogFromFile(":/dialogs/dialogs/female/Level 0 - Prologue/MonologBohatera_01.txt");
    if (sex == 1)
        readDialogFromFile(":/dialogs/dialogs/male/Level 0 - Prologue/MonologBohatera_01.txt");
    animateText(dialogs[0]);
}

PrologueGameplay::~PrologueGameplay()
{
    delete ui;
}

void PrologueGameplay::animateText(QString text)
{
    if (text == "")
    {
        ui->dialogLabel->setText("");
        delay(5);
        return;
    }
    QString toShow = "";
    for (int i=0; i<text.length(); i++)
    {
        toShow += text[i];
        ui->dialogLabel->setText(toShow);
        delay(5);
    }
}

void PrologueGameplay::readDialogFromFile(QString path)
{
    int lineCount = 0;
    QFile myFile(path);
    if (myFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&myFile);
        while (stream.atEnd() == false)
        {
            dialogs[lineCount] = stream.readLine();
            lineCount++;
        }
    }
}

void PrologueGameplay::on_nextPageButton_clicked()
{
    ui->nextPageButton->setEnabled(false);
    dialogCount++;
    switch (dialogCount)
    {
    case 2:
        changeBackground(0);
        break;
    case 5:
        changeBackground(1);
        break;
    case 6:
        changeBackground(2);
        break;
    case 7:
        changeBackground(3);
        break;
    case 10:
        emit prologueEnded();
        return;
        break;
    }
    animateText(dialogs[dialogCount]);
    ui->nextPageButton->setEnabled(true);
}

void PrologueGameplay::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void PrologueGameplay::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void PrologueGameplay::changeBackground(int whichOne)
{
    QString pic2ver = "#PrologueGameplay {"
                    "border-image: url(:/images/images/Level 0 - Prologue/Pic2.png) 0 0 0 0 stretch stretch;"
                    "}"
                    "#mainWidget {"
                    "border-style: solid;"
                    "font-size: 22px;"
                    "font-weight: bold;"
                    "background-color: rgba(40,40,40,150);"
                    "padding-left: 18px;"
                    "}"
                    "#dialogLabel {"
                    "font-size: 28px;"
                    "color: rgb(180,180,180);"
                    "}"
                    "#nextPageButton {"
                    "border-style: solid;"
                    "font-weight: bold;"
                    "font-size: 18px;"
                    "background-color: qlineargradient(spread:pad, x1:0.29207, y1:0.389, x2:1, y2:0, stop:0 rgba(40,40,40,200), "
                                                      "stop:1 rgba(60,60,60,200));"
                    "color: rgb(180, 180, 180);"
                    "}"
                    "#nextPageButton:hover {"
                    "background-color: rgba(60,60,60, 150);"
                    "}";
    QString pic3ver = "#PrologueGameplay {"
                     "border-image: url(:/images/images/Level 0 - Prologue/Pic3.png) 0 0 0 0 stretch stretch;"
                     "}"
                     "#mainWidget {"
                     "border-style: solid;"
                     "font-size: 22px;"
                     "font-weight: bold;"
                     "background-color: rgba(40,40,40,150);"
                     "padding-left: 18px;"
                     "}"
                     "#dialogLabel {"
                     "font-size: 28px;"
                     "color: rgb(180,180,180);"
                     "}"
                     "#nextPageButton {"
                     "border-style: solid;"
                     "font-weight: bold;"
                     "font-size: 18px;"
                     "background-color: qlineargradient(spread:pad, x1:0.29207, y1:0.389, x2:1, y2:0, stop:0 rgba(40,40,40,200), "
                                                       "stop:1 rgba(60,60,60,200));"
                     "color: rgb(180, 180, 180);"
                     "}"
                     "#nextPageButton:hover {"
                     "background-color: rgba(60,60,60, 150);"
                     "}";
    QString pic4ver = "#PrologueGameplay {"
                      "border-image: url(:/images/images/Level 0 - Prologue/Pic4.png) 0 0 0 0 stretch stretch;"
                      "}"
                      "#mainWidget {"
                      "border-style: solid;"
                      "font-size: 22px;"
                      "font-weight: bold;"
                      "background-color: rgba(40,40,40,150);"
                      "padding-left: 18px;"
                      "}"
                      "#dialogLabel {"
                      "font-size: 28px;"
                      "color: rgb(180,180,180);"
                      "}"
                      "#nextPageButton {"
                      "border-style: solid;"
                      "font-weight: bold;"
                      "font-size: 18px;"
                      "background-color: qlineargradient(spread:pad, x1:0.29207, y1:0.389, x2:1, y2:0, stop:0 rgba(40,40,40,200), "
                                                        "stop:1 rgba(60,60,60,200));"
                      "color: rgb(180, 180, 180);"
                      "}"
                      "#nextPageButton:hover {"
                      "background-color: rgba(60,60,60, 150);"
                      "}";
    QString pic5ver = "#PrologueGameplay {"
                      "border-image: url(:/images/images/Level 0 - Prologue/Pic5.png) 0 0 0 0 stretch stretch;"
                      "}"
                      "#mainWidget {"
                      "border-style: solid;"
                      "font-size: 22px;"
                      "font-weight: bold;"
                      "background-color: rgba(40,40,40,150);"
                      "padding-left: 18px;"
                      "}"
                      "#dialogLabel {"
                      "font-size: 28px;"
                      "color: rgb(180,180,180);"
                      "}"
                      "#nextPageButton {"
                      "border-style: solid;"
                      "font-weight: bold;"
                      "font-size: 18px;"
                      "background-color: qlineargradient(spread:pad, x1:0.29207, y1:0.389, x2:1, y2:0, stop:0 rgba(40,40,40,200), "
                                                        "stop:1 rgba(60,60,60,200));"
                      "color: rgb(180, 180, 180);"
                      "}"
                      "#nextPageButton:hover {"
                      "background-color: rgba(60,60,60, 150);"
                      "}";
    switch (whichOne)
    {
    case 0:
        this->setStyleSheet(pic2ver);
        break;
    case 1:
        this->setStyleSheet(pic3ver);
        break;
    case 2:
        this->setStyleSheet(pic4ver);
        break;
    case 3:
        this->setStyleSheet(pic5ver);
        break;
    }
}
