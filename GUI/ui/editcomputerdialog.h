#ifndef EDITCOMPUTERDIALOG_H
#define EDITCOMPUTERDIALOG_H

#include "computerservice.h"

#include <QDialog>

namespace Ui {
class editComputerDialog;
}

class editComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editComputerDialog(QWidget *parent = 0);
    ~editComputerDialog();
    void prepare(Computer computer);

private slots:
    void on_radioButton_computer_yes_toggled(bool checked);

    void on_pushButton_confirm_clicked();

private:
    Ui::editComputerDialog *ui;
    ComputerService computerService;
};

#endif // EDITCOMPUTERDIALOG_H
