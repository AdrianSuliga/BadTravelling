#include "titlebar.h"
#include "ui_titlebar.h"
#include <QStyleOption>
#include <QFontDatabase>
#include <QPainter>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/other/other/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    ui->titleLabel->setFont(Girassol);
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

void TitleBar::on_minimiseButton_clicked() {emit minimise();}
void TitleBar::on_maximiseButton_clicked() {emit maximise();}
void TitleBar::on_exitButton_clicked() {emit userWantsToExit();}

