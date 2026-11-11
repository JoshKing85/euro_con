#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

namespace european_conquest {

/** Renders a development grid for layout diagnostics. */
class DebugGrid {

private:
  sf::VertexArray gridLines;

  sf::Font font;
  std::vector<sf::Text> labels;

public:
  DebugGrid();

  void draw(sf::RenderWindow &window) const;
};

} // namespace european_conquest