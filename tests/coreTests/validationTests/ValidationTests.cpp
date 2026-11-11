#include <gtest/gtest.h>

#include "european_conquest/core/validation/ValidateTerritorySelection.h"
#include "european_conquest/core/validation/ValidateAttackInput.h"
#include "european_conquest/core/validation/ValidateAttackSelection.h"
#include "european_conquest/core/validation/ValidateDiceInput.h"
#include "european_conquest/core/validation/ValidateTroopCountInput.h"
#include "european_conquest/core/validation/ValidateSetInput.h"
#include "european_conquest/core/validation/ValidateFortifyInput.h"

#include "european_conquest/entities/Card.h"
#include "european_conquest/entities/Territory.h"
#include "european_conquest/world/Map.h"



#include "european_conquest/enums.h"

#include <vector>

using namespace european_conquest;
// Territory Selection Validation Tests

TEST(ValidationTests, TerritorySelectionReturnsTrueWhenTerritoryIsOwned)
{
    const std::vector<TerritoryID> territoriesOwned = {
        TerritoryID::England,
        TerritoryID::Scotland,
        TerritoryID::France
    };

    EXPECT_TRUE(
        isValidTerritorySelection(
            TerritoryID::Scotland,
            territoriesOwned
        )
    );
}

TEST(ValidationTests, TerritorySelectionReturnsFalseWhenTerritoryIsNotOwned)
{
    const std::vector<TerritoryID> territoriesOwned = {
        TerritoryID::England,
        TerritoryID::Scotland,
        TerritoryID::France
    };

    EXPECT_FALSE(
        isValidTerritorySelection(
            TerritoryID::Prussia,
            territoriesOwned
        )
    );
}

TEST(ValidationTests, TerritorySelectionReturnsFalseWhenOwnedTerritoriesIsEmpty)
{
    const std::vector<TerritoryID> territoriesOwned;

    EXPECT_FALSE(
        isValidTerritorySelection(
            TerritoryID::England,
            territoriesOwned
        )
    );
}

TEST(ValidationTests, TerritorySelectionFindsTerritoryLaterInVector)
{
    const std::vector<TerritoryID> territoriesOwned = {
        TerritoryID::England,
        TerritoryID::Scotland,
        TerritoryID::France
    };

    EXPECT_TRUE(
        isValidTerritorySelection(
            TerritoryID::France,
            territoriesOwned
        )
    );
}
// Attack Input Validation Tests

TEST(ValidationTests, AttackInputReturnsTrueWhenTargetIsAdjacentAndEnoughTroops)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Scotland,
        TerritoryID::Spain
    };

    EXPECT_TRUE(
        isValidAttackInput(
            TerritoryID::Scotland,
            adjacentTerritories,
            3,
            0,
            1
        )
    );
}

TEST(ValidationTests, AttackInputReturnsTrueWithMinimumTwoTroops)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Scotland
    };

    EXPECT_TRUE(
        isValidAttackInput(
            TerritoryID::Scotland,
            adjacentTerritories,
            2,
            0,
            1
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenOnlyOneTroopAvailable)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Scotland
    };

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Scotland,
            adjacentTerritories,
            1,
            0,
            1
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenTargetIsNotAdjacent)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Scotland,
        TerritoryID::Spain
    };

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Prussia,
            adjacentTerritories,
            5,
            0,
            1
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenAdjacentTerritoriesIsEmpty)
{
    const std::vector<TerritoryID> adjacentTerritories;

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Scotland,
            adjacentTerritories,
            5,
            0,
            1
        )
    );
}

TEST(ValidationTests, AttackInputFindsTargetLaterInAdjacentVector)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Scotland,
        TerritoryID::Spain,
        TerritoryID::Finland
    };

    EXPECT_TRUE(
        isValidAttackInput(
            TerritoryID::Finland,
            adjacentTerritories,
            5,
            0,
            1
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenTargetHasSameOwner)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Scotland
    };

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Scotland,
            adjacentTerritories,
            3,
            0,
            0
        )
    );
}
// Attack Selection Validation Tests

TEST(ValidationTests, AttackSelectionReturnsTrueWhenEnemyIsAdjacent)
{
    Map map;

    Territory selectedTerritory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory adjacentTerritory(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    selectedTerritory.setOwner(0);
    adjacentTerritory.setOwner(1);

    selectedTerritory.addTroops(2);

    map.addTerritory(selectedTerritory);
    map.addTerritory(adjacentTerritory);

    EXPECT_TRUE(
        isValidAttackSelection(
            0,
            TerritoryID::England,
            map
        )
    );
}

TEST(ValidationTests, AttackSelectionReturnsFalseWhenLessThanTwoTroops)
{
    Map map;

    Territory selectedTerritory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory adjacentTerritory(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    selectedTerritory.setOwner(0);
    adjacentTerritory.setOwner(1);

    selectedTerritory.addTroops(1);

    map.addTerritory(selectedTerritory);
    map.addTerritory(adjacentTerritory);

    EXPECT_FALSE(
        isValidAttackSelection(
            0,
            TerritoryID::England,
            map
        )
    );
}

TEST(ValidationTests, AttackSelectionReturnsFalseWhenNoEnemyIsAdjacent)
{
    Map map;

    Territory selectedTerritory(
        TerritoryID::England,
        RegionID::BritishIsles,
        {
            TerritoryID::Scotland
        }
    );

    Territory adjacentTerritory(
        TerritoryID::Scotland,
        RegionID::BritishIsles,
        {
            TerritoryID::England
        }
    );

    selectedTerritory.setOwner(0);
    adjacentTerritory.setOwner(0);

    selectedTerritory.addTroops(2);

    map.addTerritory(selectedTerritory);
    map.addTerritory(adjacentTerritory);

    EXPECT_FALSE(
        isValidAttackSelection(
            0,
            TerritoryID::England,
            map
        )
    );
}
// Dice Input Validation Tests

TEST(ValidationTests, DiceInputAllowsOneDieWithTwoTroops)
{
    EXPECT_TRUE(
        isValidDiceInput(
            1,
            2
        )
    );
}

TEST(ValidationTests, DiceInputAllowsTwoDiceWithThreeTroops)
{
    EXPECT_TRUE(
        isValidDiceInput(
            2,
            3
        )
    );
}

TEST(ValidationTests, DiceInputAllowsThreeDiceWithFourTroops)
{
    EXPECT_TRUE(
        isValidDiceInput(
            3,
            4
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseWhenTooManyDiceForTroops)
{
    EXPECT_FALSE(
        isValidDiceInput(
            3,
            3
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseForZeroDice)
{
    EXPECT_FALSE(
        isValidDiceInput(
            0,
            5
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseForNegativeDice)
{
    EXPECT_FALSE(
        isValidDiceInput(
            -1,
            5
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseForMoreThanThreeDice)
{
    EXPECT_FALSE(
        isValidDiceInput(
            4,
            10
        )
    );
}
// Reinforce Input Validation Tests

TEST(ValidationTests, ReinforceInputReturnsTrueWhenReinforcingWithinTroopPool)
{
    EXPECT_TRUE(
        isTroopCountValid(
            3,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsTrueWhenUsingEntireTroopPool)
{
    EXPECT_TRUE(
        isTroopCountValid(
            5,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsFalseWhenExceedingTroopPool)
{
    EXPECT_FALSE(
        isTroopCountValid(
            6,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsFalseForZeroTroops)
{
    EXPECT_FALSE(
        isTroopCountValid(
            0,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsFalseForNegativeTroops)
{
    EXPECT_FALSE(
        isTroopCountValid(
            -1,
            5
        )
    );
}
// Set Validation Tests

TEST(ValidationTests, SetReturnsInfantrySetForThreeInfantryCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    EXPECT_EQ(
        validateSet(cards),
        SetType::InfantrySet
    );
}

TEST(ValidationTests, SetReturnsCavalrySetForThreeCavalryCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Cavalry),
        Card(CardType::Cavalry),
        Card(CardType::Cavalry)
    };

    EXPECT_EQ(
        validateSet(cards),
        SetType::CavalrySet
    );
}

TEST(ValidationTests, SetReturnsArtillerySetForThreeArtilleryCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Artillery),
        Card(CardType::Artillery),
        Card(CardType::Artillery)
    };

    EXPECT_EQ(
        validateSet(cards),
        SetType::ArtillerySet
    );
}

TEST(ValidationTests, SetReturnsMixedSet)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Cavalry),
        Card(CardType::Artillery)
    };

    EXPECT_EQ(
        validateSet(cards),
        SetType::MixedSet
    );
}

TEST(ValidationTests, SetReturnsInfantrySetWhenWildCompletesInfantrySet)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Wild)
    };

    EXPECT_EQ(
        validateSet(cards),
        SetType::InfantrySet
    );
}

TEST(ValidationTests, SetReturnsMixedSetWhenWildCompletesMixedSet)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Cavalry),
        Card(CardType::Wild)
    };

    EXPECT_EQ(
        validateSet(cards),
        SetType::MixedSet
    );
}

TEST(ValidationTests, SetReturnsNulloptForInvalidCombination)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Cavalry)
    };

    EXPECT_EQ(
        validateSet(cards),
        std::nullopt
    );
}

TEST(ValidationTests, SetReturnsNulloptWithFewerThanThreeCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    EXPECT_EQ(
        validateSet(cards),
        std::nullopt
    );
}

TEST(ValidationTests, SetReturnsNulloptWithMoreThanThreeCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    EXPECT_EQ(
        validateSet(cards),
        std::nullopt
    );
}
// Fortify Validation Tests

TEST(ValidationTests, FortifyReturnsTrueForDirectOwnedConnection)
{
    Map map;

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
            TerritoryID::England
        }
    );

    england.setOwner(0);
    scotland.setOwner(0);

    map.addTerritory(england);
    map.addTerritory(scotland);

    EXPECT_TRUE(
        isFortifyValid(
            map,
            TerritoryID::England,
            TerritoryID::Scotland,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsTrueForIndirectOwnedPath)
{
    Map map;

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
    scotland.setOwner(0);
    wales.setOwner(0);

    map.addTerritory(england);
    map.addTerritory(scotland);
    map.addTerritory(wales);

    EXPECT_TRUE(
        isFortifyValid(
            map,
            TerritoryID::England,
            TerritoryID::France,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsFalseWhenEnemyTerritoryBlocksPath)
{
    Map map;

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
    wales.setOwner(0);

    map.addTerritory(england);
    map.addTerritory(scotland);
    map.addTerritory(wales);

    EXPECT_FALSE(
        isFortifyValid(
            map,
            TerritoryID::England,
            TerritoryID::France,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsFalseWhenDestinationIsEnemyOwned)
{
    Map map;

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
            TerritoryID::England
        }
    );

    england.setOwner(0);
    scotland.setOwner(1);

    map.addTerritory(england);
    map.addTerritory(scotland);

    EXPECT_FALSE(
        isFortifyValid(
            map,
            TerritoryID::England,
            TerritoryID::Scotland,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsFalseWhenNoPathExists)
{
    Map map;

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
            TerritoryID::England
        }
    );

    Territory wales(
        TerritoryID::France,
        RegionID::BritishIsles,
        {}
    );

    england.setOwner(0);
    scotland.setOwner(0);
    wales.setOwner(0);

    map.addTerritory(england);
    map.addTerritory(scotland);
    map.addTerritory(wales);

    EXPECT_FALSE(
        isFortifyValid(
            map,
            TerritoryID::England,
            TerritoryID::France,
            0
        )
    );
}