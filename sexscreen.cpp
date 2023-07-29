#include "sexscreen.h"
#include "ui_sexscreen.h"
#include <QPainter>
#include <QStyleOption>
#include <QTime>
#include <QFontDatabase>
#include <QDebug>

SexScreen::SexScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SexScreen)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/other/other/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    ui->titleLabel->setFont(family);
    connect(ui->manWidget, &QClickableWidget::clicked, this, [this]() {emit manChosen();});
    connect(ui->womanWidget, &QClickableWidget::clicked, this, [this]() {emit womanChosen();});
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


