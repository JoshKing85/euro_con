#pragma once

#include "european_conquest/core/session/GameSession.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/graphics/components/AttackWindow.h"
#include "european_conquest/graphics/components/CardContainer.h"
#include "european_conquest/graphics/components/PlayerIndicator.h"
#include "european_conquest/graphics/components/PreAttackBox.h"

#include "european_conquest/graphics/game_elements/PlayerGraphics.h"
#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace european_conquest {

/**
 * Handles attack-phase input and presentation, passing combat requests to GameSession and displaying the resulting state.
 */
class AttackUI {

private:
  // UI COMPONENTS

  sf::Text phaseTitle;

  std::optional<PreAttackBox> preAttackBox;
  std::optional<AttackWindow> attackWindow;
  std::optional<CardContainer> cardContainer;
  std::optional<PlayerIndicator> playerIndicator;

  sf::RectangleShape fortifyButton;
  std::optional<sf::Text> fortifyButtonText;

  // TERRITORY SELECTION

  void territorySelection(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  // PRE ATTACK

  void handlePreAttack(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void back(GameSession &gameSession, GameState &gameState);

  void confirm(
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  // ATTACK WINDOW
 
  void handleAttackWindow(
      const sf::Event &event, sf::RenderWindow &window, 
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void setAttackWindow(
      GameState &gameState, GameSession &gameSession, std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
  
  void selectDice(
      int diceCount,
      GameState &gameState,
      GameSession &gameSession);

  void attack(GameState &gameState, GameSession &gameSession);

  void quitAttack(GameState &gameState, GameSession &gameSession);

  // MOVE TROOPS

  void addTroops(GameSession &gameSession, GameState &gameState);

  void removeTroops(GameSession &gameSession, GameState &gameState);

  void confirmMove(GameState &gameState, GameSession &gameSession);

  // FORTIFY BUTTON

  void fortify(GameState &gameState);

public:
  // CONSTRUCTOR

  AttackUI(const sf::Font &font,
           const std::unordered_map<TerritoryID, TerritoryGraphics>
               &territoryGraphicsMap,
           GameState &gameState, GameSession &gameSession);
  // EVENT HANDLING

  void handleAttackEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
  // DRAW

  void draw(sf::RenderWindow &window, GameState &gameState);
};

} // namespace european_conquest