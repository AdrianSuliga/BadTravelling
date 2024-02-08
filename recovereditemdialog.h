#ifndef RECOVEREDITEMDIALOG_H
#define RECOVEREDITEMDIALOG_H

#include <QDialog>

namespace Ui {
class RecoveredItemDialog;
}

class RecoveredItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecoveredItemDialog(QWidget *parent = nullptr);
    ~RecoveredItemDialog();
    void setIcon(int icon);
signals:
    void acceptMessage();
private:
    Ui::RecoveredItemDialog *ui;
};

#endif // RECOVEREDITEMDIALOG_H
