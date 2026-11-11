
#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

namespace european_conquest {

/**
 * Displays attack confirmation controls and territory information
 * before combat begins.
 */
class PreAttackBox {

private:
  // CONTAINER
  sf::RectangleShape preAttackBox;

  // FROM TERRITORY
  std::optional<sf::Text> fromTerritoryText;
  std::optional<sf::Text> fromPlayerText;
  std::optional<sf::Text> fromTroopText;

  // TO TERRITORY
  std::optional<sf::Text> toTerritoryText;
  std::optional<sf::Text> toPlayerText;
  std::optional<sf::Text> toTroopText;

  // CONTROLS
  sf::RectangleShape backButton;
  std::optional<sf::Text> backButtonText;

  sf::RectangleShape confirmButton;
  std::optional<sf::Text> confirmButtonText;

public:
  PreAttackBox(const sf::Font &font);

  // POSITION
  void setPosition(sf::Vector2f position);

  // FROM TERRITORY
  void setFromTerritoryName(const std::string &name);
  void setFromPlayerName(const std::string &name);
  void setFromTroopCount(int troopCount);

  // TO TERRITORY
  void setToTerritoryName(const std::string &name);
  void setToPlayerName(const std::string &name);
  void setToTroopCount(int troopCount);

  // BOUNDS
  sf::FloatRect getBackBounds() const;
  sf::FloatRect getConfirmBounds() const;

  // DRAW
  void draw(sf::RenderWindow &window);
};

} // namespace european_conquest
