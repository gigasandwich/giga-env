#include <iostream>
#include <windows.h>

std::string getEnvVar(HKEY scopeHKey, const std::string& varName);

int main() {
    std::string varName = "Path";
    std::string varValue = getEnvVar(HKEY_LOCAL_MACHINE, varName);
    std::cout << varValue << std::endl;
    return 0;
}

std::string getEnvVar(HKEY scopeHKey, const std::string& varName) {
    HKEY hKey;
    if (RegOpenKeyExA(scopeHKey, "Environment", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        return "";
    }

    char buffer[2048];
    DWORD bufferSize = sizeof(buffer);
    if (RegQueryValueExA(hKey, varName.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return "";
    }

    RegCloseKey(hKey);
    return std::string(buffer);
}