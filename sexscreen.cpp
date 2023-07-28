#include "sexscreen.h"
#include "ui_sexscreen.h"
#include <QPainter>
#include <QStyleOption>
#include <QTime>
#include <QFontDatabase>

SexScreen::SexScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SexScreen)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/other/other/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    ui->titleLabel->setFont(family);
}

SexScreen::~SexScreen()
{
    delete ui;
}

void SexScreen::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void SexScreen::animateText()
{
    QString showThis = "";
    QString textToAnimate = ui->titleLabel->text();
    for (int i=0; i<textToAnimate.length(); i++)
    {
        showThis += textToAnimate[i];
        ui->titleLabel->setText(showThis);
        delay(50);
    }
}

void SexScreen::delay(int miliseconds)
{
    QTime dieTime = QTime::currentTime().addMSecs(miliseconds);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
