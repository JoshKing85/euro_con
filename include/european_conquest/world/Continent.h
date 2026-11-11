#pragma once

#include "european_conquest/enums.h"
#include <vector>

namespace european_conquest {

/** Stores region membership, border territories, ownership and its reinforcement bonus. */
class Continent {
private:
  ContinentID continentID;
  int controlBonus;

  std::vector<TerritoryID> territories;
  std::vector<TerritoryID> borderTerritories;

  int ownerID;

public:
  Continent(ContinentID id, int bonus,
            const std::vector<TerritoryID> &territories,
            const std::vector<TerritoryID> &borderTerritories);
  // GETTERS
  ContinentID getContinentID() const;
  int getControlBonus() const;
  const std::vector<TerritoryID> &getTerritories() const;
  const std::vector<TerritoryID> &getBorderTerritories() const;
  int getOwnerID() const;
  // SETTERS
  void setOwner(int newOwnerID);
};

} // namespace european_conquest