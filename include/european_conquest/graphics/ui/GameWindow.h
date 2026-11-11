#pragma once

#include <SFML/Graphics.hpp>

#include "european_conquest/core/session/GameSession.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/graphics/components/PlayerProfile.h"

#include "european_conquest/graphics/ui/GameSessionUI.h"
#include "european_conquest/graphics/ui/LUIExchange.h"
#include "european_conquest/graphics/ui/LoadingUI.h"
#include "european_conquest/graphics/ui/MenuUI.h"
#include "european_conquest/graphics/ui/ProfileUI.h"

#include <optional>
#include <string>
#include <vector>

namespace european_conquest {

/**
 * Owns the application window and coordinates navigation between menus, player profiles and gameplay.
 */
class GameWindow {

private:
  // WINDOW

  sf::RenderWindow window;

  // CORE

  GameState gameState;
  GameSession gameSession;
  LUIExchange exchangeLUI;

  // PRE-GAME UI

  MenuUI menuUI;

  sf::Font profileFont;
  std::optional<ProfileUI> profileUI;

  std::vector<PlayerProfile> playerProfiles;
  int currentProfile = 0;

  // GAME UI

  LoadingUI loadingUI;
  GameSessionUI gameSessionUI;

  // LOADING

  sf::Clock loadingClock;
  bool loadingStarted = false;

public:
  // CONSTRUCTION

  GameWindow(sf::VideoMode videoMode, std::string title);

  // MAIN LOOP

  void run();
};

} // namespace european_conquest