#include "european_conquest/core/orders/RollDiceOrder.h"

#include <algorithm>
#include <functional>
#include <random>

namespace european_conquest {

    // CONSTRUCTORS

    RollDiceOrder::RollDiceOrder(
        int playerID,
        int numberAttackerDice,
        int numberDefenderDice
    )
        : Order(playerID, OrderType::RollDice),
        numberAttackerDice(numberAttackerDice),
        numberDefenderDice(numberDefenderDice)
    {
    }

    RollDiceOrder::RollDiceOrder(
        int playerID,
        const std::vector<int>& attackingDice,
        const std::vector<int>& defendingDice
    )
        : Order(playerID, OrderType::RollDice),
        numberAttackerDice(static_cast<int>(attackingDice.size())),
        numberDefenderDice(static_cast<int>(defendingDice.size())),
        attackingDice(attackingDice),
        defendingDice(defendingDice)
    {
        // Sort supplied dice highest-first for paired combat comparisons.
        std::sort(
            this->attackingDice.begin(),
            this->attackingDice.end(),
            std::greater<int>()
        );

        std::sort(
            this->defendingDice.begin(),
            this->defendingDice.end(),
            std::greater<int>()
        );
    }

    // DICE CONFIGURATION

    void RollDiceOrder::updateAttackerDice(
        int numberOfDice
    )
    {
        numberAttackerDice =
            numberOfDice;
    }

    // DICE EXECUTION

    void RollDiceOrder::execute()
    {
        attackingDice =
            generateDice(
                numberAttackerDice
            );

        defendingDice =
            generateDice(
                numberDefenderDice
            );
    }

    // RANDOM DICE GENERATION

    std::vector<int> RollDiceOrder::generateDice(
        int numberOfDice
    )
    {
        std::vector<int> dice;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 6);

        for (int i = 0;
            i < numberOfDice;
            ++i)
        {
            dice.push_back(
                dist(gen)
            );
        }

        // The attack resolver compares the highest dice first.
        std::sort(
            dice.begin(),
            dice.end(),
            std::greater<int>()
        );

        return dice;
    }

    // GETTERS

    const std::vector<int>&
        RollDiceOrder::getAttackingDice() const
    {
        return attackingDice;
    }

    const std::vector<int>&
        RollDiceOrder::getDefendingDice() const
    {
        return defendingDice;
    }

} // namespace european_conquest