#pragma once

#include <exception>
#include <string>

class ExistantEntryException : public std::exception {
public:
    ExistantEntryException() : message("Entry already exists") {}
    ExistantEntryException(const std::string& message) : message(message) {}

    const char* what() const noexcept override;

private:
    std::string message;
};