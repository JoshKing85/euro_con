#pragma once

#include "european_conquest/core/orders/AttackOrder.h"
#include "european_conquest/core/orders/MoveTroopsOrder.h"
#include "european_conquest/core/orders/RollDiceOrder.h"
#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {

class GameStateManager;

/**
 * Manages attack, dice-roll and post-capture troop movement orders.
 * Coordinates combat resolution and delegates territory and troop state changes
 * to GameStateManager.
 */
class AttackManager {
private:
  std::vector<AttackOrder> attackOrders;
  std::vector<RollDiceOrder> rollDiceOrders;
  std::vector<MoveTroopsOrder> moveTroopsOrders;

  void resolveAttack(AttackOrder &currentAttack,
                     const RollDiceOrder &currentRoll,
                     GameStateManager &gameStateManager);

public:
  AttackManager();

  // ATTACK ORDER

  void createAttack(int playerID, TerritoryID fromTerritory,
                    TerritoryID toTerritory, int attackingTroopCount,
                    int defendingTroopCount);

  void undoAttack();

  // DICE-ROLL ORDER

  void createRollDiceOrder(int attackDiceCount);

  void createRollDiceOrder(const std::vector<int> &attackingDice,
                           const std::vector<int> &defendingDice);

  void undoRollDiceOrder();

  void executeAttackOrder(GameStateManager &gameStateManager);

  void updateRollDiceOrder(int diceCount);

  // POST-CAPTURE TROOP MOVEMENT

  void createMoveTroopsOrder(int playerID, TerritoryID fromTerritory,
                             TerritoryID toTerritory, int moveTroopCount);

  void updateMoveTroopsOrder(bool add);

  void undoMoveTroopsOrder();

  void executeMoveTroopsOrder(GameStateManager &gameStateManager);

  void clearOrders();

  // GETTERS

  const AttackOrder &getLastAttackOrder() const;
  const RollDiceOrder &getLastRollDiceOrder() const;
  const MoveTroopsOrder &getLastMoveTroopsOrder() const;

  const std::vector<AttackOrder> &getAttackOrders() const;
  const std::vector<RollDiceOrder> &getRollDiceOrders() const;
  const std::vector<MoveTroopsOrder> &getMoveTroopsOrders() const;
};

} // namespace european_conquest