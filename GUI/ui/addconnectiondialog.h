#ifndef ADDCONNECTIONDIALOG_H
#define ADDCONNECTIONDIALOG_H

#include <QDialog>

#include "linkservice.h"
#include "scientistservice.h"
#include "computerservice.h"

namespace Ui {
class addConnectionDialog;
}

class addConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addConnectionDialog(QWidget *parent = 0);
    ~addConnectionDialog();

private slots:
    void on_pushButton_confirm_clicked();

    void on_pushButton_cancel_clicked();

private:
    void prepareCombo();
    Ui::addConnectionDialog *ui;
    LinkService linkService;
    ScientistService scientistService;
    ComputerService computerService;
};

#endif // ADDCONNECTIONDIALOG_H
