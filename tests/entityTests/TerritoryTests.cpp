#include <gtest/gtest.h>

#include "european_conquest/entities/Territory.h"
#include "european_conquest/enums.h"

using namespace european_conquest;
// Constructor Tests

TEST(TerritoryTests, StartsWithZeroTroops)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    EXPECT_EQ(territory.getTroopCount(), 0);
}

TEST(TerritoryTests, StoresCorrectTerritoryID)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    EXPECT_EQ(
        territory.getID(),
        TerritoryID::England
    );
}

TEST(TerritoryTests, StoresCorrectRegionID)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    EXPECT_EQ(
        territory.getRegionID(),
        RegionID::BritishIsles
    );
}
// Adjacency Tests

TEST(TerritoryTests, StoresAdjacentTerritories)
{
    std::vector<TerritoryID> neighbours =
    {
        TerritoryID::Scotland,
        TerritoryID::Spain
    };

    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        neighbours
    );

    EXPECT_EQ(
        territory.getAdjacentTerritories().size(),
        2
    );
}
// Troop Tests

TEST(TerritoryTests, CanAddTroops)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    territory.addTroops(10);

    EXPECT_EQ(
        territory.getTroopCount(),
        10
    );
}

TEST(TerritoryTests, CanRemoveTroops)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    territory.addTroops(10);
    territory.removeTroops(3);

    EXPECT_EQ(
        territory.getTroopCount(),
        7
    );
}

TEST(TerritoryTests, TroopsCannotGoBelowZero)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    territory.addTroops(3);
    territory.removeTroops(100);

    EXPECT_EQ(
        territory.getTroopCount(),
        0
    );
}

TEST(TerritoryTests, TerritoryCanLoseFinalTroop)
{
    Territory territory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    territory.addTroops(1);
    territory.removeTroops(1);

    EXPECT_EQ(
        territory.getTroopCount(),
        0
    );
}