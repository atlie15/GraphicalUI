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
    vector<Scientist> scientists = scientistService.getAllScientists("id", true);

    displayScientists(scientists);

    currentView = 1;

    ui->button_remove->setEnabled(false);
}

void MainWindow::displayAllComputers()
{
    vector<Computer> computers = computerService.getAllComputers("id", true);

    displayComputers(computers);

    currentView = 2;

    ui->button_remove->setEnabled(false);
}

void MainWindow::displayAllConnections()
{
    vector<Scientist> scientists = scientistService.getAllScientists("name", true);

    displayConnections(scientists);

    currentView = 3;

    ui->button_remove->setEnabled(false);
}

void MainWindow::displayComputers(std::vector<Computer> computers)
{
    ui->table_current_view->clear();

    ui->table_current_view->setColumnCount(4);
    for(unsigned int i(0); i < 4; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Type" << "Year Built");

    ui->table_current_view->setRowCount(computers.size());

    for(unsigned int row(0); row < computers.size(); row++)
    {
        Computer tempComputer = computers.at(row);

        QString id = QString::number(tempComputer.getId());

        QString name = QString::fromStdString(tempComputer.getName());

        QString type = QString::fromStdString(tempComputer.getTypeName());

        QString yearBuilt;
        if(tempComputer.getYearBuilt() == 13337)
            yearBuilt = "Not built";
        else
            yearBuilt = QString::number(tempComputer.getYearBuilt());


        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(id));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(name));
        ui->table_current_view->setItem(row, 2, new QTableWidgetItem(type));
        ui->table_current_view->setItem(row, 3, new QTableWidgetItem(yearBuilt));
    }

    currentlyDissplayedComputers = computers;
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

    ui->table_current_view->setColumnCount(5);
    for(unsigned int i(0); i < 5; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Gender" << "Year Born" << "Year Died");
    ui->table_current_view->setRowCount(scientists.size());

    for(unsigned int row(0); row < scientists.size(); row++)
    {
        Scientist tempScientist = scientists.at(row);

        QString id = QString::number(tempScientist.getId());

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


        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(id));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(name));
        ui->table_current_view->setItem(row, 2, new QTableWidgetItem(sex));
        ui->table_current_view->setItem(row, 3, new QTableWidgetItem(yearBorn));
        ui->table_current_view->setItem(row, 4, new QTableWidgetItem(yearDied));
    }

    currentlyDissplayedScientists = scientists;
}

void MainWindow::on_button_view_computers_clicked()
{
    displayAllComputers();
}

void MainWindow::on_button_view_scientists_clicked()
{
    displayAllScientists();
}

void MainWindow::on_button_view_connections_clicked()
{
    displayAllConnections();
}

void MainWindow::on_button_add_scientists_clicked()
{
    addScientistDialog addScientist;

    int addScientistReturnValue = addScientist.exec();

    displayAllScientists();
}

void MainWindow::on_button_add_computers_clicked()
{
    addComputerDialog addComputer;

    addComputer.exec();

    displayAllComputers();
}

void MainWindow::on_button_add_connections_clicked()
{
    addConnectionDialog addConnection;

    addConnection.exec();

    displayAllConnections();
}

void MainWindow::on_table_current_view_clicked(const QModelIndex &index)
{
    ui->button_remove->setEnabled(true);
}

void MainWindow::on_button_remove_clicked()
{
    if(currentView == 1)
    {
        Scientist currentlySelectedScientist;

        int row = ui->table_current_view->currentIndex().row();

        int id = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,0)).toInt();

        for (unsigned int i(0); i < currentlyDissplayedScientists.size(); i++)
        {
            int tempID = currentlyDissplayedScientists.at(i).getId();

            if(tempID == id)
            {
                currentlySelectedScientist = currentlyDissplayedScientists.at(i);
                break;
            }
        }

        bool success = scientistService.removeScientist(currentlySelectedScientist);

        if(success)
        {
            displayAllScientists();
            ui->button_remove->setEnabled(false);
        }
    }
    if(currentView == 2)
    {
        Computer currentlySelectedComputer;

        int row = ui->table_current_view->currentIndex().row();

        int id = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,0)).toInt();

        for (unsigned int i(0); i < currentlyDissplayedComputers.size(); i++)
        {
            int tempID = currentlyDissplayedComputers.at(i).getId();

            if(tempID == id)
            {
                currentlySelectedComputer = currentlyDissplayedComputers.at(i);
                break;
            }
        }

        bool success = computerService.removeComputer(currentlySelectedComputer);

        if(success)
        {
            displayAllComputers();
            ui->button_remove->setEnabled(false);
        }
    }
}
