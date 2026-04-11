#pragma once
#include "ExistantEntryException.h"

const char* ExistantEntryException::what() const noexcept {
    return message.c_str();
}