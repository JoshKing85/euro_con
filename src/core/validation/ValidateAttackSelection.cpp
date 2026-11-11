#include "european_conquest/core/validation/ValidateAttackSelection.h"
#include "european_conquest/world/Map.h"

#include <vector>

namespace european_conquest {

    bool isValidAttackSelection(
        int playerID,
        const TerritoryID& territorySelection,
        Map& map)
    {
        int ownerID =
            map.getTerritory(
                territorySelection)
            .getOwnerID();

        if (ownerID != playerID)
        {
            return false;
        }

        int troopCount =
            map.getTerritory(
                territorySelection)
            .getTroopCount();

        if (troopCount < 2)
        {
            return false;
        }

        std::vector<TerritoryID> adjacentTerritories =
            map.getTerritory(
                territorySelection)
            .getAdjacentTerritories();

        for (const auto& territory : adjacentTerritories)
        {
            int adjacentOwnerID =
                map.getTerritory(
                    territory)
                .getOwnerID();

            if (adjacentOwnerID != playerID)
            {
                return true;
            }
        }

        return false;
    }

} // namespace european_conquest