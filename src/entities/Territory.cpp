#include "european_conquest/entities/Territory.h"

#include <algorithm>

namespace european_conquest
{
    Territory::Territory(
        TerritoryID id,
        RegionID region,
        const std::vector<TerritoryID>& adjacentIDs
    )
        : territoryID(id),
        regionID(region),
        adjacentTerritories(adjacentIDs),
        troopCount(0),
        ownerID(-1)
    {
    }

    // GETTERS

    TerritoryID Territory::getID() const
    {
        return territoryID;
    }

    const std::vector<TerritoryID>& Territory::getAdjacentTerritories() const
    {
        return adjacentTerritories;
    }

    int Territory::getTroopCount() const
    {
        return troopCount;
    }
    int Territory::getOwnerID() const
    {
        return ownerID;
	}

    RegionID Territory::getRegionID() const
    {
        return regionID;
    }
    

    // STATE UPDATES

    void Territory::setOwner(int newOwnerID)
    {
        ownerID = newOwnerID;
    }

    void Territory::addTroops(int amount)
    {
        troopCount += amount;
    }

    void Territory::removeTroops(int amount)
    {
        troopCount = std::max(0, troopCount - amount);
    }
}