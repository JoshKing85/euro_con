#include <gtest/gtest.h>

#include "european_conquest/core/orders/FortifyOrder.h"

using namespace european_conquest;
// Constructor Tests

TEST(FortifyOrderTests, StoresPlayerID)
{
    FortifyOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(FortifyOrderTests, StoresOrderType)
{
    FortifyOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(order.getOrderType(), OrderType::Fortify);
}

TEST(FortifyOrderTests, StartsIncomplete)
{
    FortifyOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_FALSE(order.isCompleted());
}
// Territory Tests

TEST(FortifyOrderTests, StoresFromTerritory)
{
    FortifyOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::England
    );
}

TEST(FortifyOrderTests, StoresToTerritory)
{
    FortifyOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::Scotland
    );
}

TEST(FortifyOrderTests, StoresFortifyTroopCount)
{
    FortifyOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(order.getFortifyTroopCount(), 5);
}