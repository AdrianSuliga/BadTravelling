#include "titlebar.h"
#include "ui_titlebar.h"
#include <QStyleOption>
#include <QFontDatabase>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);

    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);

    ui->titleLabel->setFont(Girassol);
    m_parent = parent;
}

TitleBar::~TitleBar()
{
    delete ui;
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (m_parent->isFullScreen())
    {
        m_parent->setWindowState(Qt::WindowNoState);
        mousePos = event->globalPosition().toPoint() - m_parent->geometry().topLeft();
    }
    else if (event->buttons() & Qt::LeftButton)
            mousePos = event->globalPosition().toPoint() - m_parent->geometry().topLeft();
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
            m_parent -> move(event->globalPosition().toPoint() - mousePos);
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

