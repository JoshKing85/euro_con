#pragma once

#include "european_conquest/enums.h"
#include "european_conquest/world/Map.h"

#include <vector>

namespace european_conquest {

class Player;
class Territory;
class Card;

/**
 * Coordinates updates to the map and player records.
 * Maintains territory ownership, troop counts and region ownership
 * through operations on the referenced game state.
 */
class GameStateManager {
		private:
			Map &map;
			std::vector<Player> &players;

		public:
			GameStateManager(Map &map, std::vector<Player> &players);

			// TERRITORY METHODS
			void updateTerritoryOwner(TerritoryID territoryID, int newOwnerID);
			void updateTerritoryTroopCount(TerritoryID territoryID, int newTroopCount);


			// REGION METHODS
			void updateRegionOwner(RegionID regionID, int newOwnerID);
			RegionID checkRegionOwnership(int playerID, RegionID regionID);


			// PLAYER METHODS
			void updatePlayerTerritories(int playerID, const Territory &territory, bool gainTerritory);
			void updatePlayerRegionOwnership(int playerID, RegionID regionID, bool gainOwnership);
			void updatePlayerTroopCount(int playerID, int newTroopCount);
			void updatePlayerSet(int playerID, const std::vector<Card> &newSet);

			// GETTER METHODS
			int getTerritoryOwnerID(TerritoryID territoryID) const;
	};

} // namespace european_conquest