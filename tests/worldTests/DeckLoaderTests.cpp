#include <gtest/gtest.h>

#include "european_conquest/world/DeckLoader.h"

#include <unordered_set>
#include <vector>

using namespace european_conquest;

namespace {

    Map buildTestMap()
    {
        Map map;

        const std::vector<TerritoryID> territoryIDs{
            TerritoryID::England,
            TerritoryID::Scotland,
            TerritoryID::Wales,
            TerritoryID::Ireland,
            TerritoryID::Portugal,
            TerritoryID::Spain,
            TerritoryID::France,
            TerritoryID::Netherlands,
            TerritoryID::Corsica,

            TerritoryID::Sardinia,
            TerritoryID::Prussia,
            TerritoryID::Poland,
            TerritoryID::Hanover,

            TerritoryID::Saxony,
            TerritoryID::Westphalia,
            TerritoryID::Bavaria,
            TerritoryID::Austria,
            TerritoryID::Hungary,
            TerritoryID::Serbia,
            TerritoryID::Wallachia,

            TerritoryID::Bulgaria,
            TerritoryID::Greece,
            TerritoryID::Bohemia,
            TerritoryID::Piedmont,
            TerritoryID::Lombardy,
            TerritoryID::Tuscany,

            TerritoryID::Naples,
            TerritoryID::Sicily,
            TerritoryID::Denmark,
            TerritoryID::Norway,
            TerritoryID::Sweden,
            TerritoryID::Finland,
            TerritoryID::StPetersburg,
            TerritoryID::Novgorod,
            TerritoryID::Moscow,
            TerritoryID::Smolensk,
            TerritoryID::Lithuania,
            TerritoryID::Belarus,

            TerritoryID::Ukraine,
            TerritoryID::Moldavia,
            TerritoryID::Crimea,
            TerritoryID::EasternRussia
        };

        for (TerritoryID territoryID : territoryIDs)
        {
            map.addTerritory(
                Territory(
                    territoryID,
                    RegionID::BritishIsles,
                    {}
                )
            );
        }

        return map;
    }

}
// Deck Creation Tests

TEST(DeckLoaderTests, CreatesDeckWithFortySixCards)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    for (int i = 0; i < 46; i++)
    {
        EXPECT_NO_THROW(deck.getNextCard());
    }
}

TEST(DeckLoaderTests, CreatesFourteenOfEachTerritoryCardType)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    int infantryCount = 0;
    int cavalryCount = 0;
    int artilleryCount = 0;
    int wildCount = 0;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        switch (card.getCardType())
        {
        case CardType::Infantry:
            infantryCount++;
            break;

        case CardType::Cavalry:
            cavalryCount++;
            break;

        case CardType::Artillery:
            artilleryCount++;
            break;

        case CardType::Wild:
            wildCount++;
            break;
        }
    }

    EXPECT_EQ(infantryCount, 14);
    EXPECT_EQ(cavalryCount, 14);
    EXPECT_EQ(artilleryCount, 14);
    EXPECT_EQ(wildCount, 4);
}

TEST(DeckLoaderTests, TerritoryCardsContainTerritoryAndRegionIDs)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    int territoryCardCount = 0;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        if (card.getCardType() != CardType::Wild)
        {
            EXPECT_TRUE(card.hasTerritory());
            EXPECT_TRUE(card.getTerritoryID().has_value());
            EXPECT_TRUE(card.getRegionID().has_value());

            territoryCardCount++;
        }
    }

    EXPECT_EQ(territoryCardCount, 42);
}

TEST(DeckLoaderTests, WildCardsContainNoTerritoryOrRegion)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    int wildCount = 0;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        if (card.getCardType() == CardType::Wild)
        {
            EXPECT_FALSE(card.hasTerritory());
            EXPECT_FALSE(card.getTerritoryID().has_value());
            EXPECT_FALSE(card.getRegionID().has_value());

            wildCount++;
        }
    }

    EXPECT_EQ(wildCount, 4);
}

TEST(DeckLoaderTests, EveryTerritoryAppearsOnce)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    std::unordered_set<TerritoryID> foundTerritories;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        if (card.hasTerritory())
        {
            foundTerritories.insert(
                card.getTerritoryID().value()
            );
        }
    }

    EXPECT_EQ(foundTerritories.size(), 42);
}

TEST(DeckLoaderTests, DrawingPastEndCyclesDeck)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    const Card* firstCard = &deck.getNextCard();

    for (int i = 1; i < 46; i++)
    {
        deck.getNextCard();
    }

    const Card* cycledCard = &deck.getNextCard();

    EXPECT_EQ(firstCard, cycledCard);
}