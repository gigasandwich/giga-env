#include <iostream>
#include <windows.h>
#include "EnvManager.h"

EnvManager::EnvManager(HKEY scopeHKey) : scopeHKey(scopeHKey) {}

std::string EnvManager::getEnvVar(const std::string& varName) {
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

std::string EnvManager::setEnvVar(const std::string& varName, const std::string& varValue) {
    HKEY hKey;

    if (RegOpenKeyExA(scopeHKey, "Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return ""; // TODO: throw exception ?
    }

    /**
     * REG_EXPAND_SZ: string that may contain env vars
     * varValue.size() + 1 because of "\0". Had to cast there too, otherwise we get a warning
     */
    RegSetValueExA(hKey, varName.c_str(), 0, REG_EXPAND_SZ, (BYTE*)varValue.c_str(), static_cast<DWORD>(varValue.size() + 1));
    RegCloseKey(hKey);

    return varValue;
}

std::string EnvManager::deleteEnvVar(const std::string& varName) {
    HKEY hKey;

    if (RegOpenKeyExA(scopeHKey, "Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return ""; // TODO: throw exception ?
    }

    RegDeleteValueA(hKey, varName.c_str());
    RegCloseKey(hKey);

    return varName;
}

void EnvManager::refreshEnvironment()
{
    SendMessageTimeoutA(
        HWND_BROADCAST,
        WM_SETTINGCHANGE,
        0,
        (LPARAM)"Environment",
        SMTO_ABORTIFHUNG,
        5000,
        NULL
    );
}
