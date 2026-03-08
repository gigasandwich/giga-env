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

std::string PathVarHandler::toString() {
    std::string result = "";

    std::vector<std::string> v = this->getValues();

    for (const std::string& s : v) {
        result += s + this->pathEnvVar->separator;
    }

    result.erase(result.size() - 1); // Remove last ";"

    return result;
}