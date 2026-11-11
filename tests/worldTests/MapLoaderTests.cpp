#include <gtest/gtest.h>

#include "european_conquest/world/MapLoader.h"

#include "european_conquest/utils/RegionConverter.h"
#include "european_conquest/utils/TerritoryConverter.h"

using namespace european_conquest;
// Region Conversion Tests

TEST(MapLoaderTests, ConvertsBritishIsles)
{
    EXPECT_EQ(
        stringToRegionID("BritishIsles"),
        RegionID::BritishIsles
    );
}

TEST(MapLoaderTests, ConvertsGermanStates)
{
    EXPECT_EQ(
        stringToRegionID("GermanStates"),
        RegionID::GermanStates
    );
}

TEST(MapLoaderTests, UnknownRegionThrows)
{
    EXPECT_THROW(
        stringToRegionID("Atlantis"),
        std::invalid_argument
    );
}
// Territory Conversion Tests

TEST(MapLoaderTests, ConvertsEngland)
{
    EXPECT_EQ(
        stringToTerritoryID("England"),
        TerritoryID::England
    );
}

TEST(MapLoaderTests, ConvertsPrussia)
{
    EXPECT_EQ(
        stringToTerritoryID("Prussia"),
        TerritoryID::Prussia
    );
}

TEST(MapLoaderTests, UnknownTerritoryThrows)
{
    EXPECT_THROW(
        stringToTerritoryID("MiddleEarth"),
        std::invalid_argument
    );
}
// File Tests

TEST(MapLoaderTests, MissingFileThrows)
{
    EXPECT_THROW(
        loadMap("does_not_exist.json"),
        std::runtime_error
    );
}