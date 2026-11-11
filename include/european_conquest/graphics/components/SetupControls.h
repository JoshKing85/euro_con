
#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

namespace european_conquest {

/** Displays controls for initial troop placement. */
class SetupControls {
private:
    sf::Texture buttonTexture;

    sf::Sprite backButton;
    sf::Sprite confirmButton;

    std::optional<sf::Text> backButtonText;
    std::optional<sf::Text> confirmButtonText;

    sf::Vector2f calculateStackPosition(
        sf::Vector2f counterCentre) const;

    void centreText(
        sf::Text& text,
        const sf::Sprite& button);

public:
    SetupControls(const sf::Font& font);

    void setPosition(sf::Vector2f counterCentre);

    sf::FloatRect getBackBounds() const;
    sf::FloatRect getConfirmBounds() const;

    void draw(sf::RenderWindow& window);
};

} // namespace european_conquest
