#include "addcomputerdialog.h"
#include "ui_addcomputerdialog.h"
#include "computer.h"
#include "addcomputerdialog.h"

addComputerDialog::addComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addComputerDialog)
{
    ui->setupUi(this);
}

addComputerDialog::~addComputerDialog()
{
    delete ui;
}

void addComputerDialog::on_pushButton_add_computer_clicked()
{
    QString name = ui->lineEdit_computer_name->text();
    computerType type;
    QString built = ui->lineEdit_computer_year_built->text();
    bool success = false;

    if(ui->radioButton_computer_type_electronic->isChecked())
    {
        type = electronic;
    }
    if(ui->radioButton_computer_type_mechatronic->isChecked())
    {
        type = mechatronic;
    }
    if(ui->radioButton_computer_type_transistor->isChecked())
    {
        type = transistor;
    }
    if(ui->radioButton_computer_type_other->isChecked())
    {
        type = other;
    }

    if(ui->radioButton_computer_yes->isChecked())
    {
        ui->lineEdit_computer_year_built->setEnabled(true);
    }


    success = computerService.addComputer(Computer(name.toStdString(), type, built.toInt()));

    if(success)
    {
        this->done(0);
    }
    else
    {
        //this-done(-1);
    }
}
/*
if(ui->checkBox_scientist_alive->isChecked())
    success = scientistService.addScientist(Scientist(name.toStdString(), sex, yearBorn.toInt()));
else
    success = scientistService.addScientist(Scientist(name.toStdString(), sex, yearBorn.toInt(), yearDeath.toInt()));


    /*
    if(name.isEmpty())
    {
        ui->label_error_scientist_name->setText("<span style = 'color: red'>Name cannot be empty </span>");
        return;
    }
    if(yearBorn.isEmpty())
    {
        ui->label_error_yearBorn->setText("<span style = 'color: red'>Year born cannot be empty </span>");
        return;
    }*/
