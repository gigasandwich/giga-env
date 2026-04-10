#include "EnvVar.h"
#include "PathVarHandler.h"
#include <sstream>

EnvVar::EnvVar(int scope, std::string name, char separator) : scope(scope), name(name), separator(separator) {
    // The child classes need to set this.value in their constructor
}

std::vector<std::string> EnvVar::getValues() {
    std::vector<std::string> result;

    std::stringstream ss(this->value);
    std::string item;

    while (std::getline(ss, item, this->separator)) {
        result.push_back(item);
    }

    return result;
}

std::string EnvVar::updateName(const std::string& updated) {
    const std::string currentValueBackup = this->value;
    this->remove();
    
    // Should be something like this = new EnvVar
    this->name = updated;
    this->setValue(currentValueBackup);

    return updated;
}

std::string EnvVar::remove() {
    std::string result = this->removeEnvEntry();
    this->removeRelatedPathEntries();
    return result;
}

std::vector<int> EnvVar::removeRelatedPathEntries() {
    PathVarHandler* pathVarHandler = new PathVarHandler(this->scope);
    std::vector<int> indexes = pathVarHandler->findIndexesOfValuesContaining(this->name);

    for (int i : indexes) {
        pathVarHandler->remove(i);
    }

    return indexes;
}