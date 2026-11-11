#pragma once

#include "european_conquest/core/orders/Order.h"
#include "european_conquest/enums.h"

namespace european_conquest {

/** Represents troops advancing into a territory captured in combat. */
class MoveTroopsOrder : public Order {

private:
  TerritoryID fromTerritory;
  TerritoryID toTerritory;
  int troopsMoved;

public:
  MoveTroopsOrder(int playerID, TerritoryID fromTerritory,
                  TerritoryID toTerritory, int troopsMoved);

  void updateMoveTroopsOrder(bool add);

  TerritoryID getFromTerritory() const;
  TerritoryID getToTerritory() const;
  int getTroopsMoved() const;
};

} // namespace european_conquest