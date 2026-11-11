#pragma once

namespace european_conquest {
	// Checks whether the requested troop count is valid for the available pool.
	bool isTroopCountValid(int troopCount, int TroopPool);
}