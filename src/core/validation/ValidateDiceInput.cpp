#include "european_conquest/core/validation/ValidateDiceInput.h"

namespace european_conquest {

    bool isValidDiceInput(
        int diceInput,
        int territoryTroopCount
    )
    {
        if (
            (territoryTroopCount - 1 >= diceInput) &&
            (diceInput >= 1 && diceInput <= 3)
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace european_conquest