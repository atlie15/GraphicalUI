#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addscientistdialog.h"
#include "addcomputerdialog.h"
#include "addconnectiondialog.h"
#include "editscientistdialog.h"
#include "editcomputerdialog.h"
#include "editconnectiondialog.h"
#include "QMessageBox"
#include <QDebug>

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
    ui->button_edit->setEnabled(false);
    ui->lineEdit_search->setText("");
}

void MainWindow::displayAllComputers()
{
    vector<Computer> computers = computerService.getAllComputers("id", true);

    displayComputers(computers);

    currentView = 2;

    ui->button_remove->setEnabled(false);
    ui->button_edit->setEnabled(false);
    ui->lineEdit_search->setText("");
}

void MainWindow::displayAllConnections()
{
    displayConnections();

    currentView = 3;

    ui->button_remove->setEnabled(false);
    ui->button_edit->setEnabled(false);
    ui->lineEdit_search->setText("");
}

void MainWindow::displayComputers(std::vector<Computer> computers)
{
    ui->table_current_view->clear();
    ui->table_current_view->setSortingEnabled(false);

    ui->table_current_view->setColumnCount(4);
    ui->table_current_view->setColumnWidth(0, 30);
    for(unsigned int i(1); i < 4; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Type" << "Year Built");

    ui->table_current_view->setRowCount(computers.size());

    for(unsigned int row(0); row < computers.size(); row++)
    {
        Computer tempComputer = computers.at(row);

        QTableWidgetItem itemID;
        QTableWidgetItem itemName;
        QTableWidgetItem itemType;
        QTableWidgetItem itemYearBuilt;

        itemID.setData(Qt::DisplayRole, tempComputer.getId());

        itemName.setData(Qt::DisplayRole, QString::fromStdString(tempComputer.getName()));

        itemType.setData(Qt::DisplayRole, QString::fromStdString(tempComputer.getTypeName()));

        if(tempComputer.getYearBuilt() == 13337)
            itemYearBuilt.setData(Qt::DisplayRole, "Not built");
        else
            itemYearBuilt.setData(Qt::DisplayRole, QString::number(tempComputer.getYearBuilt()));

        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(itemID));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(itemName));
        ui->table_current_view->setItem(row, 2, new QTableWidgetItem(itemType));
        ui->table_current_view->setItem(row, 3, new QTableWidgetItem(itemYearBuilt));
    }

    ui->table_current_view->setSortingEnabled(true);

    currentlyDissplayedComputers = computers;
}

void MainWindow::displayConnections()
{
    ui->table_current_view->clear();
    ui->table_current_view->setSortingEnabled(false);

    ui->table_current_view->setColumnCount(2);
    for(unsigned int i(0); i < 2; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "Scientist Name" << "Computers");

    vector<int> links = linkService.getLink();
    vector<Computer> allComputers = computerService.getAllComputers("name", true);
    vector<Scientist> allScientists = scientistService.getAllScientists("name", true);

    ui->table_current_view->setRowCount(links.size()/2);

    int row = 0;

    for(unsigned int i(0); i < links.size(); i+=2)
    {
        for(unsigned int j(0); j < allScientists.size(); j++)
        {
            unsigned int k = links.at(i);

            if(k == allScientists.at(j).getId())
                ui->table_current_view->setItem(row,0, new QTableWidgetItem(QString::fromStdString(allScientists.at(j).getName())));
        }
        for(unsigned int j(0); j < allComputers.size(); j++)
        {
            unsigned int k = links.at(i+1);

            if(k == allComputers.at(j).getId())
                ui->table_current_view->setItem(row,1, new QTableWidgetItem(QString::fromStdString(allComputers.at(j).getName())));
        }

        row++;
    }

    ui->table_current_view->setSortingEnabled(true);
}

void MainWindow::displayScientists(std::vector<Scientist> scientists)
{
    ui->table_current_view->clear();
    ui->table_current_view->setSortingEnabled(false);

    ui->table_current_view->setColumnCount(5);
    ui->table_current_view->setColumnWidth(0, 30);

    for(unsigned int i(1); i < 5; i++)
        ui->table_current_view->setColumnWidth(i, 100);

    ui->table_current_view->setHorizontalHeaderLabels(QStringList() << "ID" << "Name" << "Gender" << "Year Born" << "Year Died");
    ui->table_current_view->setRowCount(scientists.size());

    for(unsigned int row(0); row < scientists.size(); row++)
    {
        Scientist tempScientist = scientists.at(row);

        QTableWidgetItem itemID;
        QTableWidgetItem itemName;
        QTableWidgetItem itemSex;
        QTableWidgetItem itemYearBorn;
        QTableWidgetItem itemYearDied;

        itemID.setData(Qt::DisplayRole, tempScientist.getId());

        itemName.setData(Qt::DisplayRole, QString::fromStdString(tempScientist.getName()));

        if(tempScientist.getSex())
            itemSex.setData(Qt::DisplayRole, "Male");
        else
            itemSex.setData(Qt::DisplayRole, "Female");

        itemYearBorn.setData(Qt::DisplayRole, tempScientist.getYearBorn());

        if(tempScientist.getYearDied() == 13337)
            itemYearDied.setData(Qt::DisplayRole, "Alive");
        else
            itemYearDied.setData(Qt::DisplayRole, tempScientist.getYearDied());

        ui->table_current_view->setItem(row, 0, new QTableWidgetItem(itemID));
        ui->table_current_view->setItem(row, 1, new QTableWidgetItem(itemName));
        ui->table_current_view->setItem(row, 2, new QTableWidgetItem(itemSex));
        ui->table_current_view->setItem(row, 3, new QTableWidgetItem(itemYearBorn));
        ui->table_current_view->setItem(row, 4, new QTableWidgetItem(itemYearDied));
    }

    ui->table_current_view->setSortingEnabled(true);
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

    int addScientistReturn = addScientist.exec();

    if(addScientistReturn == 0)
        ui->statusBar->showMessage("Add scientist closed", 5000);
    else if(addScientistReturn == 1)
    {
        ui->statusBar->showMessage("Successfully added a Scientist", 5000);
        displayAllScientists();
    }
    else
        ui->statusBar->showMessage("An error has occurred, please try again", 5000);

}

void MainWindow::on_button_add_computers_clicked()
{
    addComputerDialog addComputer;

    int addComputerReturn = addComputer.exec();

    if(addComputerReturn == 0)
        ui->statusBar->showMessage("Add computer closed", 5000);
    else if(addComputerReturn == 1)
    {
        ui->statusBar->showMessage("Successfully added a Computer", 5000);
        displayAllComputers();
    }
    else
        ui->statusBar->showMessage("An error has occurred, please try again", 5000);
}

void MainWindow::on_button_add_connections_clicked()
{
    addConnectionDialog addConnection;

    int addConnectionReturn = addConnection.exec();

    if(addConnectionReturn == 0)
        ui->statusBar->showMessage("Add connection closed", 5000);
    else if(addConnectionReturn == 1)
    {
        ui->statusBar->showMessage("Successfully added a Connection", 5000);
        displayAllConnections();
    }
    else
        ui->statusBar->showMessage("Could not make a connection, please try again", 5000);
}

void MainWindow::on_table_current_view_clicked()
{
    ui->button_remove->setEnabled(true);
    ui->button_edit->setEnabled(true);
}

void MainWindow::on_button_remove_clicked()
{
    int row = ui->table_current_view->currentIndex().row();

    QString name;

    if(currentView == 1 || currentView == 2)
        name = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,1)).toString();
    else
        name = "Connection between "
                + ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,0)).toString()
                + " and " + ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,1)).toString();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Remove", "Are you sure you want to remove: " + name
                                  + " from database?", QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No)
    {
        return;
    }

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
            ui->button_edit->setEnabled(false);
        }
    }
    else if(currentView == 2)
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
            ui->button_edit->setEnabled(false);
        }
    }
    else if(currentView == 3)
    {
        int row = ui->table_current_view->currentIndex().row();
        string sName = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,0)).toString().toStdString();
        string cName = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,1)).toString().toStdString();

        vector<Scientist> scientists = scientistService.getAllScientists("name", true);
        vector<Computer> computers = computerService.getAllComputers("name", true);

        int sID(0);
        int cID(0);

        for(unsigned int i(0); i < scientists.size(); i++)
        {
            if(sName == scientists.at(i).getName())
            {
                sID = scientists.at(i).getId();
                break;
            }
        }
        for(unsigned int i(0); i < computers.size(); i++)
        {
            if(cName == computers.at(i).getName())
            {
                cID = computers.at(i).getId();
                break;
            }
        }

        if(linkService.removeLink(sID, cID))
        {
            displayAllConnections();
            ui->button_remove->setEnabled(false);
            ui->button_edit->setEnabled(false);
        }
    }
}

void MainWindow::on_lineEdit_search_textChanged()
{
    string userInput = ui->lineEdit_search->text().toStdString();

    if(currentView == 1)
    {
        vector<Scientist> scientists = scientistService.searchForScientists(userInput);
        displayScientists(scientists);
    }
    if(currentView == 2)
    {
        vector<Computer> computers = computerService.searchForComputers(userInput);
        displayComputers(computers);
    }
}


void MainWindow::on_button_edit_clicked()
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

        editScientistDialog editScientist;

        editScientist.prepare(currentlySelectedScientist);

        bool success = editScientist.exec();

        if(success)
        {
            displayAllScientists();
            ui->button_remove->setEnabled(false);
            ui->button_edit->setEnabled(false);
        }
    }
    else if(currentView == 2)
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

        editComputerDialog editComputer;

        editComputer.prepare(currentlySelectedComputer);

        bool success = editComputer.exec();

        if(success)
        {
            displayAllComputers();
            ui->button_remove->setEnabled(false);
            ui->button_edit->setEnabled(false);
        }
    }
    else if(currentView == 3)
    {
        editConnectionDialog editConnection;

        int row = ui->table_current_view->currentIndex().row();
        string sName = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,0)).toString().toStdString();
        string cName = ui->table_current_view->model()->data(ui->table_current_view->model()->index(row,1)).toString().toStdString();

        vector<Scientist> scientists = scientistService.getAllScientists("name", true);
        vector<Computer> computers = computerService.getAllComputers("name", true);

        int sID(0);
        int cPos(0);

        for(unsigned int i(0); i < scientists.size(); i++)
        {
            if(sName == scientists.at(i).getName())
            {
                sID = i;
                break;
            }
        }
        for(unsigned int i(0); i < computers.size(); i++)
        {
            if(cName == computers.at(i).getName())
            {
                cPos = i;
                break;
            }
        }

        Scientist currentScientist = scientists.at(sID);

        editConnection.prepare(computers, currentScientist, cPos);

        int success = editConnection.exec();

        if(success == 1)
        {
            ui->statusBar->showMessage("Successfully edited a connection", 5000);

            displayAllConnections();
            ui->button_remove->setEnabled(false);
            ui->button_edit->setEnabled(false);
        }
        else if(success == -1)
            ui->statusBar->showMessage("An error has occurred, try deleting the connection and creating another", 10000);
        else if(success == 0)
            ui->statusBar->showMessage("Edit connection closed", 5000);
    }
}
