#pragma once

#include "european_conquest/enums.h"
#include <vector>

namespace european_conquest {

/** Stores a territory’s ownership, troops and map relationships. */
class Territory {
private:
  TerritoryID territoryID;
  RegionID regionID;
  std::vector<TerritoryID> adjacentTerritories;

  int troopCount;
  int ownerID;

public:
  Territory(TerritoryID id, RegionID region,
            const std::vector<TerritoryID> &adjacentIDs);

  TerritoryID getID() const;
  RegionID getRegionID() const;
  const std::vector<TerritoryID> &getAdjacentTerritories() const;

  int getTroopCount() const;
  int getOwnerID() const;
  TerritoryID getTerritoryID() const;

  void setOwner(int newOwnerID);
  void addTroops(int amount);
  void removeTroops(int amount);
};
} // namespace european_conquest