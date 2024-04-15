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
    ui->goBackLabel->setFont(Girassol);
    ui->resurectLabel->setFont(Girassol);
    ui->goBackLabel->setStyleSheet("font-size: 30px; color: rgb(180,180,180);");
    ui->resurectLabel->setStyleSheet("font-size: 30px; color: rgb(180,180,180);");
    ui->goBackWidget->setStyleSheet("#goBackWidget:hover {"
                                    "background-color: rgba(50,50,50,100); border-radius: 10px;"
                                    "border-style: solid; border-width: 2px; border-color: rgb(180,180,180);}");
    ui->goBackIcon->setStyleSheet("QLabel {border-style: solid; color: rgb(180,180,180); font-size: 40px; margin: 10px;"
                                  "border-image: url(:/images/images/AppScreenArt/TitleIcon.png) 0 0 0 0 stretch stretch;}");
    ui->resurectWidget->setStyleSheet("#resurectWidget:hover {"
                                      "background-color: rgba(50,50,50,100); border-radius: 10px;"
                                      "border-style: solid; border-width: 2px; border-color: rgb(180,180,180);}");
    ui->resurectIcon->setStyleSheet("QLabel {border-style: solid; color: rgb(180,180,180); font-size: 40px; margin: 10px;"
                                    "border-image: url(:/images/images/AppScreenArt/healingPotionHover.png) 0 0 0 0 stretch stretch;}");
    ui->goBackWidget->hide();
    connect(ui->resurectWidget, &QClickableWidget::clicked, this, [this]() {emit resurrectYourself();});
}

DeadHeroWidget::~DeadHeroWidget()
{
    delete ui;
}

void DeadHeroWidget::showGoBackButton()
{
    ui->goBackWidget->show();
    connect(ui->goBackWidget, &QClickableWidget::clicked, this, [this]() {emit goBackToFighting();});
}

void DeadHeroWidget::showResurectButton()
{
    ui->resurectWidget->show();
    connect(ui->resurectWidget, &QClickableWidget::clicked, this, [this]() {emit resurrectYourself();});
}

void DeadHeroWidget::hideGoBackButton()
{
    ui->goBackWidget->hide();
    disconnect(ui->goBackWidget, nullptr, nullptr, nullptr);
}

void DeadHeroWidget::hideResurectButton()
{
    ui->resurectWidget->hide();
    disconnect(ui->resurectWidget, nullptr, nullptr, nullptr);
}

void DeadHeroWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

