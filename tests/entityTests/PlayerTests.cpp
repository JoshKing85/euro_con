#include <gtest/gtest.h>

#include "european_conquest/entities/Player.h"
#include "european_conquest/enums.h"

#include <string>

using namespace european_conquest;
// Constructor Tests

TEST(PlayerTests, StartsWithZeroTroops)
{
    Player player(1);

    EXPECT_EQ(
        player.getTroopCount(),
        0
    );
}

TEST(PlayerTests, StartsWithNoTerritories)
{
    Player player(1);

    EXPECT_TRUE(
        player.getTerritoriesHeld().empty()
    );
}

TEST(PlayerTests, StartsWithNoAllies)
{
    Player player(1);

    EXPECT_TRUE(
        player.getAllies().empty()
    );
}
// Player Active Tests

TEST(PlayerTests, CanSetPlayerActive)
{
    Player player(1);

    player.setIsActive(false);

    EXPECT_FALSE(
        player.getIsActive()
    );
}
// Troop Tests

TEST(PlayerTests, CanAddTroops)
{
    Player player(1);

    player.addTroops(10);

    EXPECT_EQ(
        player.getTroopCount(),
        10
    );
}

TEST(PlayerTests, CanRemoveTroops)
{
    Player player(1);

    player.addTroops(10);
    player.removeTroops(3);

    EXPECT_EQ(
        player.getTroopCount(),
        7
    );
}

TEST(PlayerTests, TroopsCannotGoNegative)
{
    Player player(1);

    player.addTroops(5);
    player.removeTroops(100);

    EXPECT_EQ(
        player.getTroopCount(),
        0
    );
}
// Territory Tests

TEST(PlayerTests, CanAddTerritory)
{
    Player player(1);

    player.addTerritory(
        TerritoryID::England
    );

    EXPECT_EQ(
        player.getTerritoriesHeld().size(),
        1
    );
}

TEST(PlayerTests, DuplicateTerritoryNotAdded)
{
    Player player(1);

    player.addTerritory(
        TerritoryID::England
    );

    player.addTerritory(
        TerritoryID::England
    );

    EXPECT_EQ(
        player.getTerritoriesHeld().size(),
        1
    );
}

TEST(PlayerTests, CanRemoveTerritory)
{
    Player player(1);

    player.addTerritory(
        TerritoryID::England
    );

    player.removeTerritory(
        TerritoryID::England
    );

    EXPECT_TRUE(
        player.getTerritoriesHeld().empty()
    );
}
// Alliance Tests

TEST(PlayerTests, CannotAllySelf)
{
    Player player(1);

    player.addAlly(
        player.getPlayerID()
    );

    EXPECT_TRUE(
        player.getAllies().empty()
    );
}

TEST(PlayerTests, CanAddAlly)
{
    Player player(1);

    player.addAlly(999);

    EXPECT_EQ(
        player.getAllies().size(),
        1
    );
}

TEST(PlayerTests, DuplicateAllyNotAdded)
{
    Player player(1);

    player.addAlly(999);
    player.addAlly(999);

    EXPECT_EQ(
        player.getAllies().size(),
        1
    );
}

TEST(PlayerTests, CanRemoveAlly)
{
    Player player(1);

    player.addAlly(999);
    player.removeAlly(999);

    EXPECT_TRUE(
        player.getAllies().empty()
    );
}