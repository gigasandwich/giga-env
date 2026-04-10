#include "PathVarHandler.h"
#include "../util/util.h"
#include "windows.h"
#include <stdexcept>

PathVarHandler::PathVarHandler(int scope) {
    this->pathEnvVar = getEnvVarImpl(scope, "PATH");
    this->values = this->pathEnvVar->getValues();
}

std::string PathVarHandler::append(std::string newValue) {
    // Control
    for (const std::string& entry : this->values) {
        if (entry == newValue) {
            throw std::runtime_error("Entry already exists");
        }
    }

    // Business logic
    this->values.push_back(newValue);

    // Persist
    this->persist();
    return newValue;
}

std::string PathVarHandler::update(int index, std::string newValue) {
    // Control
    if (this->values[index].empty()) { // Apparently "== null" doesn't work :(
        throw std::runtime_error("Unexistant entry");
    }
    // Business logic
    this->values[index] = newValue;

    // Persist
    this->persist();
    return newValue;
}

std::string PathVarHandler::remove(int index) {
    // Control
    if (this->values[index].empty()) {
        throw std::runtime_error("Entry does not exist");
    }

    // Business logic
    std::string removed = this->values[index];
    this->values.erase(this->values.begin() + index);

    // Persist
    this->persist();

    return removed;
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

void PathVarHandler::persist() {
    this->pathEnvVar->setValue(toString());
    this->pathEnvVar->refreshEnvironment();
}

std::vector<int> PathVarHandler::findIndexesOfValuesContaining(std::string part) {
    std::vector<int> result;

    for (int i = 0; i < this->values.size(); i++) {
        try {
            if (this->values[i].find(part) != std::string::npos) {
                throw i;
            }
        } catch (int index) { // :P
            result.push_back(index);
        }
    }
    
    return result;
}