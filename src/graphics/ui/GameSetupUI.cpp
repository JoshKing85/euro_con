#include "european_conquest/graphics/ui/GameSetupUI.h"

#include <iostream>

namespace european_conquest {

    // INITIALIZATION

    void GameSetupUI::initialize(
        GameSession& gameSession,
        sf::Font& font,
        std::vector<PlayerGraphics>& playerGraphics,
        const std::vector<PlayerProfile>& playerProfiles)
    {
        playerIndicator.emplace(font);
        setupControls.emplace(font);

        // PLAYER SETUP

        std::vector<int> playerIDs =
            gameSession.getPlayerIDs();

        playerGraphics.reserve(
            playerIDs.size());

        std::vector<int> troopCounts =
            gameSession.getTroopCounts();

        std::vector<int> remainingTroops =
            gameSession.getRemainingTroops();

        for (const auto playerID : playerIDs)
        {
            gameSetupState.addPlayerProfile(
                playerID,
                remainingTroops[playerID]);

            playerGraphics.emplace_back(
                playerID,
                troopCounts[playerID],
                font);

            // APPLY SELECTED PROFILE

            for (const auto& profile : playerProfiles)
            {
                if (profile.playerID == playerID)
                {
                    playerGraphics.back().setAvatar(
                        profile.avatarID);

                    if (!profile.playerName.empty())
                    {
                        playerGraphics.back().setName(
                            profile.playerName);
                    }

                    break;
                }
            }
        }

        std::cout
            << "[DEBUG] Game setup initialized"
            << " | Profiles applied: "
            << playerProfiles.size()
            << '\n';
    }

    // DRAW

    void GameSetupUI::draw(
        sf::RenderWindow& window)
    {
        // PHASE TITLE

        const float centreX =
        static_cast<float>(window.getSize().x) / 2.f;

        constexpr float bannerY = 50.f;
        // CURRENT SETUP PLAYER

        int currentPlayerID =
            gameSetupState.getCurrentProfileID();

        // PLAYER INDICATOR

        playerIndicator->setPosition(
            currentPlayerID);

        playerIndicator->draw(
            window);

        // SETUP CONTROLS

        if (gameSetupState.getTerritorySelected() !=
            TerritoryID::None)
        {
            setupControls->draw(
                window);
        }
    }

    // EVENT HANDLING

    void GameSetupUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap)
    {
        handleTroops(
            event,
            gameSession,
            gameState,
            territoryGraphicsMap);
    }

    // TROOP PLACEMENT

    void GameSetupUI::handleTroops(
        const sf::Event& event,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap)
    {
        if (gameSetupState.getTerritorySelected() ==
            TerritoryID::None)
        {
            troopPlacement(
                event,
                gameSession,
                territoryGraphicsMap);

            return;
        }

        back(
            event);

        if (gameSetupState.getTerritorySelected() !=
            TerritoryID::None)
        {
            confirm(
                event,
                gameSession,
                gameState);
        }
    }

    void GameSetupUI::troopPlacement(
        const sf::Event& event,
        GameSession& gameSession,
        std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
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
                    const std::vector<TerritoryID>& territories =
                        gameSession
                        .getPlayer(
                            gameSetupState
                            .getCurrentProfileID())
                        .getTerritoriesHeld();

                    if (gameSession.validateSelection(
                        territoryID,
                        territories))
                    {
                        gameSetupState.setTerritorySelected(
                            territoryID);

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        setupControls->setPosition(
                            territoryGraphics.getTroopPosition());

                    }

                    break;
                }
            }
        }
    }

    // SETUP CONTROLS

    void GameSetupUI::back(
        const sf::Event& event)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            if (setupControls->getBackBounds().contains(
                mousePosition))
            {
                gameSetupState.setTerritorySelected(
                    TerritoryID::None);
            }
        }
    }

    void GameSetupUI::confirm(
        const sf::Event& event,
        GameSession& gameSession,
        GameState& gameState)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            if (setupControls->getConfirmBounds().contains(
                mousePosition))
            {
                int playerID =
                    gameSetupState
                    .getCurrentProfileID();

                TerritoryID selectedTerritory =
                    gameSetupState
                    .getTerritorySelected();

                gameSession.addTroop(
                    selectedTerritory,
                    playerID);

                gameSetupState.removeTroop(
                    playerID);

                gameSetupState.setTerritorySelected(
                    TerritoryID::None);

                if (gameSetupState.allTroopsPlaced())
                {
                    gameState.setPhase(
                        PhaseType::Reinforce);

                    return;
                }

                gameSetupState.setCurrentProfile(
                    gameSetupState
                    .getCurrentProfileID());
            }
        }
    }

    // STATE ACCESS

    GameSetupState&
        GameSetupUI::getGameSetupState()
    {
        return gameSetupState;
    }

} // namespace european_conquest
