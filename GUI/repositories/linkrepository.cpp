#include "linkrepository.h"
#include "utilities/utils.h"

#include <cstdlib>
#include <sstream>
#include <QString>

using namespace std;

LinkRepository::LinkRepository()
{
    db = utils::getDatabaseConnection();
}

bool LinkRepository::addLink(string scientistId, string computerId)
{
    db.open();

    if (!db.isOpen())
    {
        return false;
    }

    QSqlQuery query(db);

    stringstream sqlQuery;
    sqlQuery << "INSERT INTO ScientistComputerConnections (scientistId, computerId) VALUES ("
             << "'" << scientistId << "', "
             << "'" << computerId << "'"
             << ")";

    if (!query.exec(QString::fromStdString(sqlQuery.str())))
    {
        return false;
    }

    db.close();

    return true;
}

bool LinkRepository::editLink(string scientistId, string computerId)
{
    db.open();

    if (!db.isOpen())
    {
        return false;
    }

    QSqlQuery query(db);

    stringstream sqlQuery;
    sqlQuery << "UPDATE ScientistComputerConnections "
             << "SET computerId='" << computerId
             << "' WHERE scientistId='" << scientistId << "'";

    if (!query.exec(QString::fromStdString(sqlQuery.str())))
    {
        return false;
    }

    db.close();

    return true;
}


std::vector<int> LinkRepository::getLink()
{
    vector<int> links;

    db.open();

    if (!db.isOpen())
    {
        return links;
    }

    QSqlQuery query(db);

    if (!query.exec("SELECT * FROM ScientistComputerConnections ORDER BY scientistId ASC"))
    {
        return links;
    }

    while (query.next())
    {
        int sID = query.value("scientistId").toInt();
        int cID = query.value("computerId").toInt();

        links.push_back(sID);
        links.push_back(cID);
    }

    return links;
}

bool LinkRepository::removeLink(int scientistId, int computerId)
{
    db.open();

    if (!db.isOpen())
    {
        return false;
    }

    QSqlQuery query(db);

    stringstream sqlQuery;
    sqlQuery << "DELETE FROM ScientistComputerConnections "
                "WHERE scientistId='" << scientistId
             << "' AND computerId='" << computerId << "'";

    if (!query.exec(QString::fromStdString(sqlQuery.str())))
    {
        return false;
    }

    db.close();

    return true;
}
