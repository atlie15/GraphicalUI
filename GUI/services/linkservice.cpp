#include "linkservice.h"

#include <string>

using namespace std;

LinkService::LinkService()
{

}

bool LinkService::addLink(string scientistId, string computerId)
{
    return linkRepo.addLink(scientistId, computerId);
}

bool LinkService::editLink(string scientistId, string computerId)
{
    return linkRepo.editLink(scientistId, computerId);
}

bool LinkService::removeLink(int scientistId, int computerId)
{
    return linkRepo.removeLink(scientistId, computerId);
}

std::vector<int> LinkService::getLink()
{
    return linkRepo.getLink();
}
