#pragma once

#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {

// Checks whether the selected territory belongs to the player.

bool isValidTerritorySelection(
    const TerritoryID &territorySelected,
    const std::vector<TerritoryID> &territoriesOwnedByPlayer);

} // namespace european_conquest