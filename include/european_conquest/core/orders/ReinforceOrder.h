#pragma once

#include "european_conquest/core/orders/Order.h"
#include "european_conquest/enums.h"

namespace european_conquest {
	/** Represents troops assigned to a territory during reinforcement. */
class ReinforceOrder : public Order {

		private:
          TerritoryID territoryID;
          int reinforceTroopCount;

		public:

			ReinforceOrder(
				int playerID, 
				TerritoryID territoryID,
                int reinforceTroopCount);

			TerritoryID getTerritoryID() const;
            int getReinforceTroopCount() const;
			void setReinforceTroopCount(int reinforceTroopCount);
	};
}// namespace european_conquest