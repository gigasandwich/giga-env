#include "PathVarHandler.h"
#include <vector>
#include "../util/util.h"
#include "windows.h"

PathVarHandler::PathVarHandler() {
    this->pathEnvVar = getEnvVarImpl(HKEY_CURRENT_USER, "PATH");
}

std::vector<std::string> PathVarHandler::getValues() {
    return this->pathEnvVar->getValues();
}