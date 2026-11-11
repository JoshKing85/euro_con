#pragma once

#include "european_conquest/core/orders/CashSetOrder.h"
#include "european_conquest/core/orders/FortifyOrder.h"
#include "european_conquest/core/orders/ReinforceOrder.h"

#include <vector>

namespace european_conquest {

class GameStateManager;
class Player;

/**
 * Manages reinforcement, fortification and card-set orders.
 * Calculates reinforcement allocations and supports order creation,
 * adjustment, execution and undo through GameStateManager.
 */
class TroopManager {

private:
  std::vector<ReinforceOrder> reinforceOrders;
  std::vector<FortifyOrder> fortifyOrders;
  std::vector<CashSetOrder> cashSetOrders;

public:
  TroopManager();

  // REINFORCEMENT CALCULATION

  int calculateReinforcements(const Player &player);

  // CREATE ORDERS

  void createReinforceOrder(int playerID, TerritoryID territoryID,
                            int reinforceTroopCount);

  void createFortifyOrder(int playerID, TerritoryID fromTerritory,
                          TerritoryID toTerritory, int fortifyTroopCount);

  void createCashSetOrder(int playerID, SetType setType,
                          std::vector<Card> cards);

  // EXECUTE ORDERS

  void executeReinforceOrder(GameStateManager &gameStateManager);

  void executeFortifyOrder(GameStateManager &gameStateManager);

  int executeCashSetOrder(const Player &player,
                          GameStateManager &gameStateManager);

  // UNDO ORDERS

  void undoReinforceOrder();
  void undoFortifyOrder();
  void undoCashSetOrder();

  void clearOrders();

  // UPDATE DURING REINFORCE

  void updateReinforceOrder(bool add);
  void updateFortifyOrder(bool add);

  // GETTERS

  const std::vector<ReinforceOrder> &getReinforceOrders() const;
  const std::vector<FortifyOrder> &getFortifyOrders() const;
  const std::vector<CashSetOrder> &getCashSetOrders() const;

  const ReinforceOrder &getLastReinforceOrder() const;
  const FortifyOrder &getLastFortifyOrder() const;
  const CashSetOrder &getLastCashSetOrder() const;
};

} // namespace european_conquest