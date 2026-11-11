#pragma once

#include "european_conquest/graphics/components/Feature.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace european_conquest {

/** Draws geographic features over the game board. */
class FeatureGraphics {
public:
  FeatureGraphics(const std::vector<Feature> &features);

  void draw(sf::RenderWindow &window) const;

private:
  std::vector<sf::VertexArray> featureShapes;

  void createRiver(const Feature &feature);
};

} // namespace european_conquest