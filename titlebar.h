#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
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
};

#endif // TITLEBAR_H
