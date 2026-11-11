
#pragma once

#include "european_conquest/graphics/components/RegionValueBoard.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace european_conquest {

/** Loads and draws the map board and its region information. */
class BoardGraphics {
private:
    sf::Texture boardTexture;
    sf::Sprite boardSprite;

   RegionValueBoard regionBoard;

public:
    BoardGraphics(
        const std::string& mapImagePath,
        const sf::Font& font);

    void draw(sf::RenderWindow& window) const;

    void drawRegionUI(sf::RenderWindow& window) const;

    bool handleRegionClick(sf::Vector2f mousePosition);
};

} // namespace european_conquest
