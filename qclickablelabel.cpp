#include "qclickablelabel.h"
#include <QPainter>
#include <QStyleOption>

QClickableLabel::QClickableLabel(QWidget* parent) : QLabel(parent) {}

QClickableLabel::~QClickableLabel() {}

void QClickableLabel::mousePressEvent(QMouseEvent *event) {emit clicked();}
