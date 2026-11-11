#include <gtest/gtest.h>

#include "european_conquest/core/managers/AttackManager.h"
#include "european_conquest/core/managers/GameStateManager.h"
#include "european_conquest/entities/Player.h"
#include "european_conquest/entities/Territory.h"
#include "european_conquest/world/Region.h"
#include "european_conquest/world/Map.h"

#include <algorithm>
#include <vector>

using namespace european_conquest;

namespace {

    bool containsTerritory(
        const Player& player,
        TerritoryID territoryID
    )
    {
        const std::vector<TerritoryID>& territories =
            player.getTerritoriesHeld();

        return std::find(
            territories.begin(),
            territories.end(),
            territoryID
        ) != territories.end();
    }

    class AttackManagerTests : public ::testing::Test {
    protected:
        Map map;
        std::vector<Player> players;
        GameStateManager gameStateManager;
        AttackManager attackManager;

        AttackManagerTests()
            : gameStateManager(map, players)
        {
        }

        void SetUp() override
        {
            Region britishIsles(
                RegionID::BritishIsles,
                5,
                {
                    TerritoryID::England,
                    TerritoryID::Scotland,
                    TerritoryID::France
                },
                {
                    TerritoryID::England,
                    TerritoryID::France
                }
            );

            Territory england(
                TerritoryID::England,
                RegionID::BritishIsles,
                {
                    TerritoryID::Scotland
                }
            );

            Territory scotland(
                TerritoryID::Scotland,
                RegionID::BritishIsles,
                {
                    TerritoryID::England,
                    TerritoryID::France
                }
            );

            Territory wales(
                TerritoryID::France,
                RegionID::BritishIsles,
                {
                    TerritoryID::Scotland
                }
            );

            england.setOwner(0);
            scotland.setOwner(1);
            wales.setOwner(1);

            england.addTroops(10);
            scotland.addTroops(5);
            wales.addTroops(5);

            map.addRegion(britishIsles);
            map.addTerritory(england);
            map.addTerritory(scotland);
            map.addTerritory(wales);

            players.emplace_back(0);
            players.emplace_back(1);

            players[0].addTerritory(
                TerritoryID::England
            );

            players[1].addTerritory(
                TerritoryID::Scotland
            );

            players[1].addTerritory(
                TerritoryID::France
            );
        }

        void createDefaultAttack()
        {
            attackManager.createAttack(
                0,
                TerritoryID::England,
                TerritoryID::Scotland,
                10,
                5
            );
        }

        void createDefaultRoll()
        {
            attackManager.createRollDiceOrder(
                { 6, 5, 4 },
                { 3, 2 }
            );
        }
    };

} // namespace
// Construction and Creation Tests

TEST_F(AttackManagerTests, ConstructorCreatesEmptyManager)
{
    EXPECT_TRUE(
        attackManager.getAttackOrders().empty()
    );

    EXPECT_TRUE(
        attackManager.getRollDiceOrders().empty()
    );

    EXPECT_TRUE(
        attackManager.getMoveTroopsOrders().empty()
    );
}

TEST_F(AttackManagerTests, CreateAttackCreatesPendingAttackOrder)
{
    // Arrange / Act
    createDefaultAttack();

    // Assert
    ASSERT_EQ(
        attackManager.getAttackOrders().size(),
        1
    );

    EXPECT_FALSE(
        attackManager.getAttackOrders()[0].isCompleted()
    );
}

TEST_F(AttackManagerTests, CreatedAttackContainsCorrectValues)
{
    // Arrange / Act
    createDefaultAttack();

    // Assert
    const AttackOrder& attackOrder =
        attackManager.getAttackOrders()[0];

    EXPECT_EQ(
        attackOrder.getPlayerID(),
        0
    );

    EXPECT_EQ(
        attackOrder.getOrderType(),
        OrderType::Attack
    );

    EXPECT_EQ(
        attackOrder.getAttackingFrom(),
        TerritoryID::England
    );

    EXPECT_EQ(
        attackOrder.getAttackingTo(),
        TerritoryID::Scotland
    );

    EXPECT_EQ(
        attackOrder.getAttackingTroopCount(),
        10
    );

    EXPECT_EQ(
        attackOrder.getDefendingTroopCount(),
        5
    );
}

TEST_F(AttackManagerTests, CreateRollDiceOrderCreatesRollDiceOrder)
{
    // Arrange
    createDefaultAttack();

    // Act
    attackManager.createRollDiceOrder(
        { 6, 4, 2 },
        { 5, 3 }
    );

    // Assert
    const std::vector<RollDiceOrder>& rolls =
        attackManager.getRollDiceOrders();

    ASSERT_EQ(
        rolls.size(),
        1
    );

    EXPECT_EQ(
        rolls[0].getPlayerID(),
        0
    );

    EXPECT_EQ(
        rolls[0].getOrderType(),
        OrderType::RollDice
    );
}

TEST_F(AttackManagerTests, MultipleCompletedAttacksRemainInCreationOrder)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6, 5, 4 },
        { 3, 2 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::France,
        10,
        5
    );

    attackManager.createRollDiceOrder(
        { 1 },
        { 6 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    const std::vector<AttackOrder>& attacks =
        attackManager.getAttackOrders();

    ASSERT_EQ(
        attacks.size(),
        2
    );

    EXPECT_EQ(
        attacks[0].getAttackingTo(),
        TerritoryID::Scotland
    );

    EXPECT_EQ(
        attacks[1].getAttackingTo(),
        TerritoryID::France
    );

    EXPECT_TRUE(
        attacks[0].isCompleted()
    );

    EXPECT_TRUE(
        attacks[1].isCompleted()
    );
}
// Undo Tests

TEST_F(AttackManagerTests, UndoAttackRemovesLatestPendingAttack)
{
    // Arrange
    createDefaultAttack();

    // Act
    attackManager.undoAttack();

    // Assert
    EXPECT_TRUE(
        attackManager.getAttackOrders().empty()
    );
}

TEST_F(AttackManagerTests, UndoAttackLeavesEarlierOrdersIntact)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6 },
        { 1 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::France,
        10,
        5
    );

    // Act
    attackManager.undoAttack();

    // Assert
    const std::vector<AttackOrder>& attacks =
        attackManager.getAttackOrders();

    ASSERT_EQ(
        attacks.size(),
        1
    );

    EXPECT_EQ(
        attacks[0].getAttackingTo(),
        TerritoryID::Scotland
    );

    EXPECT_TRUE(
        attacks[0].isCompleted()
    );
}

TEST_F(AttackManagerTests, UndoRollDiceOrderRemovesLatestRollDiceOrder)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6, 5, 4 },
        { 3, 2 }
    );

    // Act
    attackManager.undoRollDiceOrder();

    // Assert
    EXPECT_TRUE(
        attackManager.getRollDiceOrders().empty()
    );
}

TEST_F(AttackManagerTests, UndoMoveTroopsOrderRemovesLatestMoveTroopsOrder)
{
    // Arrange
    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    // Act
    attackManager.undoMoveTroopsOrder();

    // Assert
    EXPECT_TRUE(
        attackManager.getMoveTroopsOrders().empty()
    );
}
// Attack Execution Tests

TEST_F(AttackManagerTests, AttackOrderBecomesCompletedAfterExecution)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6 },
        { 1 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    EXPECT_TRUE(
        attackManager.getLastAttackOrder().isCompleted()
    );
}

TEST_F(AttackManagerTests, AttackResultMatchesStoredDice)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 2, 6, 1 },
        { 2, 5 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    const RollDiceOrder& roll =
        attackManager.getLastRollDiceOrder();

    const AttackResult& result =
        attackManager.getLastAttackOrder().getResult();

    ASSERT_EQ(
        roll.getAttackingDice(),
        (std::vector<int>{6, 2, 1})
    );

    ASSERT_EQ(
        roll.getDefendingDice(),
        (std::vector<int>{5, 2})
    );

    EXPECT_EQ(
        result.attackerLosses,
        1
    );

    EXPECT_EQ(
        result.defenderLosses,
        1
    );

    EXPECT_EQ(
        result.attackingTroopCount,
        9
    );

    EXPECT_EQ(
        result.defendingTroopCount,
        4
    );

    EXPECT_EQ(
        result.attackOutcome,
        AttackOutcome::Draw
    );
}

TEST_F(AttackManagerTests, DefenderWinsTiedDiceComparison)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6 },
        { 6 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    const AttackResult& result =
        attackManager.getLastAttackOrder().getResult();

    EXPECT_EQ(
        result.attackerLosses,
        1
    );

    EXPECT_EQ(
        result.defenderLosses,
        0
    );

    EXPECT_EQ(
        result.attackOutcome,
        AttackOutcome::DefenderGain
    );
}

TEST_F(AttackManagerTests, AttackerLossesAreRemovedFromAttackingTerritory)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 4, 2 },
        { 6, 1 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        9
    );
}

TEST_F(AttackManagerTests, DefenderLossesAreRemovedFromDefendingTerritory)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6, 5 },
        { 4, 3 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Scotland
        ).getTroopCount(),
        3
    );
}
// Capture Tests

TEST_F(AttackManagerTests, DefenderTerritoryIsCapturedWhenTroopsReachZero)
{
    // Arrange
    map.getTerritory(
        TerritoryID::Scotland
    ).removeTroops(4);

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        10,
        1
    );

    attackManager.createRollDiceOrder(
        { 6 },
        { 1 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    const AttackResult& result =
        attackManager.getLastAttackOrder().getResult();

    EXPECT_EQ(
        result.defendingTroopCount,
        0
    );

    EXPECT_EQ(
        result.attackOutcome,
        AttackOutcome::Captured
    );
}

TEST_F(AttackManagerTests, CaptureTransfersTerritoryOwnerThroughGameStateManager)
{
    // Arrange
    map.getTerritory(
        TerritoryID::Scotland
    ).removeTroops(4);

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        10,
        1
    );

    attackManager.createRollDiceOrder(
        { 6 },
        { 1 }
    );

    // Act
    attackManager.executeAttackOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Scotland
        ).getOwnerID(),
        0
    );

    EXPECT_TRUE(
        containsTerritory(
            players[0],
            TerritoryID::Scotland
        )
    );

    EXPECT_FALSE(
        containsTerritory(
            players[1],
            TerritoryID::Scotland
        )
    );
}
// Latest Order Getter Tests

TEST_F(AttackManagerTests, GetLastAttackOrderReturnsNewestAttack)
{
    // Arrange
    createDefaultAttack();

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::France,
        10,
        5
    );

    // Act
    const AttackOrder& latestAttack =
        attackManager.getLastAttackOrder();

    // Assert
    EXPECT_EQ(
        latestAttack.getAttackingTo(),
        TerritoryID::France
    );
}

TEST_F(AttackManagerTests, GetLastRollDiceOrderReturnsNewestRoll)
{
    // Arrange
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6 },
        { 1 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::France,
        10,
        5
    );

    attackManager.createRollDiceOrder(
        { 2, 1 },
        { 6, 5 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    // Act
    const RollDiceOrder& latestRoll =
        attackManager.getLastRollDiceOrder();

    // Assert
    EXPECT_EQ(
        latestRoll.getAttackingDice(),
        (std::vector<int>{2, 1})
    );

    EXPECT_EQ(
        latestRoll.getDefendingDice(),
        (std::vector<int>{6, 5})
    );
}

TEST_F(AttackManagerTests, GetLastMoveTroopsOrderReturnsNewestMove)
{
    // Arrange
    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        2
    );

    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::France,
        3
    );

    // Act
    const MoveTroopsOrder& latestMove =
        attackManager.getLastMoveTroopsOrder();

    // Assert
    EXPECT_EQ(
        latestMove.getToTerritory(),
        TerritoryID::France
    );

    EXPECT_EQ(
        latestMove.getTroopsMoved(),
        3
    );
}
// Troop Movement Tests

TEST_F(AttackManagerTests, CreateMoveTroopsOrderCreatesMoveTroopsOrder)
{
    // Arrange / Act
    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    // Assert
    const std::vector<MoveTroopsOrder>& movements =
        attackManager.getMoveTroopsOrders();

    ASSERT_EQ(
        movements.size(),
        1
    );

    EXPECT_EQ(
        movements[0].getPlayerID(),
        0
    );

    EXPECT_EQ(
        movements[0].getOrderType(),
        OrderType::MoveTroops
    );

    EXPECT_EQ(
        movements[0].getFromTerritory(),
        TerritoryID::England
    );

    EXPECT_EQ(
        movements[0].getToTerritory(),
        TerritoryID::Scotland
    );

    EXPECT_EQ(
        movements[0].getTroopsMoved(),
        3
    );
}

TEST_F(AttackManagerTests, CreatingMoveTroopsOrderDoesNotMoveTroops)
{
    // Arrange / Act
    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    // Assert
    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        10
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Scotland
        ).getTroopCount(),
        5
    );
}

TEST_F(AttackManagerTests, ExecuteMoveTroopsOrderRemovesTroopsFromSource)
{
    // Arrange
    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    // Act
    attackManager.executeMoveTroopsOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::England
        ).getTroopCount(),
        7
    );
}

TEST_F(AttackManagerTests, ExecuteMoveTroopsOrderAddsTroopsToDestination)
{
    // Arrange
    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    // Act
    attackManager.executeMoveTroopsOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Scotland
        ).getTroopCount(),
        8
    );
}

TEST_F(AttackManagerTests, MoveTroopsDoesNotChangePlayerTotalTroopCount)
{
    // Arrange
    players[0].addTroops(10);

    const int originalTroopCount =
        players[0].getTroopCount();

    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        3
    );

    // Act
    attackManager.executeMoveTroopsOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        players[0].getTroopCount(),
        originalTroopCount
    );
}
// History Getter Tests

TEST_F(AttackManagerTests, VectorGettersReturnCompleteOrderHistories)
{
    // Arrange / Act
    createDefaultAttack();

    attackManager.createRollDiceOrder(
        { 6 },
        { 1 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    attackManager.createAttack(
        0,
        TerritoryID::England,
        TerritoryID::France,
        10,
        5
    );

    attackManager.createRollDiceOrder(
        { 1 },
        { 6 }
    );

    attackManager.executeAttackOrder(gameStateManager);

    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::Scotland,
        1
    );

    attackManager.executeMoveTroopsOrder(gameStateManager);

    attackManager.createMoveTroopsOrder(
        0,
        TerritoryID::England,
        TerritoryID::France,
        1
    );

    attackManager.executeMoveTroopsOrder(gameStateManager);

    // Assert
    EXPECT_EQ(
        attackManager.getAttackOrders().size(),
        2
    );

    EXPECT_EQ(
        attackManager.getRollDiceOrders().size(),
        2
    );

    EXPECT_EQ(
        attackManager.getMoveTroopsOrders().size(),
        2
    );
}