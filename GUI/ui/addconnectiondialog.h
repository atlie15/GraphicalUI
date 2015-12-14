#ifndef ADDCONNECTIONDIALOG_H
#define ADDCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class addConnectionDialog;
}

class addConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addConnectionDialog(QWidget *parent = 0);
    ~addConnectionDialog();

private:
    Ui::addConnectionDialog *ui;
};

#endif // ADDCONNECTIONDIALOG_H
