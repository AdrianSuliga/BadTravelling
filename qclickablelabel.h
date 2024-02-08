#ifndef QCLICKABLELABEL_H
#define QCLICKABLELABEL_H


#include <QLabel>

class QClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QClickableLabel(QWidget* parent = nullptr);
    ~QClickableLabel();
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // QCLICKABLELABEL_H
