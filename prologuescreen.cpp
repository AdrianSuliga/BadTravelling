#include "prologuescreen.h"
#include "ui_prologuescreen.h"
#include <QFontDatabase>
#include <QTime>

PrologueScreen::PrologueScreen(QWidget *parent, int sex) :
    QWidget(parent),
    ui(new Ui::PrologueScreen)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/other/other/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);
    ui->infoLabel->setFont(Girassol);
}

PrologueScreen::~PrologueScreen()
{
    delete ui;
}

void PrologueScreen::animateText(QString text)
{
    /*QString current = "";
    for (int i=0; i<text.length(); i++)
    {
        current += text[i];
        ui->infoLabel->setText(current);
        delay(50);
    }*/
    ui->infoLabel->setText(text);
}
void PrologueScreen::delay(int ms)
{
    QTime dieTime = QTime::currentTime().addMSecs(ms);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
