#pragma once

#include "european_conquest/core/orders/Order.h"
#include "european_conquest/entities/Card.h"
#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {

/** Represents a player exchanging a card set for reinforcement troops. */
class CashSetOrder : public Order {
private:
  SetType setType;
  std::vector<Card> cards;
  int setValue = 0;

public:
  CashSetOrder(int playerID, SetType setType, std::vector<Card> cards);

  const std::vector<Card> &getCards() const;
  int getSetValue() const;


private:
 static int calculateSetValue(SetType setType);
};

} // namespace european_conquest