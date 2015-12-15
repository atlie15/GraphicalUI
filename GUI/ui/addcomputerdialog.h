#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>
#include "computerservice.h"

namespace Ui {
class addComputerDialog;
}

class addComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addComputerDialog(QWidget *parent = 0);
    ~addComputerDialog();

private slots:
    void on_pushButton_add_computer_clicked();

    void on_radioButton_computer_yes_toggled(bool checked);

private:
    Ui::addComputerDialog *ui;
    ComputerService computerService;
};

#endif // ADDCOMPUTERDIALOG_H
