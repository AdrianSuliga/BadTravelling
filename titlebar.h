#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QFont>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
signals:
    void minimise();
    void maximise();
    void userWantsToExit();
private slots:
    void on_minimiseButton_clicked();
    void on_maximiseButton_clicked();
    void on_exitButton_clicked();
private:
    Ui::TitleBar *ui;
    QFont Garissol;
    QWidget *m_parent;
    QPoint mousePos;
};

#endif // TITLEBAR_H
