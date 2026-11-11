#pragma once

#include "european_conquest/core/session/GameSetupState.h"
#include "european_conquest/core/session/GameState.h"

#include "european_conquest/entities/Player.h"
#include "european_conquest/world/Map.h"

#include "european_conquest/graphics/game_elements/PlayerGraphics.h"
#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include "european_conquest/enums.h"

#include <unordered_map>
#include <vector>

namespace european_conquest {

/**
 * Transfers current domain and session state into player and territory graphics for display.
 */
class LUIExchange {

public:
  LUIExchange();

  void updateGraphics(
      const Map &map, const std::vector<Player> &players,
      const GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap,
      std::vector<PlayerGraphics> &playerGraphics,
      const GameSetupState *gameSetupState = nullptr);
};

} // namespace european_conquest