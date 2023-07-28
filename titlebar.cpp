#include "titlebar.h"
#include "ui_titlebar.h"
#include <QStyleOption>
#include <QPainter>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
}

TitleBar::~TitleBar()
{
    delete ui;
}

void TitleBar::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TitleBar::on_minimiseButton_clicked()
{
    emit minimise();
}


void TitleBar::on_maximiseButton_clicked()
{
    emit maximise();
}


void TitleBar::on_exitButton_clicked()
{
    emit userWantsToExit();
}

