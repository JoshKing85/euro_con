#pragma once

#include "european_conquest/enums.h"

#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace european_conquest {

/** Describes a map feature and its geometric points. */
struct Feature {
  std::string name;
  FeatureType featureType;

  std::vector<sf::Vector2f> vertices;

  std::vector<std::vector<sf::Vector2f>> tributaries;
};

} // namespace european_conquest