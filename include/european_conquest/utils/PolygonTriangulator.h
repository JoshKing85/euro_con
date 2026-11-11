#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
namespace european_conquest {

	// Converts polygon vertices into triangles for rendering.
	std::vector<sf::Vertex> polyTri(const std::vector<sf::Vector2f> &vertices);

}