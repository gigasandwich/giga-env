# include "EnvVar.h"

EnvVar::EnvVar(HKEY scopeHkey, std::string name) : scopeHkey(scopeHkey), name(name) {
    // The child classes need to set this.value in their constructor
}
