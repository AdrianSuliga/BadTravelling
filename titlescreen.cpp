#include "titlescreen.h"
#include "ui_titlescreen.h"
#include <QStyleOption>
#include <QPainter>
#include <QFontDatabase>

TitleScreen::TitleScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleScreen)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    ui->titleLabel->setFont(Girassol);
    ui->continueButton->setFont(Girassol);
    ui->newgameButton->setFont(Girassol);
    ui->aboutButton->setFont(Girassol);
    ui->exitButton->setFont(Girassol);
    ui->titleLabel->setStyleSheet("font-size: 80px;");
    ui->continueButton->setStyleSheet("font-size: 40px;");
    ui->newgameButton->setStyleSheet("font-size: 40px;");
    ui->aboutButton->setStyleSheet("font-size: 40px;");
    ui->exitButton->setStyleSheet("font-size: 40px;");
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

void TitleScreen::activate_continue_button()
{
    ui->continueButton->setEnabled(true);
}

void TitleScreen::deactivate_continue_button()
{
    ui->continueButton->setEnabled(false);
    ui->continueButton->setStyleSheet("QPushButton {"
                                      "border-style: solid;"
                                      "font-size: 40px;"
                                      "font-weight: bold;"
                                      "border-radius: 20px;"
                                      "background-color: qlineargradient(spread:pad, x1:0.29207, y1:0.389, x2:1, y2:0, stop:0 rgba(40,40,40,200), stop:1 rgba(60,60,60,200));"
                                      "color: rgb(120, 120, 120);"
                                      "}"
                                      "QPushButton:hover {}");
}

void TitleScreen::on_exitButton_clicked() {emit exitClicked();}
void TitleScreen::on_aboutButton_clicked() {emit aboutClicked();}
void TitleScreen::on_newgameButton_clicked() {emit newgameClicked();}
void TitleScreen::on_continueButton_clicked() {emit continueClicked();}

