#include "titlescreen.h"
#include "ui_titlescreen.h"
#include <QStyleOption>
#include <QPainter>

TitleScreen::TitleScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleScreen)
{
    ui->setupUi(this);
}

TitleScreen::~TitleScreen()
{
    delete ui;
}

void TitleScreen::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TitleScreen::on_exitButton_clicked()
{
    emit exitClicked();
}


void TitleScreen::on_aboutButton_clicked()
{
    emit aboutClicked();
}


void TitleScreen::on_newgameButton_clicked()
{
    emit newgameClicked();
}


void TitleScreen::on_continueButton_clicked()
{
    emit continueClicked();
}

