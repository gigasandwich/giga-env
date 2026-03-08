#include "EnvVar.h"
#include <sstream>

EnvVar::EnvVar(int scope, std::string name) : scope(scope), name(name) {
    // The child classes need to set this.value in their constructor
}

std::vector<std::string> EnvVar::getValues(char separator) {
    std::vector<std::string> result;

    std::stringstream ss(this->value);
    std::string item;

    while (std::getline(ss, item, separator)) {
        result.push_back(item);
    }

    return result;
}