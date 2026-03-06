#include <iostream>
#include <windows.h>

std::string getEnvVar(HKEY scopeHKey, const std::string& varName);
std::string setEnvVar(HKEY scopeHKey, const std::string& varName, const std::string& varValue);
std::string deleteEnvVar(HKEY scopeHKey, const std::string& varName);
void refresh();

/*
    Somehow HKEY_LOCAL_MACHINE doesn't work on both Create and Read
    Maybe an error about permissions ?
*/
int main() {
    std::string varName = "JAVA_HOME";
    std::string  varValue = setEnvVar(HKEY_CURRENT_USER, varName, "C:\\paths\\jdk\\jdk-21.0.9");
    std::cout << varValue << std::endl;

	deleteEnvVar(HKEY_CURRENT_USER, varName);

	varValue = getEnvVar(HKEY_CURRENT_USER, varName);
	std::cout << varValue << std::endl; // Previous varValue is still displayed though

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

std::string setEnvVar(HKEY scopeHKey, const std::string& varName, const std::string& varValue) {
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

std::string deleteEnvVar(HKEY scopeHKey, const std::string& varName) {
    HKEY hKey;
    
    if (RegOpenKeyExA(scopeHKey, "Environment", 0, KEY_SET_VALUE, &hKey) != ERROR_SUCCESS) {
        return ""; // TODO: throw exception ?
    }

    RegDeleteValueA(hKey, varName.c_str());
    RegCloseKey(hKey);

    return varName;
}