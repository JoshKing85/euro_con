#include <gtest/gtest.h>

#include "european_conquest/core/managers/GameStateManager.h"
#include "european_conquest/entities/Card.h"
#include "european_conquest/entities/Player.h"
#include "european_conquest/entities/Territory.h"
#include "european_conquest/world/Region.h"
#include "european_conquest/world/Map.h"

#include <algorithm>
#include <vector>

using namespace european_conquest;

namespace {

    bool containsTerritory(
        const Player& player,
        TerritoryID territoryID
    )
    {
        const std::vector<TerritoryID>& territories =
            player.getTerritoriesHeld();

        return std::find(
            territories.begin(),
            territories.end(),
            territoryID
        ) != territories.end();
    }

    bool containsRegion(
        const Player& player,
        RegionID regionID
    )
    {
        const std::vector<RegionID>& regions =
            player.getRegionsOwned();

        return std::find(
            regions.begin(),
            regions.end(),
            regionID
        ) != regions.end();
    }

} // namespace
// Territory Troop Tests

TEST(GameStateManagerTests, UpdatesTerritoryTroopCountWhenIncreasing)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    map.addTerritory(england);

    std::vector<Player> players;

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryTroopCount(
        TerritoryID::England,
        5
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        5
    );
}

TEST(GameStateManagerTests, UpdatesTerritoryTroopCountWhenDecreasing)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    england.addTroops(5);

    map.addTerritory(england);

    std::vector<Player> players;

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryTroopCount(
        TerritoryID::England,
        -3
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        2
    );
}
// Player Territory Tests

TEST(GameStateManagerTests, AddsTerritoryToPlayer)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTerritories(
        0,
        england,
        true
    );

    EXPECT_TRUE(
        containsTerritory(
            players[0],
            TerritoryID::England
        )
    );
}

TEST(GameStateManagerTests, RemovesTerritoryFromPlayer)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    std::vector<Player> players;
    players.emplace_back(0);

    players[0].addTerritory(
        TerritoryID::England
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTerritories(
        0,
        england,
        false
    );

    EXPECT_FALSE(
        containsTerritory(
            players[0],
            TerritoryID::England
        )
    );
}
// Territory Ownership Tests

TEST(GameStateManagerTests, TransfersTerritoryBetweenPlayers)
{
    Map map;

    Region britishIsles(
        RegionID::BritishIsles,
        5,
        {
            TerritoryID::England,
            TerritoryID::Scotland,
            TerritoryID::France
        },
        {
            TerritoryID::England
        }
    );

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England,
            TerritoryID::France
        }
    );

    Territory wales(
        TerritoryID::France,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    england.setOwner(0);
    scotland.setOwner(1);
    wales.setOwner(0);

    map.addRegion(britishIsles);
    map.addTerritory(england);
    map.addTerritory(scotland);
    map.addTerritory(wales);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addTerritory(
        TerritoryID::England
    );

    players[0].addTerritory(
        TerritoryID::France
    );

    players[1].addTerritory(
        TerritoryID::Scotland
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryOwner(
        TerritoryID::England,
        1
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getOwnerID(),
        1
    );

    EXPECT_FALSE(
        containsTerritory(
            players[0],
            TerritoryID::England
        )
    );

    EXPECT_TRUE(
        containsTerritory(
            players[1],
            TerritoryID::England
        )
    );
}

TEST(GameStateManagerTests, TerritoryTransferGrantsRegionOwnership)
{
    Map map;

    Region britishIsles(
        RegionID::BritishIsles,
        5,
        {
            TerritoryID::England,
            TerritoryID::Scotland
        },
        {
            TerritoryID::England
        }
    );

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    england.setOwner(0);
    scotland.setOwner(1);

    map.addRegion(britishIsles);
    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addTerritory(
        TerritoryID::England
    );

    players[1].addTerritory(
        TerritoryID::Scotland
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryOwner(
        TerritoryID::England,
        1
    );

    EXPECT_EQ(
        map.getRegion(
            RegionID::BritishIsles
        ).getOwnerID(),
        1
    );

    EXPECT_TRUE(
        containsRegion(
            players[1],
            RegionID::BritishIsles
        )
    );
}

TEST(GameStateManagerTests, TerritoryTransferRemovesRegionOwnership)
{
    Map map;

    Region britishIsles(
        RegionID::BritishIsles,
        5,
        {
            TerritoryID::England,
            TerritoryID::Scotland
        },
        {
            TerritoryID::England
        }
    );

    britishIsles.setOwner(0);

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    england.setOwner(0);
    scotland.setOwner(0);

    map.addRegion(britishIsles);
    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addTerritory(
        TerritoryID::England
    );

    players[0].addTerritory(
        TerritoryID::Scotland
    );

    players[0].addRegion(
        RegionID::BritishIsles
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryOwner(
        TerritoryID::England,
        1
    );

    EXPECT_EQ(
        map.getRegion(
            RegionID::BritishIsles
        ).getOwnerID(),
        -1
    );

    EXPECT_FALSE(
        containsRegion(
            players[0],
            RegionID::BritishIsles
        )
    );
}
// Region Ownership Check Tests

TEST(GameStateManagerTests, ReturnsRegionWhenPlayerOwnsAllTerritories)
{
    Map map;

    Region britishIsles(
        RegionID::BritishIsles,
        5,
        {
            TerritoryID::England,
            TerritoryID::Scotland
        },
        {
            TerritoryID::England
        }
    );

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    england.setOwner(0);
    scotland.setOwner(0);

    map.addRegion(britishIsles);
    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    EXPECT_EQ(
        gameStateManager.checkRegionOwnership(
            0,
            RegionID::BritishIsles
        ),
        RegionID::BritishIsles
    );
}

TEST(GameStateManagerTests, ReturnsNoneWhenPlayerDoesNotOwnAllTerritories)
{
    Map map;

    Region britishIsles(
        RegionID::BritishIsles,
        5,
        {
            TerritoryID::England,
            TerritoryID::Scotland
        },
        {
            TerritoryID::England
        }
    );

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    england.setOwner(0);
    scotland.setOwner(1);

    map.addRegion(britishIsles);
    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    GameStateManager gameStateManager(
        map,
        players
    );

    EXPECT_EQ(
        gameStateManager.checkRegionOwnership(
            0,
            RegionID::BritishIsles
        ),
        RegionID::None
    );
}
// Region Update Tests

TEST(GameStateManagerTests, TransfersRegionBetweenPlayers)
{
    Map map;

    Region britishIsles(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    britishIsles.setOwner(0);

    map.addRegion(britishIsles);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addRegion(
        RegionID::BritishIsles
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateRegionOwner(
        RegionID::BritishIsles,
        1
    );

    EXPECT_EQ(
        map.getRegion(
            RegionID::BritishIsles
        ).getOwnerID(),
        1
    );

    EXPECT_FALSE(
        containsRegion(
            players[0],
            RegionID::BritishIsles
        )
    );

    EXPECT_TRUE(
        containsRegion(
            players[1],
            RegionID::BritishIsles
        )
    );
}
// Player Region Tests

TEST(GameStateManagerTests, AddsRegionToPlayer)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerRegionOwnership(
        0,
        RegionID::BritishIsles,
        true
    );

    EXPECT_TRUE(
        containsRegion(
            players[0],
            RegionID::BritishIsles
        )
    );
}

TEST(GameStateManagerTests, RemovesRegionFromPlayer)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    players[0].addRegion(
        RegionID::BritishIsles
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerRegionOwnership(
        0,
        RegionID::BritishIsles,
        false
    );

    EXPECT_FALSE(
        containsRegion(
            players[0],
            RegionID::BritishIsles
        )
    );
}
// Player Troop Tests

TEST(GameStateManagerTests, UpdatesPlayerTroopCountWhenIncreasing)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTroopCount(
        0,
        10
    );

    EXPECT_EQ(
        players[0].getTroopCount(),
        10
    );
}

TEST(GameStateManagerTests, UpdatesPlayerTroopCountWhenDecreasing)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    players[0].addTroops(10);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTroopCount(
        0,
        -6
    );

    EXPECT_EQ(
        players[0].getTroopCount(),
        4
    );
}
// Player Set Tests

TEST(GameStateManagerTests, UpdatesPlayerSet)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> newSet{
        Card(
            CardType::Infantry,
            TerritoryID::England,
            RegionID::BritishIsles
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Prussia,
            RegionID::WesternEurope
        ),
        Card(
            CardType::Artillery,
            TerritoryID::Bohemia,
            RegionID::AustrianEmpire
        )
    };

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerSet(
        0,
        newSet
    );

    const std::vector<Card>& playerSet =
        players[0].getPlayerSet();

    ASSERT_EQ(
        playerSet.size(),
        3
    );

    EXPECT_EQ(
        playerSet[0].getCardType(),
        CardType::Infantry
    );

    EXPECT_EQ(
        playerSet[0].getTerritoryID(),
        TerritoryID::England
    );

    EXPECT_EQ(
        playerSet[1].getCardType(),
        CardType::Cavalry
    );

    EXPECT_EQ(
        playerSet[1].getTerritoryID(),
        TerritoryID::Prussia
    );

    EXPECT_EQ(
        playerSet[2].getCardType(),
        CardType::Artillery
    );

    EXPECT_EQ(
        playerSet[2].getTerritoryID(),
        TerritoryID::Bohemia
    );
}