#include <iostream>
#include <windows.h>
#include "env/EnvVar.h"

void mainTest();

/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    mainTest();
    return 0;
}

void mainTest() {
    EnvVar var(HKEY_CURRENT_USER, "JAVA_HOME");
    std::cout << "Current value: " << var.value << std::endl;

    std::string newValue = var.setValue("C:\\paths\\jdk\\jdk-67");
    std::cout << "New value: " << newValue << std::endl;

    std::string deletedVar = var.remove();
    std::cout << "Deleted variable: " << deletedVar << " with value: " << var.value << std::endl;
}