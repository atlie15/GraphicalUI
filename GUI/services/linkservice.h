#ifndef LINKSERVICE_H
#define LINKSERVICE_H

#include "linkrepository.h"

/**
 * @brief The LinkService acts as a middle layer between the UI and Data layers
 */

class LinkService
{
public:
    LinkService();

    /**
     * @brief addLink saves a link between scientists and computers to a database
     * @param scientistId The scientist id to connect to
     * @param computerId The computer id to connect to
     * @return true if it was a success, false if it was a failure
     */
    bool addLink(std::string scientistId, std::string computerId);
    bool editLink(std::string scientistId, std::string computerId);
    bool removeLink(int scientistId, int computerId);
    std::vector<int> getLink();
private:
    LinkRepository linkRepo;
};

#endif // LINKSERVICE_H
