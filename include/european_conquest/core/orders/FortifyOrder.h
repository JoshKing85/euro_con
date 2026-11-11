#pragma once

#include "european_conquest/core/orders/Order.h"
#include "european_conquest/enums.h"

namespace european_conquest {
	/** Represents troop movement between owned territories during fortification. */
class FortifyOrder : public Order {

		private:

			TerritoryID fromTerritory;
            TerritoryID toTerritory;
            int troopCount;

		public:
            FortifyOrder(
				int playerID,
				TerritoryID fromTerritory, 
				TerritoryID toTerritory,
                int fortifyTroopCount);

			TerritoryID getFromTerritory() const;
			TerritoryID getToTerritory() const;
			int getFortifyTroopCount() const;

			void updateFortifyOrder(bool add);




	};
}// namespace european_conquest