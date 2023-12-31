#include "recovereditemdialog.h"
#include "ui_recovereditemdialog.h"
#include <QFontDatabase>

RecoveredItemDialog::RecoveredItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoveredItemDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    int id = QFontDatabase::addApplicationFont(":/other/other/Fonts/Girassol-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont Girassol(family);
    ui->label->setFont(Girassol);
    ui->label->setStyleSheet("color: rgb(180,180,180); font-size: 40px;");
    ui->pushButton->setFont(Girassol);
    connect(ui->pushButton, &QPushButton::clicked, this, [this]{emit acceptMessage();});
}

RecoveredItemDialog::~RecoveredItemDialog()
{
    delete ui;
}

void RecoveredItemDialog::setIcon(int icon)
{
    switch (icon)
    {
    case 0:
        ui->label_2->setStyleSheet("border-image: url(:/images/images/AppScreenArt/keychain.png) 0 0 0 0 stretch stretch;");
        break;
    case 1:
        ui->label_2->setStyleSheet("border-image: url(:/images/images/AppScreenArt/kays.png) 0 0 0 0 stretch stretch;");
        break;
    case 2:
        ui->label_2->setStyleSheet("border-image: url(:/images/images/AppScreenArt/id.png) 0 0 0 0 stretch stretch;");
        break;
    case 3:
        ui->label_2->setStyleSheet("border-image: url(:/images/images/AppScreenArt/wallet.png) 0 0 0 0 stretch stretch;");
        break;
    }
}
