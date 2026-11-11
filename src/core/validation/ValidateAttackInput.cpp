#include "european_conquest/core/validation/ValidateAttackInput.h"

namespace european_conquest {

    bool isValidAttackInput(
        const TerritoryID& territoryToAttack,
        const std::vector<TerritoryID>& adjacentTerritories,
        int territorySelectedTroopCount,
        int attackingOwnerID,
        int defendingOwnerID)
    {
        if (territorySelectedTroopCount < 2)
        {
            return false;
        }

        if (attackingOwnerID == defendingOwnerID)
        {
            return false;
        }

        for (const auto& territory : adjacentTerritories)
        {
            if (territory == territoryToAttack)
            {
                return true;
            }
        }

        return false;
    }

} // namespace european_conquest