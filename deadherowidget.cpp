#include "deadherowidget.h"
#include "ui_deadherowidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QFontDatabase>

DeadHeroWidget::DeadHeroWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeadHeroWidget)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);
    ui->label->setFont(Girassol);
    ui->label->setStyleSheet("font-size: 60px; color: rgb(180,180,180);");
    ui->pushButton->setFont(Girassol);
    ui->pushButton->setStyleSheet("QPushButton {border-style: solid; color: rgb(180,180,180); font-size: 40px; margin: 10px;"
                                  "border-image: url(:/images/images/AppScreenArt/healingPotionHover.png) 0 0 0 0 stretch stretch;}"
                                  "QPushButton:hover {background-color: rgba(50,50,50,100); border-radius: 10px; border-style: solid;"
                                  "border-width: 2px; border-color: rgb(180,180,180);}");
}

DeadHeroWidget::~DeadHeroWidget()
{
    delete ui;
}

void DeadHeroWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
