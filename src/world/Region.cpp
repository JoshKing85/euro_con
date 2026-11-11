#include "european_conquest/world/Region.h"


namespace european_conquest {

    Region::Region(
        RegionID id,
        int bonus,
        const std::vector<TerritoryID>& territoryIDs,
        const std::vector<TerritoryID>& borderTerritoryIDs
    )
        : regionID(id),
        controlBonus(bonus),
        territories(territoryIDs),
        borderTerritories(borderTerritoryIDs),
        ownerID(-1)
    {
    }


    // GETTERS
    RegionID Region::getRegionID() const
    {
        return regionID;
    };

    int Region::getControlBonus() const
    {
        return controlBonus;
    };

    int Region::getOwnerID() const
    {
        return ownerID;
    }

    const std::vector<TerritoryID>& Region::getTerritories() const
    {
        return territories;
    };

    const std::vector<TerritoryID>& Region::getBorderTerritories() const
    {
        return borderTerritories;
    };


    // SETTERS
    void Region::setOwner(int newOwner)
    {
        ownerID = newOwner;
    };

}