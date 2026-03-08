#include <string>
#include <iostream>
#include "EnvVarWindows.h"
#include "EnvVar.h"
#include <vector>
#include <windows.h>
#include "../util/util.h"

EnvVarWindows::EnvVarWindows(int scope, std::string name) : EnvVar(scope, name) {
    if (scope == SCOPE_CURRENT_USER) {
        this->scopeHkey = HKEY_CURRENT_USER; // Compiler forces me to use "->" and not "." ?
    } else if (scope == SCOPE_LOCAL_MACHINE) {
        this->scopeHkey = HKEY_LOCAL_MACHINE;
    } else {
        throw std::runtime_error("Unknown scope");
    }
    this->value = this->getValue();
}

std::string EnvVarWindows::getValue() {
    HKEY hKey = getHkeyOrThrow(KEY_READ);

    char buffer[2048];
    DWORD bufferSize = sizeof(buffer);
    if (RegQueryValueExA(hKey, this->name.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return "";
    }

    RegCloseKey(hKey);

    return std::string(buffer);
}

std::vector<std::string> EnvVarWindows::getValues() {
    return EnvVar::getValues(';');
}

std::string EnvVarWindows::setValue(const std::string& value) {
    HKEY hKey = getHkeyOrThrow(KEY_SET_VALUE);

    /**
     * REG_EXPAND_SZ: string that may contain env vars
     * varValue.size() + 1 because of "\0". Had to cast there too, otherwise we get a warning
     */
    RegSetValueExA(hKey, this->name.c_str(), 0, REG_EXPAND_SZ, (BYTE*)value.c_str(), static_cast<DWORD>(value.size() + 1));
    RegCloseKey(hKey);

    this->value = value; // Update value
    return this->value;
}

std::string EnvVarWindows::remove() {
    HKEY hKey = getHkeyOrThrow(KEY_SET_VALUE);

    RegDeleteValueA(hKey, this->name.c_str());
    RegCloseKey(hKey);

    return this->name;
}

/**
 * Static methods
 */

void EnvVarWindows::refreshEnvironment() {
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

/**
 * Private methods
 */

HKEY EnvVarWindows::getHkeyOrThrow(REGSAM permission) {
    HKEY hKey;

    if (RegOpenKeyExA(this->scopeHkey, "Environment", 0, permission, &hKey) != ERROR_SUCCESS) {
        throw std::runtime_error("Failed to open registry key");
    }
    return hKey;
}