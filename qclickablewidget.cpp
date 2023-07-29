#include "qclickablewidget.h"
#include <QPainter>
#include <QStyleOption>

QClickableWidget::QClickableWidget(QWidget* parent) : QWidget(parent) {}

QClickableWidget::~QClickableWidget() {}

void QClickableWidget::mousePressEvent(QMouseEvent *event) {emit clicked();}
void QClickableWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
