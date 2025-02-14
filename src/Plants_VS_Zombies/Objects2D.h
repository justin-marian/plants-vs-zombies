#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Objects2D
{
    /// <summary>
    /// Create a square mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="leftBottomCorner">Coordinates of the square's bottom-left corner.</param>
    /// <param name="length">Length of the square's sides.</param>
    /// <param name="color">Color of the square.</param>
    /// <param name="fill">Determines whether the square is filled (true) or just an outline (false).</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateSquare(const std::string& name,
                       glm::vec3 leftBottomCorner, float length,
                       const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create a rectangular mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="leftBottomCorner">Coordinates of the rectangle's bottom-left corner.</param>
    /// <param name="width">Width of the rectangle.</param>
    /// <param name="height">Height of the rectangle.</param>
    /// <param name="color">Color of the rectangle.</param>
    /// <param name="fill">Determines whether the rectangle is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateRectangle(const std::string& name,
                          glm::vec3 leftBottomCorner, float width, float height,
                          const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create a triangular mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="leftBottomCorner">Coordinates of the triangle's bottom-left corner.</param>
    /// <param name="rightBottomCorner">Coordinates of the triangle's bottom-right corner.</param>
    /// <param name="upCorner">Coordinates of the triangle's top corner.</param>
    /// <param name="color">Color of the triangle.</param>
    /// <param name="fill">Determines whether the triangle is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateTriangle(const std::string& name,
                         glm::vec3 leftBottomCorner, glm::vec3 rightBottomCorner, glm::vec3 upCorner,
                         const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create an isosceles triangular mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="vertex">Coordinates of the triangle's top vertex.</param>
    /// <param name="width">Width of the triangle's base.</param>
    /// <param name="height">Height of the triangle.</param>
    /// <param name="color">Color of the triangle.</param>
    /// <param name="fill">Determines whether the triangle is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateIsoscelesTriangle(const std::string& name,
                                  glm::vec3 vertex, float width, float height,
                                  const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create an equilateral triangular mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="vertex">Coordinates of the triangle's top vertex.</param>
    /// <param name="length">Length of each side of the triangle.</param>
    /// <param name="color">Color of the triangle.</param>
    /// <param name="fill">Determines whether the triangle is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateEquilateralTriangle(const std::string& name,
                                    glm::vec3 vertex, float length,
                                    const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create a rhombus mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="leftBottomCorner">Coordinates of the rhombus's bottom-left corner.</param>
    /// <param name="length">Length of each side of the rhombus.</param>
    /// <param name="color">Color of the rhombus.</param>
    /// <param name="fill">Determines whether the rhombus is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateRhombus(const std::string& name,
                        glm::vec3 leftBottomCorner, float length,
                        const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create a circle mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="center">Coordinates of the circle's center.</param>
    /// <param name="numSegments">Number of segments used to render the circle.</param>
    /// <param name="radius">Radius of the circle.</param>
    /// <param name="color">Color of the circle.</param>
    /// <param name="fill">Determines whether the circle is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateCircle(const std::string& name,
                        glm::vec3 center, float numSegments, float radius,
                        const glm::vec3& color, bool fill = true);


    /// <summary>
    /// Create a hexagon mesh with specified properties.
    /// </summary>
    /// <param name="name">Unique identifier for the mesh.</param>
    /// <param name="center">Coordinates of the hexagon's center.</param>
    /// <param name="radius">Distance from the center to each corner of the hexagon.</param>
    /// <param name="color">Color of the hexagon.</param>
    /// <param name="fill">Determines whether the hexagon is filled or just an outline.</param>
    /// <returns>A pointer to the created Mesh object.</returns>
    Mesh* CreateHexagon(const std::string& name,
                        glm::vec3 center, float radius,
                        const glm::vec3& color, bool fill = true);

} // namespace Objects2D
