#pragma once

#include "european_conquest/entities/Territory.h"
#include "european_conquest/world/Region.h"
#include "european_conquest/enums.h"

#include <unordered_map>

namespace european_conquest {

/** Holds the territories and regions that define the game world. Accesses and updates them by ID. */
class Map {
private:
    std::unordered_map<TerritoryID, Territory> territories;
    std::unordered_map<RegionID, Region> regions;

public:
    Territory &getTerritory(TerritoryID id);
    const Territory &getTerritory(TerritoryID id) const;

    Region &getRegion(RegionID id);
    const Region &getRegion(RegionID id) const;
    const std::unordered_map<TerritoryID, Territory> &getTerritories() const;

    void addTerritory(const Territory& territory);
    void addRegion(const Region& region);
};

} // namespace european_conquest