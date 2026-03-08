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
        envVarTest();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

void pathTest() {
    PathVarHandler pathVarHandler(SCOPE_CURRENT_USER);
    std::cout << "Before: " << pathVarHandler.toString() << std::endl;
    pathVarHandler.remove(7); // Dunno why but the "After" string isn't shown 
    std::cout << "After: " << pathVarHandler.toString() << std::endl;
}

void envVarTest() {
    EnvVar* var = getEnvVarImpl(SCOPE_CURRENT_USER, "NULL");
    std::cout << "Current value: " << var->value << std::endl;

    std::string newValue = var->setValue("null");
    std::cout << "New value: " << newValue << std::endl;

    var->updateName("NOT_NULL_XD");

    // std::string deletedVar = var->remove();
    // std::cout << "Deleted variable: " << deletedVar << " with value: " << var->value << std::endl;
}
