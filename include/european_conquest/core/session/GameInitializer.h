#pragma once

#include "european_conquest/entities/Player.h"

#include "european_conquest/world/Deck.h"
#include "european_conquest/world/Map.h"

#include "european_conquest/core/managers/GameStateManager.h"

#include <string>
#include <tuple>
#include <vector>

namespace european_conquest {

/** Prepares a new game by loading its world, creating players and dealing initial resources. */
class GameInitializer {

public:
  GameInitializer();

  std::tuple<Map, std::vector<Player>, Deck>
  initializeGame(std::string &filename, int playerNumbers, int aiNumbers);

  void updatePlayer(Player &player, const std::string &name);

  void dealDeck(Deck &deck, std::vector<Player> &players, Map &map,
                GameStateManager &gameStateManager);
};

} // namespace european_conquest