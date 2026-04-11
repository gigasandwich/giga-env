#include "windows.h"
#include "../env/EnvVar.h"
#include "../env/impl/windows/EnvVarWindows.h"

const int SCOPE_CURRENT_USER = 10;
const int SCOPE_LOCAL_MACHINE = 20;
EnvVar* getEnvVarImpl(int scope, std::string name);
