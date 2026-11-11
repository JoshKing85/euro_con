#pragma once

#include "european_conquest/core/session/GameSession.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/graphics/components/FortifyControls.h"
#include "european_conquest/graphics/components/PlayerIndicator.h"

#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>

namespace european_conquest {

/**
 * Handles fortification selections and controls, forwarding troop movement requests to GameSession.
 */
class FortifyUI {

private:
  // UI COMPONENTS

  sf::Text phaseTitle;

  std::optional<FortifyControls> fortifyControls;
  std::optional<PlayerIndicator> playerIndicator;

  // TERRITORY SELECTION

  void territorySelection(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  // FORTIFY CONTROLS

  void back(GameSession &gameSession, GameState &gameState);

  void confirm(GameSession &gameSession, GameState &gameState);

  void addTroop(GameSession &gameSession, GameState &gameState);

  void removeTroop(GameSession &gameSession, GameState &gameState);

public:
  FortifyUI(const sf::Font &font, GameState &gameState);

  void draw(sf::RenderWindow &window, GameState &gameState);

  void handleFortifyEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
};

} // namespace european_conquest