#include "european_conquest/world/FeatureLoader.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "european_conquest/graphics/components/Feature.h"

using json = nlohmann::json;

namespace european_conquest
{

std::vector<Feature> loadFeatures(const std::string& fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open feature file " + fileName);
    }

    json featureData;

    file >> featureData;

    std::vector<Feature> features;

    for (const auto& item : featureData["features"])
    {
        Feature feature;

        feature.name = item["name"].get<std::string>();

        std::string type = item["featureType"].get<std::string>();

        // Convert JSON feature names into the domain feature type.
        if (type == "River")
        {
            feature.featureType = FeatureType::River;
        }
        else if (type == "Mountain")
        {
            feature.featureType = FeatureType::Mountain;
        }
        else if (type == "Forest")
        {
            feature.featureType = FeatureType::Forest;
        }
        else
        {
            throw std::runtime_error("Unknown feature type: " + type);
        }

        // MAIN FEATURE VERTICES

        for (const auto& point : item["vertices"])
        {
            feature.vertices.emplace_back(point[0].get<float>(), point[1].get<float>());
        }

        // OPTIONAL RIVER TRIBUTARIES

        // Tributaries are optional and are only loaded for river features.
        if (feature.featureType == FeatureType::River && item.contains("tributaries"))
        {
            for (const auto& branch : item["tributaries"])
            {
                std::vector<sf::Vector2f> tributary;

                for (const auto& point : branch)
                {
                    tributary.emplace_back(point[0].get<float>(), point[1].get<float>());
                }

                feature.tributaries.push_back(std::move(tributary));
            }
        }

        features.push_back(std::move(feature));
    }

    return features;
}

}  // namespace european_conquest