#ifndef EDITSCIENTISTDIALOG_H
#define EDITSCIENTISTDIALOG_H

#include "scientistservice.h"

#include <QDialog>

namespace Ui {
class editScientistDialog;
}

class editScientistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editScientistDialog(QWidget *parent = 0);
    ~editScientistDialog();
    bool editScientist(Scientist scientist);
    void prepare(Scientist scientist);
private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

    void on_checkBox_scientist_alive_toggled(bool checked);

private:
    Ui::editScientistDialog *ui;
    ScientistService scientistService;
};

#endif // EDITSCIENTISTDIALOG_H
