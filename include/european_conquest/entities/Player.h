#pragma once
#include <vector>
#include <string>
#include "european_conquest/enums.h"
#include "european_conquest/entities/Card.h"

namespace european_conquest {

using PlayerID = int;

/** Stores a player’s identity, territories, troops and cards. */
class Player {

private:
    static PlayerID nextID;

    PlayerID playerID;
   
    int troopCount;

    std::vector<Card> currentSet;
    std::vector<TerritoryID> territoriesHeld;
    std::vector<RegionID> regionsOwned;
    std::vector<PlayerID> allies;

    bool isActive = true;

public:
    // Constructor
    Player(PlayerID playerID);

    // --- Getters ---
    PlayerID getPlayerID() const;
    int getTroopCount() const;
    bool getIsActive()const;

    const std::vector<Card>& getPlayerSet() const;
    const std::vector<TerritoryID>& getTerritoriesHeld() const;
    const std::vector<RegionID> &getRegionsOwned() const;
    const std::vector<PlayerID>& getAllies() const;

    // --- Troop management ---
    void addTroops(int amount);
    void removeTroops(int amount);

    // --- Player Management ---
    void setIsActive(bool active);

    // --- Card management ---
    void setPlayerSet(const std::vector<Card>& newSet);

    // --- Territory management ---
    void addTerritory(TerritoryID territory);
    void removeTerritory(TerritoryID territory);

    // --- Region management ---
    void addRegion(RegionID region);
    void removeRegion(RegionID region);

    // --- Alliance management ---
    void addAlly(PlayerID allyID);
    void removeAlly(PlayerID allyID);
};

}