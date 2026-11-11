#include "european_conquest/entities/Card.h"

namespace european_conquest
{

    Card::Card(
        CardType cardType,
        std::optional<TerritoryID> territoryID,
        std::optional<RegionID> regionID
    )
        : cardType(cardType),
        territoryID(territoryID),
        regionID(regionID)
    {
    }

    // GETTERS

    CardType Card::getCardType() const
    {
        return cardType;
    }

    bool Card::hasTerritory() const
    {
        return territoryID.has_value();
    }

    std::optional<TerritoryID> Card::getTerritoryID() const
    {
        return territoryID;
    }

    std::optional<RegionID> Card::getRegionID() const
    {
        return regionID;
	}

}