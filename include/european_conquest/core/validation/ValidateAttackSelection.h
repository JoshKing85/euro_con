#pragma once

#include "european_conquest/enums.h"
#include "european_conquest/world/Map.h"

#include <vector>

namespace european_conquest {

// Checks whether the selected territory can initiate an attack for the active player.

bool isValidAttackSelection(int playerID, const TerritoryID &territorySelection, Map &map);

} // namespace european_conquest