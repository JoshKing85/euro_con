#pragma once

#include <string>

namespace european_conquest {

/** Stores the name and avatar selected for a player. */
struct PlayerProfile {

  int playerID = 0;

  int avatarID = -1;

  std::string playerName;

  bool confirmed = false;
};

} // namespace european_conquest