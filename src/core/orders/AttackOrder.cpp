#include "european_conquest/core/orders/AttackOrder.h"

namespace european_conquest {

// CONSTRUCTOR

AttackOrder::AttackOrder(
    int playerID,
    TerritoryID attackingFrom,
    TerritoryID attackingTo,
    int attackingTroopCount,
    int defendingTroopCount
)
    : Order(playerID, OrderType::Attack),
      attackingFrom(attackingFrom),
      attackingTo(attackingTo),
      attackingTroopCount(attackingTroopCount),
      defendingTroopCount(defendingTroopCount)
{
}

// GETTERS

TerritoryID AttackOrder::getAttackingFrom() const
{
    return attackingFrom;
}

TerritoryID AttackOrder::getAttackingTo() const
{
    return attackingTo;
}

int AttackOrder::getAttackingTroopCount() const
{
    return attackingTroopCount;
}

int AttackOrder::getDefendingTroopCount() const
{
    return defendingTroopCount;
}

const AttackResult& AttackOrder::getResult() const
{
    return result;
}

// RESULT

void AttackOrder::setResult(const AttackResult& result)
{
    this->result = result;
    markCompleted();
}

}