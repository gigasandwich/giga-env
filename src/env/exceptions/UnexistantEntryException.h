#pragma once

#include <exception>
#include <string>

class UnexistantEntryException : public std::exception {
public:
    UnexistantEntryException() : message("Unexistant entry") {}
    UnexistantEntryException(const std::string& message) : message(message) {}

    const char* what() const noexcept override;

private:
    std::string message;
};