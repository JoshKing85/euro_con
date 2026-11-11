#include "european_conquest/core/orders/FortifyOrder.h"

namespace european_conquest {
	// CONSTRUCTOR

	FortifyOrder::FortifyOrder(
		int playerID,
		TerritoryID fromTerritory,
		TerritoryID toTerritory,
		int troopCount)
		: Order(playerID, OrderType::Fortify),
		fromTerritory(fromTerritory),
		toTerritory(toTerritory),
		troopCount(troopCount)
	{
	}

	// GETTERS

	TerritoryID FortifyOrder::getFromTerritory() const{

		return fromTerritory;
	}

	TerritoryID FortifyOrder::getToTerritory() const {

		return toTerritory;
	}

	int FortifyOrder::getFortifyTroopCount() const {

		return troopCount;
	}

	// TROOP ADJUSTMENT

	void FortifyOrder::updateFortifyOrder(bool add)
	{
		if (add)
		{
			troopCount++;
		}
		else
		{
			troopCount--;
		}
	}
	
}