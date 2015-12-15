#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addscientistdialog.h"
#include "addcomputerdialog.h"
#include "addconnectiondialog.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    displayAllScientists();
    currentView = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayAllScientists()
{
    vector<Scientist> scientists = scientistService.getAllScientists("name", true);

    displayScientists(scientists);
}

void MainWindow::displayAllComputers()
{
    vector<Computer> computers = computerService.getAllComputers("name", true);

    displayComputers(computers);
}

void MainWindow::displayAllConnections()
{
    vector<Scientist> scientists = scientistService.getAllScientists("name", true);

    displayConnections(scientists);
}

void MainWindow::displayComputers(std::vector<Computer> computers)
{
    ui->table_current_view->clear();

    ui->table_current_view->setColumnCount(3);
    for(unsigned int i(0); i < 3; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "Name" << "Type" << "Year Built");

    ui->table_current_view->setRowCount(computers.size());

    for(unsigned int row(0); row < computers.size(); row++)
    {
        Computer tempComputer = computers.at(row);

        QString name = QString::fromStdString(tempComputer.getName());

        QString type = QString::fromStdString(tempComputer.getTypeName());

        QString yearBuilt;
        if(tempComputer.getYearBuilt() == 13337)
            yearBuilt = "Not built";
        else
            yearBuilt = QString::number(tempComputer.getYearBuilt());


        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(type));
        ui->table_current_view->setItem(row, 2, new QTableWidgetItem(yearBuilt));
    }
}

void MainWindow::displayConnections(std::vector<Scientist> scientists)
{
    ui->table_current_view->clear();

    ui->table_current_view->setColumnCount(2);
    for(unsigned int i(0); i < 2; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "Scientist Name" << "Computers");

    ui->table_current_view->setRowCount(scientists.size());

    for(unsigned int row(0); row < scientists.size(); row++)
    {
        Scientist tempScientist = scientists.at(row);
        vector<Computer*> computers = tempScientist.getComputers();

        QString sName = QString::fromStdString(tempScientist.getName());
        QString noCPU = QString::number(computers.size());

        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(sName));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(noCPU));
    }
}

void MainWindow::displayScientists(std::vector<Scientist> scientists)
{
    ui->table_current_view->clear();

    ui->table_current_view->setColumnCount(4);
    for(unsigned int i(0); i < 4; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "Name" << "Gender" << "Year Born" << "Year Died");
    ui->table_current_view->setRowCount(scientists.size());

    for(unsigned int row(0); row < scientists.size(); row++)
    {
        Scientist tempScientist = scientists.at(row);

        QString name = QString::fromStdString(tempScientist.getName());

        QString sex;
        if(tempScientist.getSex())
            sex = "Male";
        else
            sex = "Female";

        QString yearBorn = QString::number(tempScientist.getYearBorn());
        QString yearDied;
        if(tempScientist.getYearDied() == 13337)
            yearDied = "Alive";
        else
            yearDied = QString::number(tempScientist.getYearDied());


        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(sex));
        ui->table_current_view->setItem(row, 2, new QTableWidgetItem(yearBorn));
        ui->table_current_view->setItem(row, 3, new QTableWidgetItem(yearDied));
    }

    currentlyDissplayedScientists = scientists;
}

void MainWindow::on_button_view_computers_clicked()
{
    currentView = 2;
    displayAllComputers();
}

void MainWindow::on_button_view_scientists_clicked()
{
    currentView = 1;
    displayAllScientists();
}

void MainWindow::on_button_view_connections_clicked()
{
    currentView = 3;
    displayAllConnections();
}

void MainWindow::on_button_add_scientists_clicked()
{
    addScientistDialog addScientist;

    int addScientistReturnValue = addScientist.exec();

}

void MainWindow::on_button_add_computers_clicked()
{
    addComputerDialog addComputer;

    addComputer.exec();
}

void MainWindow::on_button_add_connections_clicked()
{
    addConnectionDialog addConnection;

    addConnection.exec();
}

void MainWindow::on_table_current_view_clicked(const QModelIndex &index)
{
    ui->button_remove->setEnabled(true);
}

void MainWindow::on_button_remove_clicked()
{
    int selectedScientist = ui->table_current_view->currentIndex().row();

    Scientist currentlySelectedScientist = currentlyDissplayedScientists.at(selectedScientist);

    bool success = scientistService.removeScientist(currentlySelectedScientist);

    if(success)
    {
        displayAllScientists();
        ui->button_remove->setEnabled(false);
    }
}
