#pragma once

#include "european_conquest/entities/Card.h"
#include "european_conquest/enums.h"

#include <vector>

namespace european_conquest{

	/** Maintains the card collection and supplies cards for gameplay. */
class Deck {

	private:
		
		std::vector<Card> deck;
          int deckCount = 0;

	public:

		Card &getNextCard(bool initialBuild = false);
		void addDeck(const std::vector<Card>& newDeck);

        };
}
