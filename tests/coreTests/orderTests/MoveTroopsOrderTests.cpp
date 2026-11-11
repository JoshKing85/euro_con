#include <gtest/gtest.h>

#include "european_conquest/core/orders/MoveTroopsOrder.h"

using namespace european_conquest;
// Constructor Tests

TEST(MoveTroopsOrderTests, StoresPlayerID)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(MoveTroopsOrderTests, StoresOrderType)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(order.getOrderType(), OrderType::MoveTroops);
}

TEST(MoveTroopsOrderTests, StartsIncomplete)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_FALSE(order.isCompleted());
}
// Territory Tests

TEST(MoveTroopsOrderTests, StoresFromTerritory)
{
    MoveTroopsOrder order(
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

TEST(MoveTroopsOrderTests, StoresToTerritory)
{
    MoveTroopsOrder order(
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

TEST(MoveTroopsOrderTests, StoresTroopsMoved)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::England,
        TerritoryID::Scotland,
        5
    );

    EXPECT_EQ(
        order.getTroopsMoved(),
        5
    );
}