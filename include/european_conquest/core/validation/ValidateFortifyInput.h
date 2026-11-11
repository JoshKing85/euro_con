#pragma once

#include "european_conquest/enums.h"
#include "european_conquest/world/Map.h"

#include <vector>

namespace european_conquest {

    // Checks whether troops can be fortified between two territories owned by the player.

    bool isFortifyValid(
        const Map &map, 
        const TerritoryID &fromTerritory,
        const TerritoryID &toTerritory,
        int playerID);

} // namespace european_conquest