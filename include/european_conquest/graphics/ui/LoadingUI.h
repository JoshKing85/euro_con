#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace european_conquest {

/**
 * Displays the loading screen while the game prepares its resources.
 */
class LoadingUI {

private:
  // BACKGROUND

  sf::Texture backgroundTexture;
  std::optional<sf::Sprite> backgroundSprite;

  sf::VertexArray backgroundDampener;

  // LOADING BANNER

  sf::Font font;

  sf::RectangleShape loadingBanner;
  sf::Text loadingText;

  sf::RectangleShape topLine;
  sf::RectangleShape bottomLine;

  // LOADING TEXT

  void updateLoadingText(float elapsedSeconds);

public:
  LoadingUI();

  void draw(sf::RenderWindow &window, float elapsedSeconds);
};

} // namespace european_conquest