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
    ui->label_computer_name_error->setText("");
    ui->label_computer_yearBuilt_error->setText("");

    QString name = ui->lineEdit_computer_name->text();
    computerType type;
    QString built = ui->lineEdit_computer_year_built->text();
    bool success = false;
    bool isError = false;
    if(name.isEmpty())
    {
        ui->label_computer_name_error->setText("<span style = 'color: red'>Name cannot be empty </span>");
        isError = true;
    }
    if(built.isEmpty() && ui->radioButton_computer_yes->isChecked())
    {
        ui->label_computer_yearBuilt_error->setText("<span style = 'color: red'>Please enter year</span>");
        isError = true;
    }

    int wasBuilt = built.toInt();

    if(wasBuilt < 0 || wasBuilt > 2015)
    {
        ui->label_computer_yearBuilt_error->setText("<span style = 'color: red'>Invalid year</span>");
        isError = true;
    }


    if(isError)
        return;

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
        success = computerService.addComputer(Computer(name.toStdString(), type, built.toInt()));
    }
    if(ui->radioButton_computer_no->isChecked())
        success = computerService.addComputer(Computer(name.toStdString(), type));

    if(success)
    {
        this->done(1);
    }
    else
    {
        this->done(-1);
    }
}

void addComputerDialog::on_radioButton_computer_yes_toggled(bool checked)
{
    if(checked)
        ui->lineEdit_computer_year_built->setEnabled(true);
    else
        ui->lineEdit_computer_year_built->setEnabled(false);
}

void addComputerDialog::on_pushButton_cancel_clicked()
{
    this->done(0);
}
