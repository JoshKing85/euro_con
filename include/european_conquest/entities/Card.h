#pragma once

#include "european_conquest/enums.h"

#include <optional>

namespace european_conquest {
/** Represents a game card used in reinforcement sets. */
class Card {
private:
  CardType cardType;
  std::optional<TerritoryID> territoryID;
  std::optional<RegionID> regionID;

public:
  Card(CardType cardType,
       std::optional<TerritoryID> territoryID = std::nullopt,
       std::optional<RegionID> regionID = std::nullopt
  );

  CardType getCardType() const;

  bool hasTerritory() const;


  std::optional<TerritoryID> getTerritoryID() const;
  std::optional<RegionID> getRegionID() const;
};
} // namespace european_conquest