#ifndef QCLICKABLEWIDGET_H
#define QCLICKABLEWIDGET_H

#include <QWidget>

class QClickableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QClickableWidget(QWidget* parent = nullptr);
    ~QClickableWidget();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // QCLICKABLEWIDGET_H
