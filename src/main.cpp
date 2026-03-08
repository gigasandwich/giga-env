#include <iostream>
#include "env/EnvVar.h"
#include "env/PathVarHandler.h"
#include "util/util.h"
#include <stdexcept>

void pathTest();
void envVarTest();

/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    try {
        pathTest();
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}

void pathTest() {
    PathVarHandler pathVarHandler(SCOPE_CURRENT_USER);
    std::cout << "Before: " << pathVarHandler.toString() << std::endl;
    pathVarHandler.update(7, "Updated name");
    std::cout << "After: " << pathVarHandler.toString() << std::endl;
}

void envVarTest() {
    EnvVar* var = getEnvVarImpl(SCOPE_CURRENT_USER, "PATHS");
    std::cout << "Current value: " << var->value << std::endl;

    std::string newValue = var->setValue("C:\\paths\\jdk\\jdk-67");
    std::cout << "New value: " << newValue << std::endl;

    // std::string deletedVar = var->remove();
    // std::cout << "Deleted variable: " << deletedVar << " with value: " << var->value << std::endl;
}
