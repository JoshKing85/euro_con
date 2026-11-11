#pragma once

#include "european_conquest/enums.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace european_conquest {

/** Draws territory geometry, ownership and troop counts. */
class TerritoryGraphics {

private:
  TerritoryID territoryID;
  RegionID regionID;
  int playerID;
  std::string title;

  std::vector<std::vector<sf::Vector2f>> vertices;

  std::vector<sf::VertexArray> fills;
  std::vector<sf::VertexArray> outlines;

  sf::Text titleText;
  sf::Text troopCountText;

  const std::vector<sf::Texture>& factionTroopCounters;
  std::optional<sf::Sprite> troopCounter;
  sf::Vector2f troopPosition;

  float outlineThickness;
  bool selected = false;
  bool hovered = false;

  void updateOutlines();

public:
  TerritoryGraphics(TerritoryID territoryID, RegionID regionID,
                    int playerID, const std::string &title,
                    const std::vector<std::vector<sf::Vector2f>> &vertices,
                    unsigned int titleCharacterSize,
                    unsigned int troopCharacterSize, float outlineThickness,
                    const sf::Font &font,
                    const std::vector<sf::Texture>& factionTroopCounters);

  void setPlayerID(int playerID);

  void setTroopCount(int troopCount);

  void setSelected(bool selected);

  void setHovered(bool hovered);

  void setFactionColour(int avatarID);

  void draw(sf::RenderWindow &window) const;

  void drawLabels(sf::RenderWindow &window) const;

  sf::FloatRect getBounds() const;

  bool contains(sf::Vector2f point) const;

  sf::Vector2f getLabelOffset() const;

  TerritoryID getTerritoryID() const;

  int getPlayerID() const;

  const std::vector<std::vector<sf::Vector2f>> &getVertices() const;

  std::string getTitle() const;

  // TerritoryGraphics.h
    sf::Vector2f getTroopPosition() const;
 };

} // namespace european_conquest
