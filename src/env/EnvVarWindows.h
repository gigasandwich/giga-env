#pragma once

#include <string>
#include <vector>
#include <windows.h>
#include "EnvVar.h"

class EnvVarWindows : public EnvVar {
public:
	EnvVarWindows(HKEY scopeHkey, std::string name);

	std::string setValue(const std::string& value) override;
	std::string remove() override;
	std::vector<std::string> getValues() override;
	void refreshEnvironment() override;

protected:
	std::string getValue() override;
};