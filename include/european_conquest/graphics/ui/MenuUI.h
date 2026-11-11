#pragma once

#include <array>
#include <optional>

#include <SFML/Graphics.hpp>

#include "european_conquest/graphics/components/DebugGrid.h"

namespace european_conquest {

/**
 * Displays game configuration controls and collects player and map selections before starting a session.
 */
class MenuUI {

private:
  int humanPlayerNumbers;
  int aiPlayerNumbers;
  bool GameStarted = false;

  std::optional<DebugGrid> debugGrid;

  // MENU GRAPHICS

  sf::Texture backgroundTexture;
  std::optional<sf::Sprite> backgroundSprite;

  sf::Texture menuFrameTexture;
  std::optional<sf::Sprite> menuFrameSprite;

  sf::Shader desaturationShader;
  sf::Font font;

  // Background dampener
  sf::VertexArray backgroundDampener;

  // Menu title
  sf::Text title;

  // Menu backing
  sf::RectangleShape parchmentBacking;

  // CAMPAIGN

  sf::Text mapSelectionTitle;
  sf::Text campaignTitle;

  // Campaign dividers
  sf::Texture dividerTexture;

  std::optional<sf::Sprite> leftDivider;
  std::optional<sf::Sprite> rightDivider;

  // PLAYER SELECTION

  sf::Text numberOfPlayersTitle;

  // Number of players dividers
  std::optional<sf::Sprite> playerLeftDivider;
  std::optional<sf::Sprite> playerRightDivider;

  // HUMAN PLAYERS

  sf::Text humanPlayersTitle;

  std::array<sf::RectangleShape, 6> humanPlayerBoxes;

  sf::Text humanPlayer1Text;
  sf::Text humanPlayer2Text;
  sf::Text humanPlayer3Text;
  sf::Text humanPlayer4Text;
  sf::Text humanPlayer5Text;
  sf::Text humanPlayer6Text;

  // AI PLAYERS

  sf::Text aiPlayersTitle;

  std::array<sf::RectangleShape, 6> aiPlayerBoxes;

  sf::Text aiPlayer0Text;
  sf::Text aiPlayer1Text;
  sf::Text aiPlayer2Text;
  sf::Text aiPlayer3Text;
  sf::Text aiPlayer4Text;
  sf::Text aiPlayer5Text;

  // START BUTTON

  sf::RectangleShape startButton;
  sf::Text startButtonText;

public:
  MenuUI();

  // MENU METHODS

  void draw(sf::RenderWindow &window);

  void handleEvent(const sf::Event &event, sf::RenderWindow &window);

  // SETTER METHODS

  void setHumanPlayerNumbers(int number);

  void setAiPlayerNumbers(int number);

  void setGameStarted();

  // GETTER METHODS

  int getHumanPlayerNumbers() const;

  int getAiPlayerNumbers() const;

  bool isGameStarted() const;
};

} // namespace european_conquest