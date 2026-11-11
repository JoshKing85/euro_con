#include <gtest/gtest.h>

#include "european_conquest/world/Continent.h"
#include "european_conquest/enums.h"

using namespace european_conquest;
// Constructor Tests

TEST(ContinentTests, StoresCorrectContinentID)
{
    Continent continent(
        ContinentID::BritishIsles,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        continent.getContinentID(),
        ContinentID::BritishIsles
    );
}

TEST(ContinentTests, StoresCorrectControlBonus)
{
    Continent continent(
        ContinentID::BritishIsles,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        continent.getControlBonus(),
        5
    );
}

TEST(ContinentTests, StartsWithoutOwner)
{
    Continent continent(
        ContinentID::BritishIsles,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        continent.getOwnerID(),
        -1
    );
}
// Territory Storage Tests

TEST(ContinentTests, StoresTerritories)
{
    std::vector<TerritoryID> territories =
    {
        TerritoryID::England,
        TerritoryID::Scotland,
        TerritoryID::France
    };

    Continent continent(
        ContinentID::BritishIsles,
        5,
        territories,
        {}
    );

    EXPECT_EQ(
        continent.getTerritories().size(),
        3
    );
}

TEST(ContinentTests, StoresBorderTerritories)
{
    std::vector<TerritoryID> borders =
    {
        TerritoryID::England,
        TerritoryID::Wales,
        TerritoryID::Portugal
    };

    Continent continent(
        ContinentID::BritishIsles,
        5,
        {},
        borders
    );

    EXPECT_EQ(
        continent.getBorderTerritories().size(),
        3
    );
}
// Owner Tests

TEST(ContinentTests, OwnerCanBeAssigned)
{
    Continent continent(
        ContinentID::BritishIsles,
        5,
        {},
        {}
    );

    continent.setOwner(42);

    EXPECT_EQ(
        continent.getOwnerID(),
        42
    );
}

TEST(ContinentTests, OwnerCanBeChanged)
{
    Continent continent(
        ContinentID::BritishIsles,
        5,
        {},
        {}
    );

    continent.setOwner(1);
    continent.setOwner(2);

    EXPECT_EQ(
        continent.getOwnerID(),
        2
    );
}