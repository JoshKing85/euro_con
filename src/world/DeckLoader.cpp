#include "european_conquest/world/DeckLoader.h"

#include <algorithm>
#include <random>
#include <vector>

namespace european_conquest {

    Deck createDeck(const Map& map)
    {
        Deck deck;

        std::vector<Card> tempDeck;

        int infantryCount = 0;
        int cavalryCount = 0;
        int artilleryCount = 0;

        // CREATE TERRITORY CARDS

        // Assign card types in sequence before shuffling the completed deck.
        for (const auto& territoryPair :
            map.getTerritories())
        {
            const Territory& territory =
                territoryPair.second;

            CardType cardType;

            if (infantryCount < 14)
            {
                cardType =
                    CardType::Infantry;

                ++infantryCount;
            }
            else if (cavalryCount < 14)
            {
                cardType =
                    CardType::Cavalry;

                ++cavalryCount;
            }
            else
            {
                cardType =
                    CardType::Artillery;

                ++artilleryCount;
            }

            tempDeck.emplace_back(
                cardType,
                territory.getID(),
                territory.getRegionID()
            );
        }

        // ADD WILD CARDS

        for (int i = 0; i < 4; ++i)
        {
            tempDeck.emplace_back(
                CardType::Wild
            );
        }

        // SHUFFLE DECK

        // Randomise draw order after adding territory and wild cards.
        std::random_device rd;
        std::mt19937 generator(rd());

        std::shuffle(
            tempDeck.begin(),
            tempDeck.end(),
            generator
        );

        // STORE CARDS IN DECK

        deck.addDeck(tempDeck);

        return deck;
    }

} // namespace european_conquest