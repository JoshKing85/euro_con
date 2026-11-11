
#include "european_conquest/graphics/components/SetupControls.h"

#include <algorithm>
#include <stdexcept>

namespace european_conquest {

// CONSTRUCTOR

SetupControls::SetupControls(const sf::Font& font)
    : backButton(buttonTexture),
      confirmButton(buttonTexture)
{
    if (!buttonTexture.loadFromFile(
        "data/graphics/components/SelectionButton.png"))
    {
        throw std::runtime_error(
            "Could not load selection button texture");
    }

    backButton.setTexture(buttonTexture, true);
    confirmButton.setTexture(buttonTexture, true);

    // CROP TRANSPARENT TEXTURE PADDING

    const sf::IntRect buttonRect(
        {20, 23},
        {160, 57}
    );

    backButton.setTextureRect(buttonRect);
    confirmButton.setTextureRect(buttonRect);

    // BUTTON TEXT

    backButtonText.emplace(font);
    confirmButtonText.emplace(font);

    backButtonText->setString("Back");
    confirmButtonText->setString("Confirm");

    backButtonText->setCharacterSize(20);
    confirmButtonText->setCharacterSize(20);

    backButtonText->setFillColor(sf::Color::White);
    confirmButtonText->setFillColor(sf::Color::White);
}

// CALCULATE COMPLETE STACK POSITION

sf::Vector2f SetupControls::calculateStackPosition(
    sf::Vector2f counterCentre) const
{
    constexpr float screenWidth = 1920.f;
    constexpr float screenHeight = 1080.f;

    constexpr float margin = 50.f;
    constexpr float gap = 15.f;
    constexpr float buttonSpacing = 5.f;
    constexpr float counterRadius = 21.f;

    // ACTUAL CROPPED SPRITE DIMENSIONS

    const sf::FloatRect buttonBounds =
        confirmButton.getLocalBounds();

    const float buttonWidth =
        buttonBounds.size.x;

    const float buttonHeight =
        buttonBounds.size.y;

    const float stackHeight =
        buttonHeight * 2.f + buttonSpacing;

    // HORIZONTAL POSITIONING

    // Prefer left of troop counter.
    const float leftX =
        counterCentre.x
        - counterRadius
        - gap
        - buttonWidth;

    // Alternative: right of troop counter.
    const float rightX =
        counterCentre.x
        + counterRadius
        + gap;

    float x;

    if (leftX >= margin)
    {
        x = leftX;
    }
    else
    {
        x = rightX;
    }

    // If right side exceeds screen boundary,
    // switch back to the left.
    if (x + buttonWidth > screenWidth - margin)
    {
        x = leftX;
    }

    // VERTICAL POSITIONING

    // Centre complete stack on troop counter.
    float y =
        counterCentre.y - stackHeight / 2.f;

    // Keep entire stack within screen margins.
    y = std::clamp(
        y,
        margin,
        screenHeight - margin - stackHeight
    );

    return {x, y};
}

// CENTRE TEXT ON BUTTON

void SetupControls::centreText(
    sf::Text& text,
    const sf::Sprite& button)
{
    const sf::FloatRect textBounds =
        text.getLocalBounds();

    text.setOrigin({
        textBounds.position.x
            + textBounds.size.x / 2.f,
        textBounds.position.y
            + textBounds.size.y / 2.f
    });

    const sf::FloatRect buttonBounds =
        button.getGlobalBounds();

    text.setPosition({
        buttonBounds.position.x
            + buttonBounds.size.x / 2.f,
        buttonBounds.position.y
            + buttonBounds.size.y / 2.f
    });
}

// POSITION BOTH BUTTONS

void SetupControls::setPosition(
    sf::Vector2f counterCentre)
{
    constexpr float buttonSpacing = 5.f;

    const sf::Vector2f stackPosition =
        calculateStackPosition(counterCentre);

    const float buttonHeight =
        confirmButton.getLocalBounds().size.y;

    // CONFIRM ABOVE BACK

    confirmButton.setPosition(stackPosition);

    backButton.setPosition({
        stackPosition.x,
        stackPosition.y + buttonHeight + buttonSpacing
    });

    // UPDATE TEXT POSITIONS

    if (confirmButtonText.has_value())
    {
        centreText(
            *confirmButtonText,
            confirmButton);
    }

    if (backButtonText.has_value())
    {
        centreText(
            *backButtonText,
            backButton);
    }
}

// BUTTON BOUNDS FOR MOUSE DETECTION

sf::FloatRect SetupControls::getBackBounds() const
{
    return backButton.getGlobalBounds();
}

sf::FloatRect SetupControls::getConfirmBounds() const
{
    return confirmButton.getGlobalBounds();
}

// DRAW

void SetupControls::draw(sf::RenderWindow& window)
{
    window.draw(confirmButton);
    window.draw(backButton);

    if (confirmButtonText.has_value())
    {
        window.draw(*confirmButtonText);
    }

    if (backButtonText.has_value())
    {
        window.draw(*backButtonText);
    }
}

} // namespace european_conquest
