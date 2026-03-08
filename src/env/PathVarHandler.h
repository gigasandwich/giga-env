#include "EnvVar.h"
#include <vector>

class PathVarHandler {
public:
    // Expected scope values are defined in util/util.h
    PathVarHandler(int scope);
    
    std::vector<std::string> getValues();
private:
    EnvVar* pathEnvVar;
};