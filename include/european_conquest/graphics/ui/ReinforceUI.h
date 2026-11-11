#pragma once

#include "european_conquest/core/session/GameSession.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/graphics/components/CardContainer.h"
#include "european_conquest/graphics/components/PlayerIndicator.h"
#include "european_conquest/graphics/components/ReinforceControls.h"

#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace european_conquest {

/**
 * Handles reinforcement selections and card controls, passing confirmed orders to GameSession and refreshing the display.
 */
class ReinforceUI {

private:
  // UI COMPONENTS

  sf::Text phaseTitle;

  std::optional<ReinforceControls> reinforceControls;
  std::optional<CardContainer> cardContainer;
  std::optional<PlayerIndicator> playerIndicator;


  // TROOP PLACEMENT

  void handleTroops(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void troopPlacement(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  // REINFORCE CONTROLS

  void back(GameSession &gameSession, GameState &gameState);

  void confirm(GameSession &gameSession, GameState &gameState);

  void addTroop(GameSession &gameSession, GameState &gameState);

  void removeTroop(GameSession &gameSession, GameState &gameState);

  // CARD HANDLING

  void validateCardSelection(GameSession &gameSession, GameState &gameState);

  void cashSet(
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

public:
  ReinforceUI(const sf::Font &font,
              const std::unordered_map<TerritoryID, TerritoryGraphics>
                  &territoryGraphicsMap,
              GameState &gameState, GameSession &gameSession);

  // PLAYER STATE

  void ReinforceUI::setPlayerState(
      GameState &gameState, GameSession &gameSession,
      const std::unordered_map<TerritoryID, TerritoryGraphics>
          &territoryGraphicsMap);

  void draw(sf::RenderWindow &window,
            GameState &gameState);

  void handleReinforceEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
};

} // namespace european_conquest