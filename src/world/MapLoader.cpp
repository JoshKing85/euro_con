#include "european_conquest/world/MapLoader.h"

#include "european_conquest/utils/RegionConverter.h"
#include "european_conquest/utils/TerritoryConverter.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace european_conquest {

    Map loadMap(const std::string& filename)
    {
        Map map;

        std::cout
            << "[DEBUG] Loading map file: "
            << filename
            << '\n';

        std::ifstream file(filename);

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Could not open map file: " +
                filename);
        }

        json mapData;
        file >> mapData;

        // REGIONS

        // Each region entry defines its bonus, member territories and borders.
        for (const auto& regionData :
            mapData.at("regions"))
        {
            std::string regionName =
                regionData.at("cont_id")
                .get<std::string>();

            RegionID regionID =
                stringToRegionID(
                    regionName);

            int bonus =
                regionData.at("bonus")
                .get<int>();

            std::vector<TerritoryID>
                regionTerritories;

            std::vector<TerritoryID>
                borderTerritories;

            // BORDER TERRITORIES

            // Convert border territory names to IDs for region boundary data.
            for (const auto& borderTerritory :
                regionData.at(
                    "border_territories"))
            {
                borderTerritories.push_back(
                    stringToTerritoryID(
                        borderTerritory
                        .get<std::string>()));
            }

            // TERRITORIES

            for (const auto& territoryData :
                regionData.at("territories"))
            {
                std::string territoryName =
                    territoryData.at("id")
                    .get<std::string>();

                TerritoryID territoryID =
                    stringToTerritoryID(
                        territoryName);

                regionTerritories.push_back(
                    territoryID);

                std::vector<TerritoryID>
                    adjacentTerritories;

                // ADJACENT TERRITORIES

                // Convert neighbour names into the territory adjacency list.
                for (const auto& neighbour :
                    territoryData.at("neighbors"))
                {
                    adjacentTerritories.push_back(
                        stringToTerritoryID(
                            neighbour
                            .get<std::string>()));
                }

                Territory territory(
                    territoryID,
                    regionID,
                    adjacentTerritories);

                map.addTerritory(
                    territory);
            }

            // REGION

            // Register the region after its territories have been added.
            Region region(
                regionID,
                bonus,
                regionTerritories,
                borderTerritories);

            map.addRegion(
                region);
        }

        return map;
    }

} // namespace european_conquest