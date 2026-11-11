#pragma once

#include <SFML/Graphics.hpp>

#include "european_conquest/graphics/components/DebugGrid.h"
#include "european_conquest/graphics/components/PlayerProfile.h"

#include <array>
#include <optional>
#include <string>
#include <vector>

namespace european_conquest {

/**
 * Collects player names and avatar selections for use when creating the game session.
 */
class ProfileUI {

private:
  // STATE

  std::optional<DebugGrid> debugGrid;

  // RESOURCES

  sf::Font &font;

  // BACKGROUND

  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

  // MUSTER BOARD

  sf::Texture musterBoardTexture;
  sf::Sprite musterBoardSprite;

  // TEXT

  sf::Text playerText;
  sf::Text playerNumberText;

  sf::Text nameLabel;
  sf::Text nameText;

  sf::Text avatarLabel;

  sf::Text startText;

  // NAME ENTRY

  sf::RectangleShape nameBox;

  // AVATAR SELECTION

  std::array<sf::RectangleShape, 6> avatarBoxes;
  std::array<sf::Texture, 6> avatarTextures;
  std::array<sf::Sprite, 6> avatarSprites;
  
  // START

  sf::RectangleShape startButton;

  // EVENT HANDLERS

  void handleNameEntry(
      const sf::Event &event, 
      PlayerProfile &profile);

  void handleAvatarSelection(
      const sf::Event &event, 
      sf::RenderWindow &window,
      PlayerProfile &profile,
      const std::vector<PlayerProfile> &profiles);

  void handleStart(const 
      sf::Event &event, 
      sf::RenderWindow &window,
      PlayerProfile &profile);

  // ACTIONS

  void setAvatar(int avatarID, PlayerProfile &profile);

  void confirmProfile(PlayerProfile &profile);

public:
  // CONSTRUCTOR

  ProfileUI(sf::Font &font);

  // EVENT ROUTER

  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   PlayerProfile &profile,
                   const std::vector<PlayerProfile> &profiles);

  // STATE

  void resetProfile();

  // DRAW

  void profileUIdraw(sf::RenderWindow &window, int playerID,
                     const std::vector<PlayerProfile> &profiles);
};

} // namespace european_conquest