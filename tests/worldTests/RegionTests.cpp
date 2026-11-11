#include <gtest/gtest.h>

#include "european_conquest/world/Region.h"
#include "european_conquest/enums.h"

using namespace european_conquest;
// Constructor Tests

TEST(RegionTests, StoresCorrectRegionID)
{
    Region region(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        region.getRegionID(),
        RegionID::BritishIsles
    );
}

TEST(RegionTests, StoresCorrectControlBonus)
{
    Region region(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        region.getControlBonus(),
        5
    );
}

TEST(RegionTests, StartsWithoutOwner)
{
    Region region(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        region.getOwnerID(),
        -1
    );
}
// Territory Storage Tests

TEST(RegionTests, StoresTerritories)
{
    std::vector<TerritoryID> territories =
    {
        TerritoryID::England,
        TerritoryID::Scotland,
        TerritoryID::France
    };

    Region region(
        RegionID::BritishIsles,
        5,
        territories,
        {}
    );

    EXPECT_EQ(
        region.getTerritories().size(),
        3
    );
}

TEST(RegionTests, StoresBorderTerritories)
{
    std::vector<TerritoryID> borders =
    {
        TerritoryID::England,
        TerritoryID::Wales,
        TerritoryID::Portugal
    };

    Region region(
        RegionID::BritishIsles,
        5,
        {},
        borders
    );

    EXPECT_EQ(
        region.getBorderTerritories().size(),
        3
    );
}
// Owner Tests

TEST(RegionTests, OwnerCanBeAssigned)
{
    Region region(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    region.setOwner(42);

    EXPECT_EQ(
        region.getOwnerID(),
        42
    );
}

TEST(RegionTests, OwnerCanBeChanged)
{
    Region region(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    region.setOwner(1);
    region.setOwner(2);

    EXPECT_EQ(
        region.getOwnerID(),
        2
    );
}