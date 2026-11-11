#include "european_conquest/core/orders/MoveTroopsOrder.h"

namespace european_conquest {

	// CONSTRUCTOR

	MoveTroopsOrder::MoveTroopsOrder(int playerID, TerritoryID fromTerritory, TerritoryID toTerritory, int troopsMoved)
		: Order(playerID, OrderType::MoveTroops),
		fromTerritory(fromTerritory),
		toTerritory(toTerritory),
		troopsMoved(troopsMoved) {
	}

	// TROOP ADJUSTMENT

	void MoveTroopsOrder::updateMoveTroopsOrder(bool add)
	{
		if (add) 
		{
			troopsMoved ++;
		}
		else
		{
			troopsMoved --;
		}
	}

	// GETTERS

	TerritoryID MoveTroopsOrder::getFromTerritory() const {
		return fromTerritory;
	}

	TerritoryID MoveTroopsOrder::getToTerritory() const {
		return toTerritory;
	}

	int MoveTroopsOrder::getTroopsMoved() const {
		return troopsMoved;
	}
}