#include "addscientistdialog.h"
#include "ui_addscientistdialog.h"
#include "utilities/utils.h"

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
    ui->label_error_yearBorn->setText("");
    ui->label_scientist_yearDeath_error->setText("");
    ui->label_error_scientist_name->setText("");
    QString name = ui->lineEdit_scientist_name->text();
    sexType sex;
    QString yearBorn = ui->lineEdit_scientist_yearBorn->text();
    QString yearDeath = ui->lineEdit_scientist_yearDeath->text();
    bool success = false;
    bool isError = false;

    if(name.isEmpty())
    {
        ui->label_error_scientist_name->setText("<span style = 'color: red'>Name cannot be empty </span>");
        isError = true;
    }
    if(yearBorn.isEmpty())
    {
        ui->label_error_yearBorn->setText("<span style = 'color: red'>Enter a valid year for Year Born</span>");
        isError = true;
    }
    if(yearDeath.isEmpty() && !(ui->checkBox_scientist_alive->isChecked()))
    {
        ui->label_scientist_yearDeath_error->setText("<span style = 'color: red'>Please enter a year</span>");
        isError = true;
    }

    int yb = yearBorn.toInt();
    int yd = yearDeath.toInt();

    if(yb <= 0 || yb > 2015 )
    {
        ui->label_error_yearBorn->setText("<span style = 'color: red'>Invalid year</span>");
        isError = true;
    }
    if(((yd <= 0 || yd > 2015) || (yd <= yb)) && !(ui->checkBox_scientist_alive->isChecked()))
    {
        ui->label_scientist_yearDeath_error->setText("<span style = 'color: red'>Invalid year</span>");
        isError = true;
    }

    if(isError)
        return;

    if(ui->radioButton_scientist_female->isChecked())
    {
        sex = female;
    }
    if(ui->radioButton_scientist_male->isChecked())
    {
        sex = male;
    }

    if(ui->checkBox_scientist_alive->isChecked())
        success = scientistService.addScientist(Scientist(name.toStdString(), sex, yearBorn.toInt()));
    else
        success = scientistService.addScientist(Scientist(name.toStdString(), sex, yearBorn.toInt(), yearDeath.toInt()));

    if(success)
    {
        this->done(1);
    }
    else
    {
        this->done(-1);
    }
}

void addScientistDialog::on_checkBox_scientist_alive_toggled(bool checked)
{
    if(checked)
    {
       ui->lineEdit_scientist_yearDeath->setEnabled(false);
       ui->lineEdit_scientist_yearDeath->setText("");
    }
    else
        ui->lineEdit_scientist_yearDeath->setEnabled(true);
}


void addScientistDialog::on_pushButton_return_to_main_menu_clicked()
{
    this->done(0);
}
