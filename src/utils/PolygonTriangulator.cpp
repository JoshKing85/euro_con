
#include "european_conquest/utils/PolygonTriangulator.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace european_conquest
{

std::vector<sf::Vertex> polyTri(const std::vector<sf::Vector2f>& vertices)
{
    std::vector<sf::Vertex> triangles;

    if (vertices.size() < 3)
    {
        return triangles;
    }

    // Remove repeated adjacent points and a duplicated closing point.
    // These would create degenerate triangles during ear clipping.

    std::vector<sf::Vector2f> points;

    for (const auto& point : vertices)
    {
        if (points.empty() || points.back() != point)
        {
            points.push_back(point);
        }
    }

    if (points.size() > 1)
    {
        if (points.front() == points.back())
        {
            points.pop_back();
        }
    }

    if (points.size() < 3)
    {
        return triangles;
    }

    // Calculate signed area to determine vertex winding.
    // A near-zero area indicates a degenerate polygon.

    double signedArea = 0.0;

    for (std::size_t i = 0; i < points.size(); i++)
    {
        const auto& a = points[i];
        const auto& b = points[(i + 1) % points.size()];

        signedArea += static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
    }

    if (std::abs(signedArea) < 0.00000001)
    {
        throw std::runtime_error("polyTri: polygon has no area");
    }

    // Normalise the working vertex order so convex corners have positive cross products.
    // Indices allow ears to be removed without changing the original points.

    std::vector<std::size_t> indices(points.size());

    for (std::size_t i = 0; i < points.size(); i++)
    {
        indices[i] = i;
    }

    if (signedArea < 0.0)
    {
        std::reverse(indices.begin(), indices.end());
    }

    // The cross product indicates which side of a directed edge a point lies on.

    auto cross = [](
        const sf::Vector2f& a, 
        const sf::Vector2f& b, 
        const sf::Vector2f& c) -> double
    {
        return static_cast<double>(b.x - a.x) * (c.y - a.y) -
               static_cast<double>(b.y - a.y) * (c.x - a.x);
    };

    // For the normalised winding, a point lies inside or on the triangle
    // when it is on the positive side of all three edges.

    auto pointInTriangle = [&](const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b,
                               const sf::Vector2f& c) -> bool
    { return cross(a, b, p) >= 0.0 && cross(b, c, p) >= 0.0 && cross(c, a, p) >= 0.0; };

    // EAR-CLIPPING TRIANGULATION


    // Repeatedly find a convex triangle containing no other polygon vertex.
    // Emit that triangle, then remove its middle vertex from the working polygon.

    while (indices.size() > 3)
    {
        bool earFound = false;

        for (std::size_t i = 0; i < indices.size(); ++i)
        {
            // Use neighbouring indices to form a candidate ear at vertex B.

            std::size_t prev = (i + indices.size() - 1) % indices.size();

            std::size_t curr = i;

            std::size_t next = (i + 1) % indices.size();

            const sf::Vector2f& a = points[indices[prev]];

            const sf::Vector2f& b = points[indices[curr]];

            const sf::Vector2f& c = points[indices[next]];

            // Reject reflex or collinear corners; only convex corners can form ears.

            if (cross(a, b, c) <= 0.0)
            {
                continue;
            }

            // An ear cannot contain any other remaining polygon vertex.

            bool containsVertex = false;

            for (std::size_t j = 0; j < indices.size(); ++j)
            {
                if (j == prev || j == curr || j == next)
                {
                    continue;
                }

                const sf::Vector2f& p = points[indices[j]];

                if (pointInTriangle(p, a, b, c))
                {
                    containsVertex = true;
                    break;
                }
            }

            if (containsVertex)
            {
                continue;
            }

            // Emit the valid ear as three SFML vertices.

            triangles.push_back(sf::Vertex{a, sf::Color::White});

            triangles.push_back(sf::Vertex{b, sf::Color::White});

            triangles.push_back(sf::Vertex{c, sf::Color::White});

            // Removing B leaves a smaller polygon for the next iteration.

            indices.erase(indices.begin() + curr);

            earFound = true;
            break;
        }

        // If no ear exists, report the remaining points and stop rather than loop forever.

        // Invalid or numerically problematic polygon geometry can cause this.

        if (!earFound)
        {
            std::cerr << "\n[polyTri] Failed with " << indices.size() << " vertices remaining:\n";

            for (std::size_t i = 0; i < indices.size(); ++i)
            {
                const sf::Vector2f& p = points[indices[i]];

                std::cerr << i << ": (" << p.x << ", " << p.y << ")\n";
            }

            throw std::runtime_error("polyTri: unable to find a valid ear");
        }
    }

    // The last three vertices already form the final triangle.

    const sf::Vector2f& a = points[indices[0]];

    const sf::Vector2f& b = points[indices[1]];

    const sf::Vector2f& c = points[indices[2]];

    triangles.push_back(sf::Vertex{a, sf::Color::White});

    triangles.push_back(sf::Vertex{b, sf::Color::White});

    triangles.push_back(sf::Vertex{c, sf::Color::White});

    return triangles;
}

}  // namespace european_conquest
