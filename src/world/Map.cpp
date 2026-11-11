#include "european_conquest/world/Map.h"

namespace european_conquest {

    Territory& Map::getTerritory(TerritoryID id)
    {
        return territories.at(id);
    }

    const Territory& Map::getTerritory(TerritoryID id) const
    {
        return territories.at(id);
    }

    Region& Map::getRegion(RegionID id)
    {
        return regions.at(id);
    }

    const Region& Map::getRegion(RegionID id) const
    {
        return regions.at(id);
    }
    const std::unordered_map<TerritoryID, Territory>& Map::getTerritories() const
    {
        return territories;
    }

    void Map::addTerritory(const Territory& territory)
    {
        territories.emplace(
            territory.getID(),
            territory
        );
    }

    void Map::addRegion(const Region& region)
    {
        regions.emplace(
            region.getRegionID(),
            region
        );
    }

} // namespace european_conquest