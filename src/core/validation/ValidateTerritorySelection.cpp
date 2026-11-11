#include "european_conquest/core/validation/ValidateTerritorySelection.h"

namespace european_conquest {

    bool isValidTerritorySelection(
        const TerritoryID& territorySelected,
        const std::vector<TerritoryID>& territoriesOwnedByPlayer
    )
    {
        for (const auto& territory : territoriesOwnedByPlayer)
        {
            if (territory == territorySelected)
            {
                return true;
            }
        }

        return false;
    }

} // namespace european_conquest