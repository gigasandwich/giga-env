#include "windows.h"
#include "../env/EnvVar.h"
#include "../env/impl/windows/EnvVarWindows.h"

// TODO: remove HKEY argument because it's exclusive to windows 
EnvVar* getEnvVarImpl(int scope, std::string name) {
    EnvVar* instance;
    #ifdef _WIN32
        instance = new EnvVarWindows(scope, name);
    #elif __linux__
        //instance = new EnvVarLinux(scopeHkey, name);
        throw std::runtime_error("Unsupported platform"); // For now :P
    #else
        throw std::runtime_error("Unsupported platform");
    #endif
    return instance;
}
