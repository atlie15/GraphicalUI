#ifndef EDITCONNECTIONDIALOG_H
#define EDITCONNECTIONDIALOG_H

#include "linkservice.h"
#include "scientist.h"
#include "computer.h"

#include <QDialog>

namespace Ui {
class editConnectionDialog;
}

class editConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editConnectionDialog(QWidget *parent = 0);
    ~editConnectionDialog();
    void prepare(std::vector<Computer> computers, Scientist scientist, int cPos);

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::editConnectionDialog *ui;
    LinkService linkService;
};

#endif // EDITCONNECTIONDIALOG_H
