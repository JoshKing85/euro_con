#pragma once

#include "european_conquest/entities/Card.h"
#include "european_conquest/enums.h"
#include "european_conquest/graphics/game_elements/CardGraphics.h"
#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

namespace european_conquest {

/** Displays and manages the player’s card selection interface. */
class CardContainer {
private:
  //---------------------------------------------------------
  // Container Graphics
  //---------------------------------------------------------

  sf::RectangleShape container;

  sf::RectangleShape tab;
  sf::Text tabText;

  sf::RectangleShape cashSetButton;
  sf::Text cashSetButtonText;

  const sf::Font &font;

  //---------------------------------------------------------
  // Card Graphics
  //---------------------------------------------------------

  std::vector<CardGraphics> cardGraphics;

  //---------------------------------------------------------
  // State
  //---------------------------------------------------------

  bool open = false;
  bool cashSetAvailable = false;

  std::vector<int> selectedCards;

  //---------------------------------------------------------
  // Card Handling
  //---------------------------------------------------------

  void setContainer(const std::unordered_map<TerritoryID, TerritoryGraphics>
                        &territoryGraphicsMap,
                    const std::vector<Card> &playerSet);

  void setCardPositions();

public:
  CardContainer(const sf::Font &font,
                const std::unordered_map<TerritoryID, TerritoryGraphics>
                    &territoryGraphicsMap,
                const std::vector<Card> &playerSet);

  //---------------------------------------------------------
  // Open / Close
  //---------------------------------------------------------

  void openContainer();
  void closeContainer();

  bool isOpen() const;

  //---------------------------------------------------------
  // Set Validity
  //---------------------------------------------------------

  void setCashSetAvailable(bool available);

  bool getCashSetAvailable() const;

  //---------------------------------------------------------
  // Selection
  //---------------------------------------------------------

  void selectCard(sf::Vector2f mousePosition);

  const std::vector<int> &getSelectedCards() const;

  void clearSelectedCards();

  //---------------------------------------------------------
  // Bounds
  //---------------------------------------------------------

  sf::FloatRect getTabBounds() const;

  sf::FloatRect getCashSetBounds() const;

  //---------------------------------------------------------
  // Update
  //---------------------------------------------------------

  void updateCards(const std::unordered_map<TerritoryID, TerritoryGraphics>
                       &territoryGraphicsMap,
                   const std::vector<Card> &playerSet);

  //---------------------------------------------------------
  // Clear
  //---------------------------------------------------------

  void clear();

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window) const;
};

} // namespace european_conquest