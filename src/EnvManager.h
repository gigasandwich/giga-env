#pragma once

#include <string>
#include <windows.h>

class EnvManager {
public:
    EnvManager(HKEY scopeHKey = HKEY_CURRENT_USER);

    std::string getEnvVar(const std::string& varName);
    std::string setEnvVar(const std::string& varName, const std::string& varValue);
    std::string deleteEnvVar(const std::string& varName);
    static void refreshEnvironment();

private:
    HKEY scopeHKey;
};
