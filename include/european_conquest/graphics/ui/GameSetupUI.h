#pragma once

#include "european_conquest/core/session/GameSession.h"
#include "european_conquest/core/session/GameSetupState.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/graphics/components/PlayerIndicator.h"
#include "european_conquest/graphics/components/PlayerProfile.h"
#include "european_conquest/graphics/components/SetupControls.h"

#include "european_conquest/graphics/game_elements/PlayerGraphics.h"
#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace european_conquest {

/**
 * Manages the initial troop placement interface and setup selections. Passes confirmed placements to GameSession and updates the displayed setup state.
 */
class GameSetupUI {

private:
  GameSetupState gameSetupState;

  std::optional<PlayerIndicator> playerIndicator;
  std::optional<SetupControls> setupControls;
  void handleTroops(
      const sf::Event &event, GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void troopPlacement(
      const sf::Event &event, GameSession &gameSession,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void back(const sf::Event &event);

  void confirm(const sf::Event &event, GameSession &gameSession,
               GameState &gameState);

public:
  void initialize(GameSession &gameSession, sf::Font &font,
                  std::vector<PlayerGraphics> &playerGraphics,
                  const std::vector<PlayerProfile> &playerProfiles);

  void handleEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void draw(sf::RenderWindow &window);

  GameSetupState &getGameSetupState();
};

} // namespace european_conquest