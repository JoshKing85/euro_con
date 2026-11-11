#pragma once

#include "european_conquest/world/Map.h"

#include <string>

namespace european_conquest {

// Loads the game map from a file.
Map loadMap(const std::string &filename);

} // namespace european_conquest