#include <iostream>
#include <windows.h>
#include "env/EnvVar.h"
#include "env/PathVarHandler.h"
#include "util/util.h"

void pathTest();
void envVarTest();

/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    pathTest();
    return 0;
}

void pathTest() {
    PathVarHandler pathVarHandler(SCOPE_CURRENT_USER);
    std::cout << pathVarHandler.toString() << std::endl;
}

void envVarTest() {
    EnvVar* var = getEnvVarImpl(SCOPE_CURRENT_USER, "PATHS");
    std::cout << "Current value: " << var->value << std::endl;

    std::string newValue = var->setValue("C:\\paths\\jdk\\jdk-67");
    std::cout << "New value: " << newValue << std::endl;

    // std::string deletedVar = var->remove();
    // std::cout << "Deleted variable: " << deletedVar << " with value: " << var->value << std::endl;
}
