#include <iostream>
#include <windows.h>
#include "EnvManager.h"


/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    EnvManager envManager;

    std::string varName = "JAVA_HOME";
    std::string  varValue = envManager.setEnvVar(varName, "C:\\paths\\jdk\\jdk-21.0.9");
    std::cout << varValue << std::endl;

    envManager.deleteEnvVar(varName);

	varValue = envManager.getEnvVar(varName);
	std::cout << varValue << std::endl;

    EnvManager::refreshEnvironment();

    return 0;
}
