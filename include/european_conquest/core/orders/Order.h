#pragma once

#include "european_conquest/enums.h"

namespace european_conquest {

/** Base class for player orders, tracking their type, owner and completion. */
class Order {
private:
  int playerID;
  OrderType orderType;
  bool completed = false;

public:
  Order(int playerID, OrderType orderType);
  virtual ~Order() = default;

  int getPlayerID() const;
  OrderType getOrderType() const;
  bool isCompleted() const;

  void complete();

protected:
  void markCompleted();
};

} // namespace european_conquest