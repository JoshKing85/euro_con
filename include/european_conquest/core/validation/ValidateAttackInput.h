#pragma once

#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {

// Checks whether a selected attack satisfies adjacency, ownership and troop requirements.

bool isValidAttackInput(const TerritoryID &territoryToAttack,
                        const std::vector<TerritoryID> &adjacentTerritories,
                        int territorySelectedTroopCount, int attackingOwnerID,
                        int defendingOwnerID);

} // namespace european_conquest