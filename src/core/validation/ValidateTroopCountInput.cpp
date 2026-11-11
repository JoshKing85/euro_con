#include "european_conquest/core/validation/ValidateTroopCountInput.h"

namespace european_conquest {

    bool isTroopCountValid(int troopCount, int troopPool) {
        if (troopCount <= troopPool && troopCount > 0) {
            return true;
        }
        return false;
    }
}

