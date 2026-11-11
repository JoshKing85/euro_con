
#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace european_conquest {

/** Displays map previews and provides controls for map selection. */
class MapSelector {

private:
  // MAP PREVIEW
  sf::RectangleShape mapImageBox;

  sf::Texture mapTexture;
  std::optional<sf::Sprite> mapSprite;

  // MAP TITLES
  sf::RectangleShape mapTitleBox;
  sf::Text mapTitleClassicText;

  // SELECTION ARROWS
  sf::RectangleShape leftArrowBox;
  sf::RectangleShape rightArrowBox;

  sf::ConvexShape leftArrow;
  sf::ConvexShape rightArrow;

public:
  // CONSTRUCTOR
  explicit MapSelector(const sf::Font &font);

  // DRAW
  void draw(sf::RenderWindow &window);

  // GETTERS
  const sf::RectangleShape &getLeftArrowBox() const;
  const sf::RectangleShape &getRightArrowBox() const;
};

} // namespace european_conquest
