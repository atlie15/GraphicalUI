#include "editscientistdialog.h"
#include "ui_editscientistdialog.h"

editScientistDialog::editScientistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editScientistDialog)
{
    ui->setupUi(this);
}

editScientistDialog::~editScientistDialog()
{
    delete ui;
}

bool editScientistDialog::editScientist(Scientist scientist)
{
    return scientistService.editScientist(scientist);
}

void editScientistDialog::prepare(Scientist scientist)
{
    ui->lineEdit_id->insert(QString::number(scientist.getId()));
    if(scientist.getSex() == female)
        ui->radioButton_scientist_female->toggle();
    else
        ui->radioButton_scientist_male->toggle();
    ui->lineEdit_scientist_name->insert(QString::fromStdString(scientist.getName()));
    ui->lineEdit_scientist_yearBorn->insert(QString::number(scientist.getYearBorn()));
    if(scientist.getYearDied() == 13337)
        ui->checkBox_scientist_alive->toggle();
    else
        ui->lineEdit_scientist_yearDeath->insert(QString::number(scientist.getYearDied()));
}

void editScientistDialog::on_pushButton_cancel_clicked()
{
    this->done(0);
}

void editScientistDialog::on_pushButton_confirm_clicked()
{
    ui->label_error_yearBorn->setText("");
    ui->label_scientist_yearDeath_error->setText("");
    ui->label_error_scientist_name->setText("");

    int id = ui->lineEdit_id->text().toInt();
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
        success = scientistService.editScientist(Scientist(id, name.toStdString(), sex, yearBorn.toInt(), 13337));
    else
        success = scientistService.editScientist(Scientist(id, name.toStdString(), sex, yearBorn.toInt(), yearDeath.toInt()));

    if(success)
    {
        this->done(1);
    }
    else
    {
        this->done(-1);
    }
}

void editScientistDialog::on_checkBox_scientist_alive_toggled(bool checked)
{
    if(checked)
    {
        ui->lineEdit_scientist_yearDeath->setDisabled(true);
        ui->lineEdit_scientist_yearDeath->setText("");
    }
    else
        ui->lineEdit_scientist_yearDeath->setDisabled(false);
}
