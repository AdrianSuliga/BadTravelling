#include "deadherowidget.h"
#include "ui_deadherowidget.h"
#include <QPainter>
#include <QStyleOption>

DeadHeroWidget::DeadHeroWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeadHeroWidget)
{
    ui->setupUi(this);
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
