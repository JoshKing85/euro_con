#pragma once

#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {
class AttackOrder;
class FortifyOrder;
class ReinforceOrder;
class MoveTroopsOrder;

	/**
 * Provides logging operations for gameplay orders.
 * Associates logging with a player and accepts attack, fortify,
 * reinforcement and troop movement order collections.
 */
	class LogManager {
		
		private:

			int playerID;

		public:
			LogManager(int playerID);

			void logAttackOrders(const std::vector<AttackOrder>& attackOrders);
			void logFortifyOrders(const std::vector<FortifyOrder>& fortiyOrders);
			void logReinforceOrders(const std::vector<ReinforceOrder>& reinforceOrders);
			void logMoveTroopsOrders(const std::vector<MoveTroopsOrder>& moveTroopsOrders);
	};
}