#pragma once
#include "UnexistantEntryException.h"

const char* UnexistantEntryException::what() const noexcept {
    return message.c_str();
}