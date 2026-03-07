#include "EnvVar.h"
#include <sstream>

EnvVar::EnvVar(HKEY scopeHkey, std::string name) : scopeHkey(scopeHkey), name(name) {
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