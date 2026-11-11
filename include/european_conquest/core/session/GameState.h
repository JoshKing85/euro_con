#pragma once

#include "european_conquest/core/orders/AttackOrder.h"
#include "european_conquest/core/orders/FortifyOrder.h"
#include "european_conquest/core/orders/MoveTroopsOrder.h"
#include "european_conquest/core/orders/ReinforceOrder.h"
#include "european_conquest/core/orders/RollDiceOrder.h"

#include "european_conquest/entities/Card.h"
#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest {

/** Holds the active turn phase, player selections and pending order references.
 * Provides temporary turn state used by the interface and gameplay coordination. */
class GameState {
private:
  PhaseType phase = PhaseType::Loading;
  bool turnStarted = false;
  int playerTurnID = 0;

  int reinforcePool = 0;
  bool initReinforceComplete = false;

  TerritoryID toSelection = TerritoryID::None;
  TerritoryID fromSelection = TerritoryID::None;

  int attackerDice = 0;
  bool attackConfirmed = false;

  int setCount = 0;
  std::vector<Card> playerCards;
  // ORDERS

  std::vector<const ReinforceOrder *> reinforceOrders;
  std::vector<const AttackOrder *> attackOrders;
  std::vector<const RollDiceOrder *> rollDiceOrders;
  std::vector<const MoveTroopsOrder *> moveTroopsOrders;
  std::vector<const FortifyOrder *> fortifyOrders;

public:
  GameState();
  // SETTERS

  void setPhase(PhaseType newPhase);

  void setPlayerTurnID(int playerID);

  void setToSelection(TerritoryID territoryID);
  void setFromSelection(TerritoryID territoryID);

  void setAttackerDice(int diceCount);
  void setAttackConfirmed(bool confirmed);

  void setInitialReinforceCount(int troopCount);
  void updateReinforcePool(int troopCount);
  void setReinforceComplete(bool complete);

  void setPlayerCards(const std::vector<Card> &playerSet);
  void setTurnStarted(bool started);
  // ADD ORDERS

  void addReinforceOrder(const ReinforceOrder &order);
  void addAttackOrder(const AttackOrder &order);
  void addRollDiceOrder(const RollDiceOrder &order);
  void addMoveTroopsOrder(const MoveTroopsOrder &order);
  void addFortifyOrder(const FortifyOrder &order);
  // REMOVE LAST ORDERS

  void removeLastReinforceOrder();
  void removeLastAttackOrder();
  void removeLastRollDiceOrder();
  void removeLastMoveTroopsOrder();
  void removeLastFortifyOrder();
  // CLEARERS
  void clearTurn();

  void clearOrders();

  void clearAttack();
  // GETTERS

  PhaseType getPhase() const;

  int getPlayerTurnID();

  int getReinforcePool();

  bool getReinforceComplete();

  int calcSetCount();

  TerritoryID getToTerritorySelection() const;
  TerritoryID getFromTerritorySelection() const;

  int getAttackerDice() const;
  bool getAttackConfirmed() const;

  std::vector<Card> getPlayerCards();

   bool getTurnStarted() const;
  // ORDER GETTERS

  const ReinforceOrder &getLastReinforceOrder() const;
  const AttackOrder &getLastAttackOrder() const;
  const RollDiceOrder &getLastRollDiceOrder() const;
  const MoveTroopsOrder &getLastMoveTroopsOrder() const;
  const FortifyOrder &getLastFortifyOrder() const;

  bool hasMoveTroopsOrder() const;
};

} // namespace european_conquest