#include "european_conquest/world/Deck.h"

#include <stdexcept>

namespace european_conquest {

    Card& Deck::getNextCard(bool initialBuild)
    {
        if (deck.empty())
        {
            throw std::runtime_error("Cannot draw from an empty deck");
        }

        // Wrap the draw position when the end of the deck is reached.
        if (deckCount >= deck.size())
        {
            deckCount = 0;
        }

        // During initial setup, skip wild cards and cycle through territory cards.
        while (initialBuild)
        {
            if (deckCount >= deck.size())
            {
                deckCount = 0;
            }

            if (deck[deckCount].hasTerritory())
            {
                return deck[deckCount++];
            }

            deckCount++;
        }

        return deck[deckCount++];
    }

    void Deck::addDeck(const std::vector<Card>& newDeck)
    {
        deck = newDeck;
        deckCount = 0;
    }

}