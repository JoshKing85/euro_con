#include "european_conquest/graphics/ui/GameSessionUI.h"

#include "european_conquest/graphics/game_elements/TerritoryGraphics.h"

#include "european_conquest/core/session/GameState.h"
#include "european_conquest/entities/Territory.h"
#include "european_conquest/utils/TerritoryConverter.h"
#include "european_conquest/world/FeatureLoader.h"
#include "european_conquest/graphics/components/Feature.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace european_conquest
{

GameSessionUI::GameSessionUI()
    : frameSprite(frameTexture), devMapSprite(devMapTexture)
{
    // FRAME

    if (!frameTexture.loadFromFile("data/graphics/board/BoardFrame4.png"))
    {
        throw std::runtime_error("Could not load game frame");
    }

    frameSprite.setTexture(frameTexture, true);
    frameSprite.setScale({1.f, 1.f});
    // frameSprite.setPosition();

    // SHARED PHASE TITLE BANNER

    if (!phaseBannerTexture.loadFromFile(
            "data/graphics/board/PhaseTitleBanner.png"))
    {
        throw std::runtime_error("Could not load phase title banner");
    }

    phaseBannerSprite.setTexture(phaseBannerTexture, true);
    phaseBannerSprite.setTexture(phaseBannerTexture, true);

    phaseBannerSprite.setTexture(phaseBannerTexture, true);

    phaseBannerSprite.setScale({1.f, 1.f});

    phaseBannerSprite.setPosition({
        (1920.f - 650.f) / 2.f,
        0.f
    });

    if (!phaseTitleFont.openFromFile("C:/Windows/Fonts/georgiab.ttf"))
    {
        throw std::runtime_error("Could not load phase title font");
    }

    phaseTitleText.setCharacterSize(28);
    phaseTitleText.setFillColor(sf::Color(235, 210, 155));

    // MAP REFERENCE (DEBUG)

    if (!devMapTexture.loadFromFile("data/graphics/devMap.png"))
    {
        throw std::runtime_error("Could not load dev map");
    }

    devMapSprite.setTexture(devMapTexture, true);

    devMapSprite.setScale({1.f, 1.f});

    devMapSprite.setPosition({100.0f, 0.f});

    // FINE MESH (DEBUG)

    fineMesh.emplace();

    // FILTER - PAPER GRAIN

    if (!paperGrainShader.loadFromFile(
        "data/graphics/shaders/paper_grain.frag",
        sf::Shader::Type::Fragment))
    {
        throw std::runtime_error(
            "Could not load paper grain shader");
    }

    paperGrainShader.setUniform(
        "grainStrength", 0.045f);

    paperGrainShader.setUniform(
        "currentTexture",
        sf::Shader::CurrentTexture);

    if (!screenTexture.resize({1920, 1080}))
    {
        throw std::runtime_error(
            "Could not create screen capture texture");
    }

    screenSprite.emplace(screenTexture);
}

    // INITIAL LOADING

    // Build the shared board and phase interfaces from the initial domain session.
    void GameSessionUI::initialLoading(GameSession& gameSession, GameState& gameState, int humanPlayers,
                                   int aiPlayers, const std::vector<PlayerProfile>& playerProfiles)
{
    humanPlayerNumbers = humanPlayers;
    aiPlayerNumbers = aiPlayers;

    try
    {
        const std::string boardFilename = "data/graphics/europe/europe_board.json";

        std::ifstream boardFile(boardFilename);

        if (!boardFile.is_open())
        {
            throw std::runtime_error("Could not open board graphics file: " + boardFilename);
        }

        nlohmann::json boardJson;
        boardFile >> boardJson;

        const auto& boardData = boardJson.at("board");

        const std::string mapImagePath = boardData.at("background_texture").get<std::string>();

        static sf::Font font;

        if (!font.openFromFile("C:/Windows/Fonts/georgia.ttf"))
        {
            throw std::runtime_error("Could not load font");
        }

        const std::string featureFileName = "data/graphics/europe/map_features.json";

        // BOARD

        boardGraphics.emplace(mapImagePath, font);

        // FEATURES

        featureGraphics.emplace(loadFeatures(featureFileName));
        // FACTION TROOP TEXTURES

        factionTroopCounters.clear();
        factionTroopCounters.reserve(6);

        // NAPOLEON
        sf::Texture napoleonCounter;

        if (!napoleonCounter.loadFromFile("data/graphics/factions/NapoleonTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Napoleon troop counter");
        }

        factionTroopCounters.push_back(std::move(napoleonCounter));

        // WELLINGTON
        sf::Texture wellingtonCounter;

        if (!wellingtonCounter.loadFromFile("data/graphics/factions/WellingtonTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Wellington troop counter");
        }

        factionTroopCounters.push_back(std::move(wellingtonCounter));

        // BULCHER
        sf::Texture blucherCounter;

        if (!blucherCounter.loadFromFile("data/graphics/factions/BlucherTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Blucher troop counter");
        }

        factionTroopCounters.push_back(std::move(blucherCounter));

        // VON OSTERRIECH
        sf::Texture vonCounter;

        if (!vonCounter.loadFromFile("data/graphics/factions/VonTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Von troop counter");
        }

        factionTroopCounters.push_back(std::move(vonCounter));

        // LA NEEDLE
        sf::Texture needleCounter;

        if (!needleCounter.loadFromFile("data/graphics/factions/NeedleTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Needle troop counter");
        }

        factionTroopCounters.push_back(std::move(needleCounter));

        // ALEXANDER
        sf::Texture alexCounter;

        if (!alexCounter.loadFromFile("data/graphics/factions/AlexTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Alex troop counter");
        }

        factionTroopCounters.push_back(std::move(alexCounter));
        // SHARED GAME GRAPHICS

        createTerritoryGraphicsMap(gameSession.getMap());

        screenTexture.resize({1920, 1080});
        screenSprite.emplace(screenTexture);

        if (!playerSlotsTexture.loadFromFile(
            "data/graphics/components/PlayerSlots.png"))
        {
            throw std::runtime_error(
                "Could not load player slots texture");
        }
        playerSlotsSprite.setScale({1.02f, 1.0f});
        playerSlotsSprite.setTexture(playerSlotsTexture, true);
        playerSlotsSprite.setPosition({30.f, 750.f});

        // GAME SETUP UI

        gameSetupUI.emplace();

        gameSetupUI->initialize(gameSession, font, playerGraphics, playerProfiles);

        gameState.setPhase(PhaseType::GameSetup);
    }
    catch (const std::exception& exception)
    {
        std::cerr << "GameSessionUI initialization error: " << exception.what() << std::endl;
        throw std::runtime_error(std::string("GameSessionUI initial loading failed: ") +
                                 exception.what());
    }
}

    // DRAW

    // Render the current phase from GameState without applying gameplay rules.
    void GameSessionUI::draw(
        sf::RenderWindow& window,
        GameState& gameState,
        GameSession& gameSession)
    {
        // BOARD

        if (boardGraphics.has_value())
        {
            boardGraphics->draw(
                window);
        }

        // TERRITORY GEOMETRY

        for (const auto& [territoryID, territory] : territoryGraphicsMap)
        {
            territory.draw(window);
        }

        // GEOGRAPHICAL FEATURES

        if (featureGraphics.has_value())
        {
            featureGraphics->draw(window);
        }

        // TERRITORY LABELS AND TROOP COUNTS

        for (const auto& [territoryID, territory] : territoryGraphicsMap)
        {
            territory.drawLabels(window);
        }

                // PAPER GRAIN FILTER

        // Capture the completed map.
        screenTexture.update(window);

        // Apply the paper grain shader.
        sf::RenderStates states;
        states.shader = &paperGrainShader;

        // Draw the filtered image back onto the window.
        window.draw(
            *screenSprite,
            states);
        // PLAYERS
       
        window.draw(playerSlotsSprite);

        for (auto& playerGraphic :
            playerGraphics)
        {
            playerGraphic.draw(
                window);
        }

        // GAME SETUP

        if (gameState.getPhase() ==
            PhaseType::GameSetup)
        {
            if (gameSetupUI.has_value())
            {
                gameSetupUI->draw(
                    window);
            }
        }

        // REINFORCE

        if (gameState.getPhase() ==
            PhaseType::Reinforce)
        {
            if (!reinforceUI.has_value())
            {
                static sf::Font font;

                if (!font.openFromFile(
                    "C:/Windows/Fonts/arial.ttf"))
                {
                    throw std::runtime_error(
                        "Could not load font");
                }

                reinforceUI.emplace(
                    font,
                    territoryGraphicsMap,
                    gameState,
                    gameSession);
            }

            if (!gameState.getTurnStarted())
            {
                reinforceUI->setPlayerState(
                    gameState,
                    gameSession,
                    territoryGraphicsMap);
            }

            reinforceUI->draw(
                window,
                gameState);
        }

        // ATTACK

        if (gameState.getPhase() ==
            PhaseType::Attack)
        {
            if (!attackUI.has_value())
            {
                static sf::Font font;

                if (!font.openFromFile(
                    "C:/Windows/Fonts/arial.ttf"))
                {
                    throw std::runtime_error(
                        "Could not load font");
                }

                attackUI.emplace(
                    font,
                    territoryGraphicsMap,
                    gameState,
                    gameSession);
            }

            attackUI->draw(
                window,
                gameState);
        }

        // FORTIFY

        if (gameState.getPhase() ==
            PhaseType::Fortify)
        {
            if (!fortifyUI.has_value())
            {
                static sf::Font font;

                if (!font.openFromFile(
                    "C:/Windows/Fonts/arial.ttf"))
                {
                    throw std::runtime_error(
                        "Could not load font");
                }

                fortifyUI.emplace(
                    font,
                    gameState);
            }

            fortifyUI->draw(
                window,
                gameState);
        }

        // FRAME

        /*window.draw(
            devMapSprite);*/

        /*fineMesh->draw(
            window);*/

        window.draw(
            frameSprite);

        // Shared phase title (rendered over the board frame)

        std::string title;
        switch (gameState.getPhase())
        {
        case PhaseType::GameSetup:
            title = "INITIAL REINFORCEMENT PHASE";
            break;
        case PhaseType::Reinforce:
            title = "REINFORCEMENT PHASE";
            break;
        case PhaseType::Attack:
            title = "ATTACK PHASE";
            break;
        case PhaseType::Fortify:
            title = "FORTIFICATION PHASE";
            break;
        default:
            break;
        }

        if (!title.empty())
        {
            phaseTitleText.setString(title);
            const sf::FloatRect bounds = phaseTitleText.getLocalBounds();
            phaseTitleText.setOrigin({
                bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f
            });
            // Keep the text centred within the banner as phases change.
            const sf::FloatRect bannerBounds = phaseBannerSprite.getGlobalBounds();
            phaseTitleText.setPosition({
                bannerBounds.position.x + bannerBounds.size.x / 2.f,
                bannerBounds.position.y + bannerBounds.size.y / 2.f
            });
            window.draw(phaseBannerSprite);
            window.draw(phaseTitleText);
        }

        // REGION DROPDOWN

        if (boardGraphics.has_value())
        {
            boardGraphics->drawRegionUI(window);
        }
        /*
        debugGrid->draw(
            window);
        */
    }

    // EVENT ROUTING

    void GameSessionUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState)
    {   
        // REGION DROPDOWN INTERACTION

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left &&
                boardGraphics.has_value())
            {
                sf::Vector2f mousePosition =
                    window.mapPixelToCoords(mousePressed->position);

                if (boardGraphics->handleRegionClick(mousePosition))
                {
                    return;
                }
            }
        }
        // TERRITORY HOVER

        if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords(mouseMoved->position);
            mousePosition.y -= 15.0f;

            for (auto& [territoryID, territory] : territoryGraphicsMap)
            {
                territory.setHovered(territory.contains(mousePosition));
            }
        }

        // GAME SETUP

        if (gameState.getPhase() ==
            PhaseType::GameSetup)
        {
            if (gameSetupUI.has_value())
            {
                gameSetupUI->handleEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    territoryGraphicsMap);
            }

            return;
        }

        // REINFORCE

        if (gameState.getPhase() ==
            PhaseType::Reinforce)
        {
            if (reinforceUI.has_value())
            {
                reinforceUI->handleReinforceEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    territoryGraphicsMap);
            }
        }

        // ATTACK

        if (gameState.getPhase() ==
            PhaseType::Attack)
        {
            if (attackUI.has_value())
            {
                attackUI->handleAttackEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    playerGraphics,
                    territoryGraphicsMap);
            }
        }

        // FORTIFY

        if (gameState.getPhase() ==
            PhaseType::Fortify)
        {
            if (fortifyUI.has_value())
            {
                fortifyUI->handleFortifyEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    territoryGraphicsMap);
            }
        }
    }

    // SHARED GAME GRAPHICS

    void GameSessionUI::createTerritoryGraphicsMap(
        Map& territoryMap)
    {
        try
        {
            const std::string boardFilename =
                "data/graphics/europe/europe_board.json";

            std::ifstream boardFile(
                boardFilename);

            if (!boardFile.is_open())
            {
                throw std::runtime_error(
                    "Could not open board graphics file: " +
                    boardFilename);
            }

            nlohmann::json boardJson;
            boardFile >> boardJson;

            const auto& boardData =
                boardJson.at("board");

            const auto& territoriesData =
                boardData.at("territories");

            static sf::Font font;

            if (!font.openFromFile(
                "C:/Windows/Fonts/arial.ttf"))
            {
                throw std::runtime_error(
                    "Could not load font");
            }

            territoryGraphicsMap.clear();

            for (const auto& territoryData :
                territoriesData)
            {
                TerritoryID territoryID =
                    stringToTerritoryID(
                        territoryData.at(
                            "territory"
                        ).get<std::string>());

                // TERRITORY POLYGONS

                const auto& polygonsData =
                    territoryData.at("polygons");

                std::vector<
                    std::vector<sf::Vector2f>>
                    vertices;

                for (const auto& polygonData :
                    polygonsData)
                {
                    std::vector<sf::Vector2f>
                        polygonVertices;

                    for (const auto& pointData :
                        polygonData)
                    {
                        sf::Vector2f point(
                            pointData.at(0).get<float>(),
                            pointData.at(1).get<float>());

                        polygonVertices.push_back(
                            point);
                    }

                    vertices.push_back(
                        polygonVertices);
                }

                // DOMAIN TERRITORY

                Territory& territory =
                    territoryMap.getTerritory(
                        territoryID);

                int playerID =
                    territory.getOwnerID();

                RegionID regionID =
                    territory.getRegionID();

                // TERRITORY GRAPHICS DATA

                std::string title =
                    territoryData.at(
                        "territory"
                    ).get<std::string>();

                unsigned int titleCharacterSize =
                    territoryData.at(
                        "title_character_size"
                    ).get<unsigned int>();

                unsigned int troopCharacterSize =
                    territoryData.at(
                        "troop_character_size"
                    ).get<unsigned int>();

                float outlineThickness =
                    territoryData.at(
                        "outline_thickness"
                    ).get<float>();

                // CREATE TERRITORY GRAPHICS
                std::cout << "[DEBUG] Triangulating territory: " << title << std::endl;
                auto [iterator, inserted] =
                    territoryGraphicsMap.emplace(
                        territoryID,
                        TerritoryGraphics(
                            territoryID,
                            regionID,
                            playerID,
                            title,
                            vertices,
                            titleCharacterSize,
                            troopCharacterSize,
                            outlineThickness,
                            font,
                            factionTroopCounters));

                iterator->second.setTroopCount(
                    territory.getTroopCount());
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string(
                    "territory graphics map creation failed: "
                ) +
                exception.what());
        }
    }

    // UI STATE ACCESS

    GameSetupState&
        GameSessionUI::getGameSetupState()
    {
        return gameSetupUI
            ->getGameSetupState();
    }

    BoardGraphics&
        GameSessionUI::getBoardGraphics()
    {
        return boardGraphics.value();
    }

    std::unordered_map<
        TerritoryID,
        TerritoryGraphics
    >& GameSessionUI::getTerritoryGraphics()
    {
        return territoryGraphicsMap;
    }

    std::vector<PlayerGraphics>&
        GameSessionUI::getPlayerGraphics()
    {
        return playerGraphics;
    }

} // namespace european_conquest
