#include "addconnectiondialog.h"
#include "ui_addconnectiondialog.h"

addConnectionDialog::addConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addConnectionDialog)
{
    ui->setupUi(this);
    prepareCombo();
}

addConnectionDialog::~addConnectionDialog()
{
    delete ui;
}

void addConnectionDialog::prepareCombo()
{
    std::vector<Scientist> scientists = scientistService.getAllScientists("name", true);

    for (unsigned int i(0); i < scientists.size(); i++)
    {
        Scientist tempNerd = scientists.at(i);

        QString name = QString::fromStdString(tempNerd.getName());
        QString id = QString::number(tempNerd.getId());

        ui->combo_scientists->addItem(name, id);
    }

    std::vector<Computer> computers = computerService.getAllComputers("name", true);

    for (unsigned int i(0); i < computers.size(); i++)
    {
        Computer tempCPU = computers.at(i);

        QString name = QString::fromStdString(tempCPU.getName());
        QString id = QString::number(tempCPU.getId());

        ui->combo_computers->addItem(name, id);
    }
}

void addConnectionDialog::on_pushButton_confirm_clicked()
{
    std::string computer, scientist;

    computer = ui->combo_computers->currentData().toString().toStdString();
    scientist = ui->combo_scientists->currentData().toString().toStdString();

    if(linkService.addLink(scientist, computer))
    {
        this->done(1);
    }
    else
        this->done(-1);
}

void addConnectionDialog::on_pushButton_cancel_clicked()
{
    this->done(1);
}
