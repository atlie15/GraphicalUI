#include "editconnectiondialog.h"
#include "ui_editconnectiondialog.h"

editConnectionDialog::editConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editConnectionDialog)
{
    ui->setupUi(this);
}

editConnectionDialog::~editConnectionDialog()
{
    delete ui;
}

void editConnectionDialog::prepare(std::vector<Computer> computers, Scientist scientist, int cPos)
{
    ui->combo_scientists->addItem(QString::fromStdString(scientist.getName()), scientist.getId());

    for (unsigned int i(0); i < computers.size(); i++)
    {
        Computer tempCPU = computers.at(i);

        QString name = QString::fromStdString(tempCPU.getName());
        QString id = QString::number(tempCPU.getId());

        ui->combo_computers->addItem(name, id);
    }

    ui->combo_computers->setCurrentIndex(cPos);
}

void editConnectionDialog::on_pushButton_cancel_clicked()
{
    this->done(0);
}

void editConnectionDialog::on_pushButton_confirm_clicked()
{
    std::string computer, scientist;

    computer = ui->combo_computers->currentData().toString().toStdString();
    scientist = ui->combo_scientists->currentData().toString().toStdString();

    if(linkService.editLink(scientist, computer))
    {
        this->done(1);
    }
    else
        this->done(-1);
}
