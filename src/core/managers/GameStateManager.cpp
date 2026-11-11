#include "european_conquest/core/managers/GameStateManager.h"

#include "european_conquest/entities/Player.h"

namespace european_conquest {

    // CONSTRUCTOR

    GameStateManager::GameStateManager(
        Map& map,
        std::vector<Player>& players
    )
        : map(map),
        players(players)
    {
    }

    // TERRITORY METHODS

    void GameStateManager::updateTerritoryOwner(
        TerritoryID territoryID,
        int newOwnerID
    )
    {
        Territory& territory =
            map.getTerritory(territoryID);

        const int oldOwnerID =
            territory.getOwnerID();

        const RegionID regionID =
            territory.getRegionID();

        if (oldOwnerID == newOwnerID)
        {
            return;
        }

        // remove territory from previous owner

        if (oldOwnerID >= 0)
        {
            updatePlayerTerritories(
                oldOwnerID,
                territory,
                false
            );
        }

        // update territory owner

        territory.setOwner(newOwnerID);

        // give territory to new owner

        updatePlayerTerritories(
            newOwnerID,
            territory,
            true
        );

        // check whether the previous owner lost control of the region

        if (
            oldOwnerID >= 0 &&
            map.getRegion(regionID).getOwnerID() == oldOwnerID &&
            checkRegionOwnership(
                oldOwnerID,
                regionID
            ) == RegionID::None
            )
        {
            updatePlayerRegionOwnership(
                oldOwnerID,
                regionID,
                false
            );

            map.getRegion(regionID).setOwner(-1);
        }

        // check whether the new owner gained control of the region

        if (
            checkRegionOwnership(
                newOwnerID,
                regionID
            ) != RegionID::None
            )
        {
            updateRegionOwner(
                regionID,
                newOwnerID
            );
        }
    }

    void GameStateManager::updateTerritoryTroopCount(
        TerritoryID territoryID,
        int troopChange
    )
    {
        Territory& territory =
            map.getTerritory(territoryID);

        if (troopChange > 0)
        {
            territory.addTroops(troopChange);
        }
        else if (troopChange < 0)
        {
            territory.removeTroops(-troopChange);
        }
    }

    // REGION METHODS

    void GameStateManager::updateRegionOwner(
        RegionID regionID,
        int newOwnerID
    )
    {
        Region& region =
            map.getRegion(regionID);

        const int oldOwnerID =
            region.getOwnerID();

        if (oldOwnerID == newOwnerID)
        {
            return;
        }

        if (oldOwnerID >= 0)
        {
            updatePlayerRegionOwnership(
                oldOwnerID,
                regionID,
                false
            );
        }

        updatePlayerRegionOwnership(
            newOwnerID,
            regionID,
            true
        );

        region.setOwner(newOwnerID);
    }

    RegionID GameStateManager::checkRegionOwnership(
        int playerID,
        RegionID regionID
    )
    {
        const Region& region =
            map.getRegion(regionID);

        const std::vector<TerritoryID>& territories =
            region.getTerritories();

        for (const TerritoryID territoryID : territories)
        {
            const Territory& territory =
                map.getTerritory(territoryID);

            if (territory.getOwnerID() != playerID)
            {
                return RegionID::None;
            }
        }

        return regionID;
    }

    // PLAYER METHODS

    void GameStateManager::updatePlayerTerritories(
        int playerID,
        const Territory& territory,
        bool gainTerritory
    )
    {
        Player& player =
            players[playerID];

        if (gainTerritory)
        {
            player.addTerritory(
                territory.getID()
            );
        }
        else
        {
            player.removeTerritory(
                territory.getID()
            );
        }
    }

    void GameStateManager::updatePlayerRegionOwnership(
        int playerID,
        RegionID regionID,
        bool gainOwnership
    )
    {
        Player& player =
            players[playerID];

        if (gainOwnership)
        {
            player.addRegion(regionID);
        }
        else
        {
            player.removeRegion(regionID);
        }
    }

    void GameStateManager::updatePlayerTroopCount(
        int playerID,
        int troopChange
    )
    {
        Player& player =
            players[playerID];

        if (troopChange > 0)
        {
            player.addTroops(troopChange);
        }
        else if (troopChange < 0)
        {
            player.removeTroops(-troopChange);
        }
    }

    void GameStateManager::updatePlayerSet(
        int playerID,
        const std::vector<Card>& newSet
    )
    {
        Player& player =
            players[playerID];

        player.setPlayerSet(newSet);
    }
    // TERRITORY QUERIES
    int GameStateManager::getTerritoryOwnerID(
        TerritoryID territoryID
    ) const
    {
        return map.getTerritory(territoryID).getOwnerID();
    }

} // namespace european_conquest