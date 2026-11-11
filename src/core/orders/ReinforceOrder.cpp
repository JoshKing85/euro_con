#include "european_conquest/core/orders/ReinforceOrder.h"

namespace european_conquest {
	// CONSTRUCTOR

	ReinforceOrder::ReinforceOrder(
		int playerID, 
		TerritoryID territoryID,
		int reinforceTroopCount)
		: Order(playerID, OrderType::Reinforce),
		  territoryID(territoryID),
		  reinforceTroopCount(reinforceTroopCount)
	{
	}

	// GETTERS

	TerritoryID ReinforceOrder::getTerritoryID() const {
		return territoryID;
	}

	int ReinforceOrder::getReinforceTroopCount() const {
		return reinforceTroopCount;
	}

	// TROOP ADJUSTMENT

	void ReinforceOrder::setReinforceTroopCount(int reinforceTroopCount)
	{
		this->reinforceTroopCount = reinforceTroopCount;
	}
}