#pragma once

#include "european_conquest/core/orders/Order.h"
#include "european_conquest/enums.h"

namespace european_conquest {

/** Stores troop losses and the outcome of a resolved attack. */
struct AttackResult {
  int attackerLosses = 0;
  int defenderLosses = 0;

  int attackingTroopCount = 0;
  int defendingTroopCount = 0;

  AttackOutcome attackOutcome = AttackOutcome::None;
};

/** Represents an attack from one territory to another, including its result. */
class AttackOrder : public Order {
private:
  TerritoryID attackingFrom;
  TerritoryID attackingTo;

  int attackingTroopCount;
  int defendingTroopCount;

  AttackResult result;

public:
  AttackOrder(int playerID, TerritoryID attackingFrom, TerritoryID attackingTo,
              int attackingTroopCount, int defendingTroopCount);

  TerritoryID getAttackingFrom() const;
  TerritoryID getAttackingTo() const;

  int getAttackingTroopCount() const;
  int getDefendingTroopCount() const;

  const AttackResult &getResult() const;

  void setResult(const AttackResult &result);
};

} // namespace european_conquest