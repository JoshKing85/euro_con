
#pragma once

#include "european_conquest/enums.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace european_conquest {

/**
 * Renders card artwork and territory geometry.
 * Manages visual transformations, selection state and interaction bounds.
 */
class CardGraphics {
private:
  // CARD DATA
  CardType cardType;

  // GRAPHICS
  sf::RectangleShape cardShape;
  std::vector<sf::VertexArray> territoryShapes;
  sf::Text cardTypeText;

  // TERRITORY TRANSFORM
  sf::Vector2f territoryPosition = {0.0f, 0.0f};
  float territoryScale = 1.0f;
  sf::Angle territoryRotation = sf::degrees(0.0f);

  // STATE
  bool selected = false;

public:
  // CONSTRUCTOR
  CardGraphics(CardType cardType,
               const std::vector<std::vector<sf::Vector2f>> &territoryVertices,
               const sf::Font &font);

  // TRANSFORM
  void setPosition(sf::Vector2f position);
  void setRotation(sf::Angle rotation);

  // SELECTION
  void setSelected(bool selected);
  bool isSelected() const;

  // CARD DATA
  CardType getCardType() const;

  // BOUNDS
  sf::FloatRect getBounds() const;
  bool contains(sf::Vector2f point) const;

  // DRAW
  void draw(sf::RenderWindow &window) const;
};

} // namespace european_conquest
