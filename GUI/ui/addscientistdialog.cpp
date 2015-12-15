#include "addscientistdialog.h"
#include "ui_addscientistdialog.h"


addScientistDialog::addScientistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addScientistDialog)
{
    ui->setupUi(this);
}

addScientistDialog::~addScientistDialog()
{
    delete ui;
}

void addScientistDialog::on_Button_add_scientist_clicked()
{
    QString name = ui->lineEdit_scientist_name->text();
    QString yearBorn = ui->lineEdit_scientist_yearBorn->text();
    QString yearDeath = ui->lineEdit_scientist_yearDeath->text();
    bool success = false;

    if(name.isEmpty())
    {
        ui->label_error_scientist_name->setText("<span style = 'color: red'>Name cannot be empty </span>");
        return;
    }
    if(yearBorn.isEmpty())
    {
        ui->label_error_yearBorn->setText("<span style = 'color: red'>Year born cannot be empty </span>");
        return;
    }
    if(ui->radioButton_scientist_female->isChecked())
    {
        success = scientistService.addScientist(Scientist(name.toStdString(), female, yearBorn.toInt(), yearDeath.toInt()));
    }
    if(ui->radioButton_scientist_male->isChecked())
    {
        success = scientistService.addScientist(Scientist(name.toStdString(), male, yearBorn.toInt(), yearDeath.toInt()));
    }

    if(success)
    {
        this->done(0);
    }
    else
    {
        this->done(-1);
        //error
    }
}
