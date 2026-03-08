#include "PathVarHandler.h"
#include "../util/util.h"
#include "windows.h"
#include "stdexcept"

PathVarHandler::PathVarHandler(int scope) {
    this->pathEnvVar = getEnvVarImpl(scope, "PATH");
    this->values = this->pathEnvVar->getValues();
}

std::string PathVarHandler::append(std::string newValue) {
    for (const std::string& entry : this->values) {
        if (entry == newValue) {
            throw new std::runtime_error("Entry already exists");
        }
    }
    this->values.push_back(newValue);

    // Persist
    this->pathEnvVar->setValue(toString());
    this->pathEnvVar->refreshEnvironment();
    return newValue;
}

std::string PathVarHandler::update(int index, std::string newValue) {
    if (this->values[index].empty()) { // Apparently "== null" doesn't work :(
        throw new std::runtime_error("Unexistant entry");
    }
    
    this->values[index] = newValue;

    // Persist
    this->pathEnvVar->setValue(toString());
    this->pathEnvVar->refreshEnvironment();
    return newValue;
}

std::string PathVarHandler::toString() {
    std::string result = "";

    std::vector<std::string> v = this->values;

    for (const std::string& s : v) {
        result += s + this->pathEnvVar->separator;
    }

    result.erase(result.size() - 1); // Remove last ";"

    return result;
}