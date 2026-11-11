#pragma once

#include "european_conquest/enums.h"
#include "european_conquest/entities/Card.h"
#include <vector>

namespace european_conquest {

	// Identifies a valid card set, returning its type when one exists.

	std::optional<SetType> validateSet(const std::vector<Card> &cards);
}

