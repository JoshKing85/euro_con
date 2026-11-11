#include "european_conquest/graphics/ui/FortifyUI.h"
#include "european_conquest/core/validation/ValidateTroopCountInput.h"

namespace european_conquest {

    // CONSTRUCTOR

    FortifyUI::FortifyUI(
        const sf::Font& font,
        GameState& gameState)
        : phaseTitle(font)
    {
        // PHASE TITLE

        phaseTitle.setString(
            "FORTIFY PHASE");

        phaseTitle.setCharacterSize(
            28);

        phaseTitle.setFillColor(
            sf::Color::Black);

        phaseTitle.setStyle(
            sf::Text::Bold);

        sf::FloatRect titleBounds =
            phaseTitle.getLocalBounds();

        phaseTitle.setOrigin(
            {
                titleBounds.position.x +
                    titleBounds.size.x / 2.0f,
                titleBounds.position.y
            });

        phaseTitle.setPosition(
            {
                960.0f,
                20.0f
            });

        // FORTIFY CONTROLS

        fortifyControls.emplace(
            font);

        playerIndicator.emplace(
            font);

        playerIndicator->setPosition(
            gameState.getPlayerTurnID());
    }

    // EVENT HANDLING

    void FortifyUI::handleFortifyEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<
        TerritoryID,
        TerritoryGraphics>& territoryGraphicsMap)
    {
        // TERRITORY SELECTION

        if (gameState.getFromTerritorySelection() ==
            TerritoryID::None ||
            gameState.getToTerritorySelection() ==
            TerritoryID::None)
        {
            territorySelection(
                event,
                window,
                gameSession,
                gameState,
                territoryGraphicsMap);

            return;
        }

        // FORTIFY CONTROLS

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            if (fortifyControls->getAddTroopsBounds().contains(
                mousePosition))
            {
                addTroop(
                    gameSession,
                    gameState);

                return;
            }

            if (fortifyControls->getRemoveTroopsBounds().contains(
                mousePosition))
            {
                removeTroop(
                    gameSession,
                    gameState);

                return;
            }

            if (fortifyControls->getBackBounds().contains(
                mousePosition))
            {
                back(
                    gameSession,
                    gameState);

                return;
            }

            if (fortifyControls->getConfirmBounds().contains(
                mousePosition))
            {
                confirm(
                    gameSession,
                    gameState);

                return;
            }
        }
    }

    // TERRITORY SELECTION

    // Select a source and a reachable destination owned by the active player.
    void FortifyUI::territorySelection(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<
        TerritoryID,
        TerritoryGraphics>& territoryGraphicsMap)
    {
        TerritoryID fromTerritory =
            gameState.getFromTerritorySelection();

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            for (auto& [territoryID, territoryGraphics] :
                territoryGraphicsMap)
            {
                if (territoryGraphics.contains(
                    mousePosition))
                {
                    // FROM SELECTION

                    if (fromTerritory ==
                        TerritoryID::None)
                    {
                        const std::vector<TerritoryID>& territories =
                            gameSession
                            .getPlayer(
                                gameState.getPlayerTurnID())
                            .getTerritoriesHeld();

                        if (gameSession.validateSelection(
                            territoryID,
                            territories))
                        {
                            gameState.setFromSelection(
                                territoryID);
                        }

                        return;
                    }

                    // TO SELECTION

                    if (gameSession.validateFortifySelection(
                        fromTerritory,
                        territoryID,
                        gameState))
                    {
                        gameState.setToSelection(
                            territoryID);

                        gameSession.createFortifyOrder(
                            fromTerritory,
                            territoryID,
                            1,
                            gameState);

                        fortifyControls->setTroopCount(
                            1);

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        float boxX =
                            bounds.position.x +
                            bounds.size.x +
                            10.0f;

                        float boxY =
                            bounds.position.y;

                        if (boxX + 250.0f >
                            static_cast<float>(
                                window.getSize().x))
                        {
                            boxX =
                                bounds.position.x -
                                250.0f -
                                10.0f;
                        }

                        fortifyControls->setTroopControlsPosition(
                            {
                                boxX,
                                boxY
                            });

                        return;
                    }

                    // CHANGE FROM SELECTION

                    const std::vector<TerritoryID>& territories =
                        gameSession
                        .getPlayer(
                            gameState.getPlayerTurnID())
                        .getTerritoriesHeld();

                    if (gameSession.validateSelection(
                        territoryID,
                        territories))
                    {
                        gameState.setFromSelection(
                            territoryID);
                    }

                    return;
                }
            }
        }
    }

    // BACK

    void FortifyUI::back(
        GameSession& gameSession,
        GameState& gameState)
    {
        gameSession.undoFortifyOrder(
            gameState);

        gameState.setFromSelection(
            TerritoryID::None);

        gameState.setToSelection(
            TerritoryID::None);
    }

    // CONFIRM

    // Apply the pending fortification through the session only after confirmation.
    void FortifyUI::confirm(
        GameSession& gameSession,
        GameState& gameState)
    {
        gameSession.executeFortifyOrder(
            gameState);

        gameSession.endTurn(
            gameState);
    }

    // ADD TROOP

    void FortifyUI::addTroop(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState.getLastFortifyOrder()
            .getFortifyTroopCount() + 1;

        int troopPool =
            gameSession.getMap()
            .getTerritory(
                gameState.getFromTerritorySelection())
            .getTroopCount() - 1;

        if (isTroopCountValid(
            troopCount,
            troopPool))
        {
            gameSession.updateFortifyOrder(
                true);

            fortifyControls->setTroopCount(
                gameState.getLastFortifyOrder()
                .getFortifyTroopCount());
        }
    }

    // REMOVE TROOP

    void FortifyUI::removeTroop(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState.getLastFortifyOrder()
            .getFortifyTroopCount();

        if (troopCount > 1)
        {
            gameSession.updateFortifyOrder(
                false);

            fortifyControls->setTroopCount(
                gameState.getLastFortifyOrder()
                .getFortifyTroopCount());
        }
    }

    // DRAW

    void FortifyUI::draw(
        sf::RenderWindow& window,
        GameState& gameState)
    {
        phaseTitle.setPosition(
            {
                static_cast<float>(
                    window.getSize().x) / 2.0f,
                20.0f
            });

        window.draw(
            phaseTitle);

        // FORTIFY CONTROLS

        if (gameState.getFromTerritorySelection() !=
            TerritoryID::None &&
            gameState.getToTerritorySelection() !=
            TerritoryID::None)
        {
            fortifyControls->draw(
                window);
        }

        // PLAYER INDICATOR

        if (playerIndicator)
        {
            playerIndicator->draw(
                window);
        }
    }

} // namespace european_conquest
