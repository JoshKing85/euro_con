#include "european_conquest/core/session/GameInitializer.h"

#include "european_conquest/world/DeckLoader.h"
#include "european_conquest/world/MapLoader.h"

#include <iostream>

namespace european_conquest {

    // CONSTRUCTOR

    GameInitializer::GameInitializer()
    {
    }

    // INITIALIZE GAME

    std::tuple<Map, std::vector<Player>, Deck>
        GameInitializer::initializeGame(
            std::string& filename,
            int playerNumbers,
            int aiNumbers)
    {
        std::cout
            << "[DEBUG] Initializing game\n";

        // Create map.

        Map map =
            loadMap(filename);

        // Create deck.

        Deck deck =
            createDeck(map);

        // Create players.

        std::vector<Player> players;

        for (int i = 0; i < playerNumbers; ++i)
        {
            players.emplace_back(i);
        }

        // AI player setup is not yet implemented.

        (void)aiNumbers;

        // Initialization summary.

        std::cout
            << "[DEBUG] Game initialized | Players: "
            << players.size()
            << " | Territories: "
            << map.getTerritories().size()
            << '\n';

        return {
            map,
            players,
            deck
        };
    }

    // PLAYER SETUP

    void GameInitializer::updatePlayer(
        Player& player,
        const std::string& name)
    {
        std::cout
            << "[DEBUG] Player "
            << player.getPlayerID()
            << " name updated to: "
            << name
            << '\n';
    }

    // INITIAL TERRITORY DEAL

    void GameInitializer::dealDeck(
        Deck& deck,
        std::vector<Player>& players,
        Map& map,
        GameStateManager& gameStateManager)
    {
        std::cout
            << "[DEBUG] Dealing initial territories\n";

        const int territoryCount =
            static_cast<int>(
                map.getTerritories().size());

        int territoriesDealt = 0;
        int playerIndex = 0;

        while (territoriesDealt < territoryCount)
        {
            Card& card =
                deck.getNextCard(true);

            TerritoryID territoryID =
                card.getTerritoryID().value();

            Player& currentPlayer =
                players[playerIndex];

            // Assign territories in round-robin order through GameStateManager.

            gameStateManager.updateTerritoryOwner(
                territoryID,
                currentPlayer.getPlayerID());

            // Place initial territory troop.

            gameStateManager.updateTerritoryTroopCount(
                territoryID,
                1);

            gameStateManager.updatePlayerTroopCount(
                currentPlayer.getPlayerID(),
                1);

            // Next player.

            ++territoriesDealt;
            ++playerIndex;

            if (playerIndex >=
                static_cast<int>(players.size()))
            {
                playerIndex = 0;
            }
        }

        std::cout
            << "[DEBUG] Territory deal complete | Territories dealt: "
            << territoriesDealt
            << '\n';
    }

} // namespace european_conquest