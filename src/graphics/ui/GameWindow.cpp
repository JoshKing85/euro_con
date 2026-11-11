#include <iostream>

#include "european_conquest/graphics/ui/GameWindow.h"
#include "european_conquest/utils/FilePathConverter.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace european_conquest {

    // CONSTRUCTION

    GameWindow::GameWindow(
        sf::VideoMode videoMode,
        std::string title)
        :window(videoMode, title, sf::Style::Default, sf::State::Windowed,
        []
        {
            sf::ContextSettings settings;
            settings.antiAliasingLevel = 8;

            return settings;
        }()),
        gameState(),
        gameSession(),
        exchangeLUI()
       
    {
        // PROFILE UI

        if (!profileFont.openFromFile(
            "C:/Windows/Fonts/georgia.ttf"))
        {
            throw std::runtime_error(
                "Could not load profile font");
        }

        profileUI.emplace(
            profileFont);

        std::cout << "Shaders supported: "
          << sf::Shader::isAvailable()
          << '\n';
    }

    // MAIN LOOP

    void GameWindow::run()
    {
        std::cout << "MSAA: " << window.getSettings().antiAliasingLevel << '\n';
        bool menuActive = true;
        bool profilesActive = false;
        bool gameCreated = false;

        while (window.isOpen())
        {
            // HANDLE EVENTS

            while (const std::optional event =
                window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }

                // MENU EVENTS

                if (menuActive)
                {
                    menuUI.handleEvent(
                        *event,
                        window);
                }

                // PROFILE EVENTS

                else if (profilesActive)
                {
                    if (currentProfile <
                        static_cast<int>(
                            playerProfiles.size()))
                    {
                        PlayerProfile& profile =
                            playerProfiles[
                                currentProfile];

                        bool wasConfirmed =
                            profile.confirmed;

                        profileUI->handleEvent(
                            *event,
                            window,
                            profile,
                            playerProfiles);

                        // AVATAR SELECTED

                        if (!wasConfirmed &&
                            profile.confirmed)
                        {
                            currentProfile++;

                            // ALL PROFILES COMPLETE

                            if (currentProfile >=
                                static_cast<int>(
                                    playerProfiles.size()))
                            {
                                try
                                {
                                    std::string mapFilename =
                                        "data/graphics/europe/europe_NA_map.json";

                                    gameSession.createGame(
                                        mapFilename,
                                        menuUI.getHumanPlayerNumbers(),
                                        menuUI.getAiPlayerNumbers());

                                    gameCreated = true;
                                    profilesActive = false;

                                    loadingClock.restart();
                                    loadingStarted = true;
                                }
                                catch (
                                    const std::exception&
                                    exception)
                                {
                                    std::cerr
                                        << "Game creation failed: "
                                        << exception.what()
                                        << '\n';

                                    window.close();
                                }
                            }
                        }
                    }
                }

                // GAME EVENTS

                else if (
                    gameCreated &&
                    gameState.getPhase() !=
                    PhaseType::Loading)
                {
                    gameSessionUI.handleEvent(
                        *event,
                        window,
                        gameSession,
                        gameState);
                }
            }

            // LEAVE MENU AND CREATE PROFILES

            if (menuActive &&
                menuUI.isGameStarted())
            {
                menuActive = false;
                profilesActive = true;

                playerProfiles.clear();

                currentProfile = 0;

                int humanPlayers =
                    menuUI.getHumanPlayerNumbers();

                for (int playerID = 0;
                    playerID < humanPlayers;
                    ++playerID)
                {
                    PlayerProfile profile;

                    profile.playerID =
                        playerID;

                    playerProfiles.push_back(
                        profile);
                }
            }

            // UPDATE GAME GRAPHICS

            if (gameCreated &&
                gameState.getPhase() !=
                PhaseType::Loading)
            {
                std::vector<PlayerGraphics>&
                    playerGraphics =
                    gameSessionUI
                    .getPlayerGraphics();

                std::unordered_map<
                    TerritoryID,
                    TerritoryGraphics>&
                    territoryGraphicsMap =
                    gameSessionUI
                    .getTerritoryGraphics();

                const std::vector<Player>& players =
                    gameSession.getPlayers();

                const Map& map =
                    gameSession.getMap();

                // INITIAL TROOP PLACEMENT

                if (gameState.getPhase() ==
                    PhaseType::GameSetup)
                {
                    GameSetupState& gameSetupState =
                        gameSessionUI
                        .getGameSetupState();

                    exchangeLUI.updateGraphics(
                        map,
                        players,
                        gameState,
                        territoryGraphicsMap,
                        playerGraphics,
                        &gameSetupState);
                }

                // NORMAL GAME PHASES

                else
                {
                    exchangeLUI.updateGraphics(
                        map,
                        players,
                        gameState,
                        territoryGraphicsMap,
                        playerGraphics);
                }
            }

            // DRAW

            window.clear();

            // MENU

            if (menuActive)
            {
                menuUI.draw(
                    window);
            }

            // PROFILES

            else if (profilesActive)
            {
                if (currentProfile <
                    static_cast<int>(
                        playerProfiles.size()))
                {
                    profileUI->profileUIdraw(
                        window,
                        currentProfile,
                        playerProfiles);
                }
            }

            // LOADING

            else if (
                gameCreated &&
                gameState.getPhase() ==
                PhaseType::Loading)
            {
                loadingUI.draw(
                    window,
                    loadingClock
                    .getElapsedTime()
                    .asSeconds());

                if (loadingStarted &&
                    loadingClock
                    .getElapsedTime()
                    .asSeconds() >= 3.f)
                {
                    gameSessionUI.initialLoading(
                        gameSession,
                        gameState,
                        menuUI.getHumanPlayerNumbers(),
                        menuUI.getAiPlayerNumbers(),
                        playerProfiles);

                    loadingStarted = false;
                }
            }

            // GAME

            else if (gameCreated)
            {
                gameSessionUI.draw(
                    window,
                    gameState,
                    gameSession);
            }

            window.display();
        }
    }

} // namespace european_conquest
