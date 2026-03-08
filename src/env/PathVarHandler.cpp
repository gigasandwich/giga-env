#include "PathVarHandler.h"
#include <vector>
#include "../util/util.h"
#include "windows.h"

PathVarHandler::PathVarHandler(int scope) {
    this->pathEnvVar = getEnvVarImpl(scope, "PATH");
}

std::vector<std::string> PathVarHandler::getValues() {
    return this->pathEnvVar->getValues();
}