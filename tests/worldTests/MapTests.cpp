#include <gtest/gtest.h>

#include "european_conquest/world/Map.h"
#include "european_conquest/world/Region.h"
#include "european_conquest/entities/Territory.h"
#include "european_conquest/enums.h"

using namespace european_conquest;
// Territory Tests

TEST(MapTests, TerritoryCanBeAdded)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    map.addTerritory(england);

    EXPECT_EQ(
        map.getTerritory(TerritoryID::England).getID(),
        TerritoryID::England
    );
}

TEST(MapTests, TerritoryLookupIndependentOfInsertionOrder)
{
    Map map;

    map.addTerritory(
        Territory(
            TerritoryID::France,
            RegionID::BritishIsles,
            {}
        )
    );

    map.addTerritory(
        Territory(
            TerritoryID::England,
            RegionID::BritishIsles,
            {}
        )
    );

    EXPECT_EQ(
        map.getTerritory(TerritoryID::England).getID(),
        TerritoryID::England
    );

    EXPECT_EQ(
        map.getTerritory(TerritoryID::France).getID(),
        TerritoryID::France
    );
}

TEST(MapTests, TerritoryReferenceCanBeModified)
{
    Map map;

    map.addTerritory(
        Territory(
            TerritoryID::England,
            RegionID::BritishIsles,
            {}
        )
    );

    map.getTerritory(TerritoryID::England)
        .addTroops(5);

    EXPECT_EQ(
        map.getTerritory(TerritoryID::England)
        .getTroopCount(),
        5
    );
}
// Region Tests

TEST(MapTests, RegionCanBeAdded)
{
    Map map;

    Region region(
        RegionID::BritishIsles,
        5,
        {},
        {}
    );

    map.addRegion(region);

    EXPECT_EQ(
        map.getRegion(
            RegionID::BritishIsles
        ).getRegionID(),
        RegionID::BritishIsles
    );
}

TEST(MapTests, RegionLookupIndependentOfInsertionOrder)
{
    Map map;

    map.addRegion(
        Region(
            RegionID::GermanStates,
            5,
            {},
            {}
        )
    );

    map.addRegion(
        Region(
            RegionID::BritishIsles,
            5,
            {},
            {}
        )
    );

    EXPECT_EQ(
        map.getRegion(
            RegionID::BritishIsles
        ).getRegionID(),
        RegionID::BritishIsles
    );

    EXPECT_EQ(
        map.getRegion(
            RegionID::GermanStates
        ).getRegionID(),
        RegionID::GermanStates
    );
}

TEST(MapTests, RegionReferenceCanBeModified)
{
    Map map;

    map.addRegion(
        Region(
            RegionID::BritishIsles,
            5,
            {},
            {}
        )
    );

    map.getRegion(
        RegionID::BritishIsles
    ).setOwner(42);

    EXPECT_EQ(
        map.getRegion(
            RegionID::BritishIsles
        ).getOwnerID(),
        42
    );
}