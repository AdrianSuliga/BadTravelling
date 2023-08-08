#ifndef PROLOGUEGAMEPLAY_H
#define PROLOGUEGAMEPLAY_H

#include <QWidget>

namespace Ui {
class PrologueGameplay;
}

class PrologueGameplay : public QWidget
{
    Q_OBJECT

public:
    explicit PrologueGameplay(QWidget *parent = nullptr);
    ~PrologueGameplay();
private slots:
    void animateText(QString text);
    void readDialogFromFile(QString path);
    void delay(int ms);
    void changeBackground(int whichOne);
    void on_nextPageButton_clicked();
protected:
    void paintEvent(QPaintEvent *event);
signals:
    void prologueEnded();
private:
    Ui::PrologueGameplay *ui;
    int dialogCount;
    QString dialogs[9];
};

#endif // PROLOGUEGAMEPLAY_H
