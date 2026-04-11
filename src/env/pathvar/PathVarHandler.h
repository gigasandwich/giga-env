#include "../EnvVar.h"
#include <vector>

class PathVarHandler {
public:
    PathVarHandler(int scope); // Expected scope values are defined in util/util.h
    
    std::vector<std::string> getValues();
    std::string append(std::string newValue);
    std::string update(int index, std::string newValue);
    std::string remove(int index);
    
    std::vector<int> findIndexesOfValuesContaining(std::string value); // Guess how I'm gonna implement this

    std::string toString(); // It's like getValues().implode() of php
private:
    EnvVar* pathEnvVar;
    std::vector<std::string> values;
    void persist();
};