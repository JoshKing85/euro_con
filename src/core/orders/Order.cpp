#include "european_conquest/core/orders/Order.h"

namespace european_conquest {

    // CONSTRUCTOR

    Order::Order(int playerID, OrderType orderType)
        : playerID(playerID),
        orderType(orderType)
    {
    }

    // ACCESSORS

    int Order::getPlayerID() const
    {
        return playerID;
    }

    OrderType Order::getOrderType() const
    {
        return orderType;
    }

    bool Order::isCompleted() const
    {
        return completed;
    }
    // COMPLETION STATE

    void Order::complete()
    {
        markCompleted();
    }
    void Order::markCompleted()
    {
        completed = true;
    }

}