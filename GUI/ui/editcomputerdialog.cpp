#include "editcomputerdialog.h"
#include "ui_editcomputerdialog.h"

#include "computerservice.h"

editComputerDialog::editComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editComputerDialog)
{
    ui->setupUi(this);
}

editComputerDialog::~editComputerDialog()
{
    delete ui;
}

void editComputerDialog::prepare(Computer computer)
{
    ui->lineEdit_id->insert(QString::number(computer.getId()));
    ui->lineEdit_computer_name->insert(QString::fromStdString(computer.getName()));

    if(computer.getType() == electronic)
        ui->radioButton_computer_type_electronic->toggle();
    else if(computer.getType() == mechatronic)
        ui->radioButton_computer_type_mechatronic->toggle();
    else if(computer.getType() == transistor)
        ui->radioButton_computer_type_transistor->toggle();
    else
        ui->radioButton_computer_type_other->toggle();

    if(computer.wasBuilt())
    {
        ui->radioButton_computer_yes->toggle();
        ui->lineEdit_computer_year_built->insert(QString::number(computer.getYearBuilt()));
    }
    else
        ui->radioButton_computer_no->toggle();
}

void editComputerDialog::on_radioButton_computer_yes_toggled(bool checked)
{
    if(checked)
        ui->lineEdit_computer_year_built->setEnabled(true);
    else
    {
        ui->lineEdit_computer_year_built->setEnabled(false);
        ui->lineEdit_computer_year_built->setText("");
    }
}

void editComputerDialog::on_pushButton_confirm_clicked()
{
    ui->label_computer_name_error->setText("");
    ui->label_computer_yearBuilt_error->setText("");

    int id = ui->lineEdit_id->text().toInt();
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
        success = computerService.editComputer(Computer(id, name.toStdString(), type, built.toInt()));
    }
    if(ui->radioButton_computer_no->isChecked())
        success = computerService.editComputer(Computer(id, name.toStdString(), type, 13337));

    if(success)
    {
        this->done(1);
    }
    else
    {
        this->done(-1);
    }
}

void editComputerDialog::on_pushButton_cancel_clicked()
{
    this->done(0);
}
