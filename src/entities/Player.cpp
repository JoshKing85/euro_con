#include "european_conquest/entities/Player.h"
#include <vector>
#include <algorithm>

namespace european_conquest {

	// CONSTRUCTOR
	Player::Player(
		PlayerID playerID
	)
		: playerID(playerID),
		troopCount(0)
	{
	}

	// GETTERS
	PlayerID Player::getPlayerID() const {
		return playerID;
	}

	int Player::getTroopCount()const {

		return troopCount;
	}

	bool Player::getIsActive()const {
		return isActive;
	}

	const std::vector<Card>& Player::getPlayerSet() const {
		return currentSet;
	}

	const std::vector<TerritoryID>& Player::getTerritoriesHeld() const {
		return territoriesHeld;
	}
	const std::vector<PlayerID>& Player::getAllies() const {
		return allies;
	}
	const std::vector<RegionID>& Player::getRegionsOwned() const {
		return regionsOwned;
	}


	// TROOP MANAGEMENT
	void Player::addTroops(int amount) {
		troopCount += amount;
	}

	void Player::removeTroops(int amount) {
		troopCount = std::max(0, troopCount - amount);
	}

	// CARD MANAGEMENT
	void Player::setPlayerSet(const std::vector<Card>& newSet) {
		currentSet = newSet;
	}
	// PLAYER STATE
	void Player::setIsActive(bool active) {
		isActive = active;
	}

	// TERRITORY MANAGEMENT
	// Prevent duplicate territory ownership entries.
	void Player::addTerritory(TerritoryID territory) {
		if (std::find(territoriesHeld.begin(), territoriesHeld.end(), territory) == territoriesHeld.end()) {
			territoriesHeld.push_back(territory);
		}
	}
	
	void Player::removeTerritory(TerritoryID territory) {
		territoriesHeld.erase(
			std::remove(territoriesHeld.begin(), territoriesHeld.end(), territory),
			territoriesHeld.end()
		);
	}

	// REGION MANAGEMENT
	void Player::addRegion(RegionID region) {
		if (std::find(regionsOwned.begin(), regionsOwned.end(), region) == regionsOwned.end()) {
			regionsOwned.push_back(region);
		}
	}
	void Player::removeRegion(RegionID region) {
		regionsOwned.erase(
			std::remove(regionsOwned.begin(), regionsOwned.end(), region),
			regionsOwned.end()
		);
	}
	// ALLIANCE MANAGEMENT
	void Player::addAlly(PlayerID allyID) {
		if (allyID == playerID) return;

		if (std::find(allies.begin(), allies.end(), allyID) == allies.end()) {
			allies.push_back(allyID);
		}
	}

	void Player::removeAlly(PlayerID allyID) {
		allies.erase(
			std::remove(allies.begin(), allies.end(), allyID),
			allies.end()
		);
	}

}