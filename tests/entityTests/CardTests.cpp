#include <gtest/gtest.h>

#include "european_conquest/entities/Card.h"

namespace european_conquest {

    TEST(CardTests, StoresCardType)
    {
        Card card(
            CardType::Infantry,
            TerritoryID::England,
            RegionID::BritishIsles
        );

        EXPECT_EQ(card.getCardType(), CardType::Infantry);
    }

    TEST(CardTests, StoresTerritoryID)
    {
        Card card(
            CardType::Cavalry,
            TerritoryID::England,
            RegionID::BritishIsles
        );

        ASSERT_TRUE(card.getTerritoryID().has_value());
        EXPECT_EQ(
            card.getTerritoryID().value(),
            TerritoryID::England
        );
    }

    TEST(CardTests, StoresRegionID)
    {
        Card card(
            CardType::Artillery,
            TerritoryID::England,
            RegionID::BritishIsles
        );

        ASSERT_TRUE(card.getRegionID().has_value());
        EXPECT_EQ(
            card.getRegionID().value(),
            RegionID::BritishIsles
        );
    }

    TEST(CardTests, TerritoryCardHasTerritory)
    {
        Card card(
            CardType::Infantry,
            TerritoryID::England,
            RegionID::BritishIsles
        );

        EXPECT_TRUE(card.hasTerritory());
    }

    TEST(CardTests, WildCardHasNoTerritory)
    {
        Card card(CardType::Wild);

        EXPECT_FALSE(card.hasTerritory());
        EXPECT_FALSE(card.getTerritoryID().has_value());
        EXPECT_FALSE(card.getRegionID().has_value());
    }

    TEST(CardTests, WildCardStoresWildType)
    {
        Card card(CardType::Wild);

        EXPECT_EQ(card.getCardType(), CardType::Wild);
    }

}