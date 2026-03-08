#include <iostream>
#include <windows.h>
#include "env/EnvVar.h"
#include "env/PathVarHandler.h"
#include "util/util.h"

void pathTest();
void mainTest();

/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    pathTest();
    return 0;
}

void pathTest() {
    PathVarHandler pathVarHandler;
    std::vector<std::string> v = pathVarHandler.getValues();

    for (const std::string& s : v) {
        std::cout << s << std::endl;
    }
}

void mainTest() {
    EnvVar* var = getEnvVarImpl(HKEY_CURRENT_USER, "PATHS");
    std::cout << "Current value: " << var->value << std::endl;

    std::string newValue = var->setValue("C:\\paths\\jdk\\jdk-67");
    std::cout << "New value: " << newValue << std::endl;

    // std::string deletedVar = var->remove();
    // std::cout << "Deleted variable: " << deletedVar << " with value: " << var->value << std::endl;
}
