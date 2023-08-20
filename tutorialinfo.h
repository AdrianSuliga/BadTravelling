#ifndef TUTORIALINFO_H
#define TUTORIALINFO_H

#include <QWidget>

namespace Ui {
class TutorialInfo;
}

class TutorialInfo : public QWidget
{
    Q_OBJECT

public:
    explicit TutorialInfo(QWidget *parent = nullptr);
    ~TutorialInfo();
signals:
    void endTutorial();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();

private:
    Ui::TutorialInfo *ui;
};

#endif // TUTORIALINFO_H
