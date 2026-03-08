#include "EnvVar.h"
#include <vector>

class PathVarHandler {
public:
    PathVarHandler();
    
    std::vector<std::string> getValues();
private:
    EnvVar* pathEnvVar;
};