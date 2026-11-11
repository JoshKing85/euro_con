#pragma once

#include "european_conquest/enums.h"

#include "european_conquest/core/managers/AttackManager.h"
#include "european_conquest/core/managers/GameStateManager.h"
#include "european_conquest/core/managers/TroopManager.h"

#include "european_conquest/core/session/GameInitializer.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/entities/AIPlayer.h"
#include "european_conquest/entities/Card.h"
#include "european_conquest/entities/Player.h"

#include "european_conquest/world/Deck.h"
#include "european_conquest/world/Map.h"

#include <string>
#include <vector>

namespace european_conquest {

/** Coordinates gameplay requests from the graphics layer through the domain managers.
 * Owns the players, map and deck, and exposes validation, order handling and turn progression. */
class GameSession {

private:
  std::vector<Player> players;
  Deck deck;
  Map map;

  std::vector<int> remainingTroops;

  GameStateManager gameStateManager;
  AttackManager attackManager;
  TroopManager troopManager;

  // std::vector<AIPlayer> AIPlayers;
  // persistent logs
  // player profiles

public:
  GameSession();

  
  // GAME
  void createGame(std::string &filename, int playerNumbers, int aiNumbers);

  void endTurn(GameState &gameState);

  
  // VALIDATION
  
  bool validateSelection(TerritoryID selectedTerritory,
                         std::vector<TerritoryID> territories);

  bool validateAttackSelection(int playerID, TerritoryID &territorySelection);

  bool validateAttackInput(TerritoryID toSelection,
                               TerritoryID fromSelection);

  bool validateTroopCountInput(int troopCount, GameState &gameState);

  bool validateDiceInput(int diceCount, GameState &gameState);

  bool validateFortifySelection(TerritoryID fromSelection,
                                TerritoryID toSelection, GameState &gameState);

  std::optional<SetType> validateCashSet(const std::vector<Card> &cards);

  
  // REINFORCE ORDER
  void createReinforceOrder(TerritoryID territoryID, int troopCount,
                            GameState &gameState);

  void executeReinforceOrder(GameState &gameState);

  void undoReinforceOrder(GameState &gameState);

  void updateReinforceOrder(bool add, GameState &gameState);

  
  // CASH SET ORDER

  void createCashSetOrder(SetType setType, const std::vector<Card> &cards,
                          GameState &gameState);

  void executeCashSetOrder(GameState &gameState);

  void undoCashSetOrder(GameState &gameState);

 
  // ATTACK ORDER
  
  void createAttackOrder(GameState &gameState);

  void executeAttackOrder(GameState &gameState);

  void undoAttackOrder(GameState &gameState);

  
  // ROLL DICE ORDER
 
  void createRollDiceOrder(int diceCount, GameState &gameState);

  void undoRollDiceOrder(GameState &gameState);

  void updateRollDiceOrder(int diceCount);

  
  // MOVE TROOPS ORDER
  
  void createMoveTroopsOrder(TerritoryID fromTerritory, TerritoryID toTerritory,
                             int troopCount, GameState &gameState);

  void updateMoveTroopsOrder(bool add);

  void executeMoveTroopsOrder(GameState &gameState);

  void undoMoveTroopsOrder(GameState &gameState);

  
  // FORTIFY ORDER
  
  void createFortifyOrder(TerritoryID fromTerritory, TerritoryID toTerritory,
                          int troopCount, GameState &gameState);

  void executeFortifyOrder(GameState &gameState);

  void undoFortifyOrder(GameState &gameState);

  void updateFortifyOrder(bool add);

  
  // SETTERS
 
  void addTroop(TerritoryID territoryID, int playerID);

  void setReinforcePool(GameState &gameState);

  void updatePlayerSet(GameState &gameState, std::vector<Card> &cards);
  

  
  // GETTERS
  Map &getMap();
  std::vector<Player> &getPlayers();

  std::vector<int> getPlayerIDs() const;
  std::vector<int> getRemainingTroops() const;
  std::vector<int> getTroopCounts() const;

  Player &getPlayer(int playerID);
  const std::vector<Card> &getPlayerCards(int playerID);
  std::vector<Card> checkCardState(int defendingPlayerID);
};

} // namespace european_conquest