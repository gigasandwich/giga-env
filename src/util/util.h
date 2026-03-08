#include "windows.h"
#include "../env/EnvVar.h"
#include "../env/EnvVarWindows.h"

EnvVar* getEnvVarImpl(HKEY scopeHkey, std::string name);
