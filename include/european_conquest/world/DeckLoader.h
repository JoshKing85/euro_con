#pragma once

#include "european_conquest/enums.h"
#include "european_conquest/world/Deck.h"
#include "european_conquest/world/Map.h"

namespace european_conquest {

// Creates the gameplay card deck from the territories in the map.
Deck createDeck(const Map &map);

}