#pragma once

#include "european_conquest/core/orders/Order.h"
#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {

/** Stores attacker and defender dice for a combat round. */
class RollDiceOrder : public Order {
private:
  int numberAttackerDice;
  int numberDefenderDice;

  std::vector<int> attackingDice;
  std::vector<int> defendingDice;

  std::vector<int> generateDice(int numberOfDice);

public:
  RollDiceOrder(int playerID, int numberAttackerDice, int numberDefenderDice);

  RollDiceOrder(int playerID, const std::vector<int> &attackingDice,
                const std::vector<int> &defendingDice);

  void updateAttackerDice(int numberOfDice);

  void execute();

  const std::vector<int> &getAttackingDice() const;
  const std::vector<int> &getDefendingDice() const;
};

} // namespace european_conquest