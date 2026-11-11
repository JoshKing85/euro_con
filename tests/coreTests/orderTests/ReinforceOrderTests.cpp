#include <gtest/gtest.h>

#include "european_conquest/core/orders/ReinforceOrder.h"

using namespace european_conquest;
// Constructor Tests

TEST(ReinforceOrderTests, StoresPlayerID)
{
    ReinforceOrder order(
        1,
        TerritoryID::England,
        8
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(ReinforceOrderTests, StoresOrderType)
{
    ReinforceOrder order(
        1,
        TerritoryID::England,
        8
    );

    EXPECT_EQ(order.getOrderType(), OrderType::Reinforce);
}

TEST(ReinforceOrderTests, StartsIncomplete)
{
    ReinforceOrder order(
        1,
        TerritoryID::England,
        8
    );

    EXPECT_FALSE(order.isCompleted());
}
// Data Tests

TEST(ReinforceOrderTests, StoresTerritoryID)
{
    ReinforceOrder order(
        1,
        TerritoryID::England,
        8
    );

    EXPECT_EQ(
        order.getTerritoryID(),
        TerritoryID::England
    );
}

TEST(ReinforceOrderTests, StoresReinforceTroopCount)
{
    ReinforceOrder order(
        1,
        TerritoryID::England,
        8
    );

    EXPECT_EQ(
        order.getReinforceTroopCount(),
        8
    );
}