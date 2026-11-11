#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace european_conquest {

/** Displays the active player’s identity and turn context. */
class PlayerIndicator {
private:

  std::optional<sf::Text> currentPlayerText;
  sf::Texture pointerTexture;
  sf::Sprite pointerSprite;

  sf::Texture instructionTexture;
  sf::Sprite instructionSprite;

public:
  PlayerIndicator(const sf::Font &font);

  void setPosition(int playerID);

  void draw(sf::RenderWindow &window);
};

} // namespace european_conquest