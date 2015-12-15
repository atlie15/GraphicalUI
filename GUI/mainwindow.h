#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "computerservice.h"
#include "scientistservice.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_view_computers_clicked();

    void on_button_add_computers_clicked();

    void on_button_view_scientists_clicked();

    void on_button_view_connections_clicked();

    void on_button_add_scientists_clicked();

    void on_button_add_connections_clicked();

    void on_table_current_view_clicked();

    void on_button_remove_clicked();

    void on_lineEdit_search_textChanged(const QString &arg1);

private:
    void displayAllScientists();
    void displayAllComputers();
    void displayAllConnections();
    void displayScientists(std::vector<Scientist> scientists);
    void displayComputers(std::vector<Computer> computers);
    void displayConnections(std::vector<Scientist> scientists);
    Ui::MainWindow *ui;
    int currentView;
    ComputerService computerService;
    ScientistService scientistService;
    std::vector<Scientist> currentlyDissplayedScientists;
    std::vector<Computer> currentlyDissplayedComputers;
};

#endif // MAINWINDOW_H
