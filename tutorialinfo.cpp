#include "tutorialinfo.h"
#include "ui_tutorialinfo.h"
#include <QStyleOption>
#include <QFontDatabase>
#include <QPainter>

TutorialInfo::TutorialInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TutorialInfo)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    ui->attackActionLabel->setFont(Girassol);
    ui->defenseActionLabel->setFont(Girassol);
    ui->healActionLabel->setFont(Girassol);
    ui->firstLabel->setFont(Girassol);
    ui->secondLabel->setFont(Girassol);
    ui->pushButton->setFont(Girassol);
}

TutorialInfo::~TutorialInfo()
{
    delete ui;
}

void TutorialInfo::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TutorialInfo::on_pushButton_clicked() {emit endTutorial();}

