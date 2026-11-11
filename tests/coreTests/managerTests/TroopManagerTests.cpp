#include <gtest/gtest.h>

#include "european_conquest/core/managers/GameStateManager.h"
#include "european_conquest/core/managers/TroopManager.h"

#include "european_conquest/core/orders/CashSetOrder.h"
#include "european_conquest/core/orders/FortifyOrder.h"
#include "european_conquest/core/orders/ReinforceOrder.h"

#include "european_conquest/entities/Card.h"
#include "european_conquest/entities/Player.h"
#include "european_conquest/entities/Territory.h"

#include "european_conquest/world/Map.h"

#include <vector>

using namespace european_conquest;
// Constructor / Initial State Tests

TEST(TroopManagerTests, StartsWithEmptyOrderHistories)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    EXPECT_TRUE(
        troopManager.getReinforceOrders().empty()
    );

    EXPECT_TRUE(
        troopManager.getFortifyOrders().empty()
    );

    EXPECT_TRUE(
        troopManager.getCashSetOrders().empty()
    );
}
// Reinforce Order Creation Tests

TEST(TroopManagerTests, CreatesReinforceOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        5
    );

    ASSERT_EQ(
        troopManager.getReinforceOrders().size(),
        1
    );

    const ReinforceOrder& order =
        troopManager.getLastReinforceOrder();

    EXPECT_EQ(order.getPlayerID(), 0);

    EXPECT_EQ(
        order.getTerritoryID(),
        TerritoryID::England
    );

    EXPECT_EQ(
        order.getReinforceTroopCount(),
        5
    );

    EXPECT_FALSE(order.isCompleted());
}
// Reinforce Execution Tests

TEST(TroopManagerTests, ExecuteReinforceOrderAddsTroopsToTerritory)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    england.addTroops(3);

    map.addTerritory(england);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        5
    );

    troopManager.executeReinforceOrder(gameStateManager);

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        8
    );
}

TEST(TroopManagerTests, ExecuteReinforceOrderMarksOrderCompleted)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    map.addTerritory(england);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        5
    );

    troopManager.executeReinforceOrder(gameStateManager);

    EXPECT_TRUE(
        troopManager
        .getLastReinforceOrder()
        .isCompleted()
    );
}
// Reinforce Undo Tests

TEST(TroopManagerTests, UndoReinforceOrderRemovesLatestPendingOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        3
    );

    troopManager.undoReinforceOrder();

    EXPECT_TRUE(
        troopManager.getReinforceOrders().empty()
    );
}

TEST(TroopManagerTests, UndoReinforceOrderLeavesEarlierOrdersIntact)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Scotland,
        4
    );

    troopManager.undoReinforceOrder();

    ASSERT_EQ(
        troopManager.getReinforceOrders().size(),
        1
    );

    EXPECT_EQ(
        troopManager
        .getLastReinforceOrder()
        .getTerritoryID(),
        TerritoryID::England
    );
}
// Fortify Order Creation Tests

TEST(TroopManagerTests, CreatesFortifyOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        4
    );

    ASSERT_EQ(
        troopManager.getFortifyOrders().size(),
        1
    );

    const FortifyOrder& order =
        troopManager.getLastFortifyOrder();

    EXPECT_EQ(order.getPlayerID(), 0);

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::England
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::Scotland
    );

    EXPECT_EQ(
        order.getFortifyTroopCount(),
        4
    );

    EXPECT_FALSE(order.isCompleted());
}
// Fortify Execution Tests

TEST(TroopManagerTests, ExecuteFortifyOrderMovesTroopsBetweenTerritories)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {}
    );

    england.addTroops(10);
    scotland.addTroops(2);

    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        4
    );

    troopManager.executeFortifyOrder(gameStateManager);

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        6
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Scotland
        ).getTroopCount(),
        6
    );
}

TEST(TroopManagerTests, ExecuteFortifyOrderDoesNotChangeCombinedTroopCount)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {}
    );

    england.addTroops(10);
    scotland.addTroops(2);

    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    const int troopsBefore =
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount()
        +
        map.getTerritory(
            TerritoryID::Scotland
        ).getTroopCount();

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        4
    );

    troopManager.executeFortifyOrder(gameStateManager);

    const int troopsAfter =
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount()
        +
        map.getTerritory(
            TerritoryID::Scotland
        ).getTroopCount();

    EXPECT_EQ(
        troopsAfter,
        troopsBefore
    );
}

TEST(TroopManagerTests, ExecuteFortifyOrderMarksOrderCompleted)
{
    Map map;

    Territory england(
        TerritoryID::England,
        RegionID::BritishIsles,
        {}
    );

    Territory scotland(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {}
    );

    england.addTroops(5);

    map.addTerritory(england);
    map.addTerritory(scotland);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        2
    );

    troopManager.executeFortifyOrder(gameStateManager);

    EXPECT_TRUE(
        troopManager
        .getLastFortifyOrder()
        .isCompleted()
    );
}
// Fortify Undo Tests

TEST(TroopManagerTests, UndoFortifyOrderRemovesLatestPendingOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    troopManager.undoFortifyOrder();

    EXPECT_TRUE(
        troopManager.getFortifyOrders().empty()
    );
}
// Cash Set Creation Tests

TEST(TroopManagerTests, CreatesCashSetOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> cards
    {
        Card(
            CardType::Infantry,
            TerritoryID::England,
            RegionID::BritishIsles
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Prussia,
            RegionID::WesternEurope
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Bohemia,
            RegionID::AustrianEmpire
        )
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        cards
    );

    ASSERT_EQ(
        troopManager.getCashSetOrders().size(),
        1
    );

    const CashSetOrder& order =
        troopManager.getLastCashSetOrder();

    EXPECT_EQ(order.getPlayerID(), 0);

    EXPECT_EQ(
        order.getCards().size(),
        3
    );

    EXPECT_FALSE(order.isCompleted());
}
// Cash Set Execution Tests

TEST(TroopManagerTests, ExecuteCashSetOrderRemovesCashedCardsFromPlayer)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> playerCards
    {
        Card(
            CardType::Infantry,
            TerritoryID::England,
            RegionID::BritishIsles
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Prussia,
            RegionID::WesternEurope
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Bohemia,
            RegionID::AustrianEmpire
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Denmark,
            RegionID::RussianEmpire
        )
    };

    players[0].setPlayerSet(playerCards);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> cardsToCash
    {
        playerCards[0],
        playerCards[1],
        playerCards[2]
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        cardsToCash
    );

    troopManager.executeCashSetOrder(
        players[0],
        gameStateManager);

    const std::vector<Card>& remainingCards =
        players[0].getPlayerSet();

    ASSERT_EQ(
        remainingCards.size(),
        1
    );

    EXPECT_EQ(
        remainingCards[0].getCardType(),
        CardType::Cavalry
    );

    EXPECT_EQ(
        remainingCards[0].getTerritoryID(),
        TerritoryID::Denmark
    );
}


TEST(TroopManagerTests, ExecuteCashSetOrderReturnsSetValue)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> cards
    {
        Card(
            CardType::Cavalry,
            TerritoryID::England,
            RegionID::BritishIsles
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Prussia,
            RegionID::WesternEurope
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Bohemia,
            RegionID::AustrianEmpire
        )
    };

    players[0].setPlayerSet(cards);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createCashSetOrder(
        0,
        SetType::CavalrySet,
        cards
    );

    const int expectedValue =
        troopManager
        .getLastCashSetOrder()
        .getSetValue();

    const int returnedValue =
        troopManager.executeCashSetOrder(
            players[0],
            gameStateManager);

    EXPECT_EQ(
        returnedValue,
        expectedValue
    );
}

TEST(TroopManagerTests, ExecuteCashSetOrderMarksOrderCompleted)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> cards
    {
        Card(
            CardType::Artillery,
            TerritoryID::England,
            RegionID::BritishIsles
        ),
        Card(
            CardType::Artillery,
            TerritoryID::Prussia,
            RegionID::WesternEurope
        ),
        Card(
            CardType::Artillery,
            TerritoryID::Bohemia,
            RegionID::AustrianEmpire
        )
    };

    players[0].setPlayerSet(cards);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createCashSetOrder(
        0,
        SetType::ArtillerySet,
        cards
    );

    troopManager.executeCashSetOrder(
        players[0],
        gameStateManager);

    EXPECT_TRUE(
        troopManager
        .getLastCashSetOrder()
        .isCompleted()
    );
}
// Cash Set Undo Tests

TEST(TroopManagerTests, UndoCashSetOrderRemovesLatestPendingOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> cards
    {
        Card(CardType::Wild),
        Card(CardType::Wild),
        Card(CardType::Wild)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::MixedSet,
        cards
    );

    troopManager.undoCashSetOrder();

    EXPECT_TRUE(
        troopManager.getCashSetOrders().empty()
    );
}
// History Tests

TEST(TroopManagerTests, OrderGettersReturnCompleteHistories)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Scotland,
        4
    );

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        2
    );

    std::vector<Card> cards
    {
        Card(CardType::Wild),
        Card(CardType::Wild),
        Card(CardType::Wild)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::MixedSet,
        cards
    );

    EXPECT_EQ(
        troopManager.getReinforceOrders().size(),
        2
    );

    EXPECT_EQ(
        troopManager.getFortifyOrders().size(),
        1
    );

    EXPECT_EQ(
        troopManager.getCashSetOrders().size(),
        1
    );
}
// Getter Tests

TEST(TroopManagerTests, GetReinforceOrdersReturnsCompleteHistory)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Scotland,
        5
    );

    const std::vector<ReinforceOrder>& orders =
        troopManager.getReinforceOrders();

    ASSERT_EQ(
        orders.size(),
        2
    );

    EXPECT_EQ(
        orders[0].getTerritoryID(),
        TerritoryID::England
    );

    EXPECT_EQ(
        orders[1].getTerritoryID(),
        TerritoryID::Scotland
    );
}

TEST(TroopManagerTests, GetFortifyOrdersReturnsCompleteHistory)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        2
    );

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Scotland,
        TerritoryID::France,
        3
    );

    const std::vector<FortifyOrder>& orders =
        troopManager.getFortifyOrders();

    ASSERT_EQ(
        orders.size(),
        2
    );

    EXPECT_EQ(
        orders[0].getFromTerritory(),
        TerritoryID::England
    );

    EXPECT_EQ(
        orders[1].getFromTerritory(),
        TerritoryID::Scotland
    );
}

TEST(TroopManagerTests, GetCashSetOrdersReturnsCompleteHistory)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> firstSet
    {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    std::vector<Card> secondSet
    {
        Card(CardType::Cavalry),
        Card(CardType::Cavalry),
        Card(CardType::Cavalry)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        firstSet
    );

    troopManager.createCashSetOrder(
        0,
        SetType::CavalrySet,
        secondSet
    );

    const std::vector<CashSetOrder>& orders =
        troopManager.getCashSetOrders();

    ASSERT_EQ(
        orders.size(),
        2
    );

    EXPECT_EQ(
        orders[0].getCards().size(),
        3
    );

    EXPECT_EQ(
        orders[1].getCards().size(),
        3
    );
}

TEST(TroopManagerTests, GetLastReinforceOrderReturnsNewestOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::England,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::France,
        6
    );

    const ReinforceOrder& order =
        troopManager.getLastReinforceOrder();

    EXPECT_EQ(
        order.getTerritoryID(),
        TerritoryID::France
    );

    EXPECT_EQ(
        order.getReinforceTroopCount(),
        6
    );
}

TEST(TroopManagerTests, GetLastFortifyOrderReturnsNewestOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        2
    );

    troopManager.createFortifyOrder(
        0,
        TerritoryID::France,
        TerritoryID::Netherlands,
        4
    );

    const FortifyOrder& order =
        troopManager.getLastFortifyOrder();

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::France
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::Netherlands
    );

    EXPECT_EQ(
        order.getFortifyTroopCount(),
        4
    );
}

TEST(TroopManagerTests, GetLastCashSetOrderReturnsNewestOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> firstSet
    {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    std::vector<Card> secondSet
    {
        Card(CardType::Artillery),
        Card(CardType::Artillery),
        Card(CardType::Artillery)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        firstSet
    );

    troopManager.createCashSetOrder(
        0,
        SetType::ArtillerySet,
        secondSet
    );

    const CashSetOrder& order =
        troopManager.getLastCashSetOrder();

    ASSERT_EQ(
        order.getCards().size(),
        3
    );

    EXPECT_EQ(
        order.getCards()[0].getCardType(),
        CardType::Artillery
    );
}