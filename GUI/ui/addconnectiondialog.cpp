#include "addconnectiondialog.h"
#include "ui_addconnectiondialog.h"

addConnectionDialog::addConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addConnectionDialog)
{
    ui->setupUi(this);
}

addConnectionDialog::~addConnectionDialog()
{
    delete ui;
}
