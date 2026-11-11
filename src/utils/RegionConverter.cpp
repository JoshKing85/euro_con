#include "european_conquest/utils/RegionConverter.h"

#include <stdexcept>

namespace european_conquest
{
    RegionID stringToRegionID(
        const std::string& regionName)
    {
        if (regionName == "BritishIsles")
            return RegionID::BritishIsles;

        if (regionName == "WesternEurope")
            return RegionID::WesternEurope;

        if (regionName == "GermanStates")
            return RegionID::GermanStates;

        if (regionName == "AustrianEmpire")
            return RegionID::AustrianEmpire;

        if (regionName == "ItalianStates")
            return RegionID::ItalianStates;

        if (regionName == "Scandinavia")
            return RegionID::Scandinavia;

        if (regionName == "RussianEmpire")
            return RegionID::RussianEmpire;

        throw std::invalid_argument(
            "Unknown region name: " +
            regionName);
    }
};