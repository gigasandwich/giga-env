#include <iostream>
#include <windows.h>
#include "env/EnvVar.h"
#include "env/EnvVarWindows.h"

void mainTest();
EnvVar* getEnvVarImpl(HKEY scopeHkey, std::string name);

/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    mainTest();
    return 0;
}

void mainTest() {
    EnvVar* var = getEnvVarImpl(HKEY_CURRENT_USER, "JAVA_HOME");
    std::cout << "Current value: " << var->value << std::endl;

    std::string newValue = var->setValue("C:\\paths\\jdk\\jdk-67");
    std::cout << "New value: " << newValue << std::endl;

    // std::string deletedVar = var->remove();
    // std::cout << "Deleted variable: " << deletedVar << " with value: " << var->value << std::endl;
}

EnvVar* getEnvVarImpl(HKEY scopeHkey, std::string name) {
    EnvVar* instance;
    #ifdef _WIN32
        instance = new EnvVarWindows(scopeHkey, name);
    #elif __linux__
        //instance = new EnvVarLinux(scopeHkey, name);
        throw std::runtime_error("Unsupported platform"); // For now :P
    #else
        throw std::runtime_error("Unsupported platform");
    #endif
    return instance;
}