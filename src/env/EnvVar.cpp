#include <string>
#include <iostream>
#include "EnvVar.h"
#include <vector>
#include <windows.h>

EnvVar::EnvVar(HKEY scopeHkey, std::string name) : scopeHkey(scopeHkey), name(name) {
    this->value = this->getValue();
}

std::string EnvVar::getValue() {
    HKEY hKey;

    if (RegOpenKeyExA(this->scopeHkey, "Environment", 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        return "";
    }

    char buffer[2048];
    DWORD bufferSize = sizeof(buffer);
    if (RegQueryValueExA(hKey, this->name.c_str(), NULL, NULL, (LPBYTE)buffer, &bufferSize) != ERROR_SUCCESS) {
        RegCloseKey(hKey);
        return "";
    }

    RegCloseKey(hKey);

    return std::string(buffer);
}

std::string EnvVar::setValue(const std::string& value) {
    HKEY hKey;

    if (RegOpenKeyExA(scopeHkey, "Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return ""; // TODO: throw exception ?
    }

    /**
     * REG_EXPAND_SZ: string that may contain env vars
     * varValue.size() + 1 because of "\0". Had to cast there too, otherwise we get a warning
     */
    RegSetValueExA(hKey, this->name.c_str(), 0, REG_EXPAND_SZ, (BYTE*)value.c_str(), static_cast<DWORD>(value.size() + 1));
    RegCloseKey(hKey);

    this->value = value; // Update value
    return this->value;
}

std::string EnvVar::remove() {
    HKEY hKey;

    if (RegOpenKeyExA(scopeHkey, "Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return "";
    }

    RegDeleteValueA(hKey, this->name.c_str());
    RegCloseKey(hKey);

    return this->name;
}

std::vector<std::string> EnvVar::getValues() {
    return { "" };
}

void EnvVar::refreshEnvironment()
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
