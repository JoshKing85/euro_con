#pragma once

#include "european_conquest/enums.h"
#include <string>

namespace european_conquest {
// Converts continent names into domain identifiers.
ContinentID stringToContinentID(const std::string &continentName);
}