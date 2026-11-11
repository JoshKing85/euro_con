#pragma once

#include "european_conquest/enums.h"
#include <string>

namespace european_conquest {
// Converts territory names into domain identifiers.
TerritoryID stringToTerritoryID(const std::string &territoryName);
}