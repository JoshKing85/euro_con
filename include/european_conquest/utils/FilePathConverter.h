#pragma once

#include "european_conquest/enums.h"
#include <string>

namespace european_conquest {

// MAP DATA
inline std::string mapTypeToFilename(MapType mapType) {
  switch (mapType) {
  case MapType::Classic:
    return "data/maps/europe_NA_map.json";
  }

  return "";
}

// BOARD GRAPHICS DATA
inline std::string mapTypeToBoardFilename(MapType mapType) {
  switch (mapType) {
  case MapType::Classic:
    return "data/graphics/classic/"
           "classic_board.json";
  }

  return "";
}

} // namespace european_conquest