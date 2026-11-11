#pragma once

#include "european_conquest/enums.h"
#include "european_conquest/graphics/components/Feature.h"

namespace european_conquest {

// Loads map feature definitions from a file for graphical display.
	std::vector<Feature> loadFeatures(
	const std::string& fileName );
}