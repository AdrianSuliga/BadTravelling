#include "deadenemywidget.h"
#include "ui_deadenemywidget.h"
#include <QPainter>
#include <QStyleOption>
#include <QFontDatabase>
#include <QPushButton>
#include <QWidget>

DeadEnemyWidget::DeadEnemyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeadEnemyWidget)
{
    ui->setupUi(this);
    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);
    ui->label->setFont(Girassol);
    ui->label->setStyleSheet("font-size: 60px; color: rgb(180,180,180);");
    ui->pushButton->setFont(Girassol);
    ui->pushButton->setStyleSheet("QPushButton {border-style: solid; color: rgb(180,180,180); font-size: 40px; margin: 10px;"
                                  "border-image: url(:/images/images/AppScreenArt/TitleIcon.png) 0 0 0 0 stretch stretch;}"
                                  "QPushButton:hover {background-color: rgba(50,50,50,100); border-radius: 10px; border-style: solid;"
                                  "border-width: 2px; border-color: rgb(180,180,180);}");
    ui->bossButton->setStyleSheet("QPushButton {border-style: solid; color: rgb(180,180,180); font-size: 40px; margin: 10px;"
                                  "border-image: url() 0 0 0 0 stretch stretch;}"
                                  "QPushButton:hover {background-color: rgba(50,50,50,100); border-radius: 10px; border-style: solid;"
                                  "border-width: 2px; border-color: rgb(180,180,180);}");
    ui->bossButton->hide();
}

DeadEnemyWidget::~DeadEnemyWidget()
{
    delete ui;
}

void DeadEnemyWidget::showBossButton()
{
    ui->bossButton->show();
    connect(ui->bossButton, &QPushButton::clicked, this, [this]() {
        delete ui->bossButton;
        emit fightBoss();
    });
}

void DeadEnemyWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DeadEnemyWidget::on_pushButton_clicked()
{
    emit transitionToNextPhase();
}

