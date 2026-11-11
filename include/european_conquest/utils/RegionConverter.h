#pragma once

#include "european_conquest/enums.h"
#include <string>

namespace european_conquest {
// Converts region names into domain identifiers.
RegionID stringToRegionID(const std::string &regionName);
}