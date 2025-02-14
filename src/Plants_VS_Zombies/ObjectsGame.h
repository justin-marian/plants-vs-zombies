#pragma once

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

#include <string>


namespace ObjectsGame
{
	/// <summary>
	/// Create a Mesh representing a "SUN" (PointScores) with specified attributes.
	/// </summary>
	/// <param name="name">The unique name for the Mesh.</param>
	/// <param name="radius">The radius of the sun.</param>
	/// <param name="segments">The number of segments in the sun.</param>
	/// <param name="raySegments">The number of ray segments in the sun.</param>
	/// <param name="rayBigger">The length of the bigger rays.</param>
	/// <param name="raySmaller">The length of the smaller rays.</param>
	/// <param name="color">The color of the sun.</param>
	/// <param name="fill">Set to true to create a filled sun, false for outline.</param>
	/// <returns>A pointer to the created Mesh.</returns>
	Mesh* CreatePointScore(const std::string& name,
						   float radius,
						   int segments, int raySegments,
						   float rayBigger, float raySmaller,
						   const glm::vec3 color, bool fill = true);


	/// <summary>
	/// Create a Mesh representing a "HEART" (Health) with specified attributes.
	/// https://blogs.lcps.org/academiesonline/2021/02/13/the-equation-of-the-heart/
	/// </summary>
	/// <param name="name">The unique name for the Mesh.</param>
	/// <param name="scale">The scale factor for the heart.</param>
	/// <param name="segments">The number of segments in the heart.</param>
	/// <param name="color">The color of the heart.</param>
	/// <param name="fill">Set to true to create a filled heart, false for outline.</param>
	/// <returns>A pointer to the created Mesh.</returns>
	Mesh* CreateHearth(const std::string& name,
					   float scale, int segments,
					   const glm::vec3 color, bool fill = true);


	/// <summary>
	/// Create a Mesh representing a "CHATTERBOX - STAR" (Projectile) with specified attributes.
	/// </summary>
	/// <param name="name">The unique name for the Mesh.</param>
	/// <param name="segments">The number of segments in the star.</param>
	/// <param name="longerSide">The length of the longer side of the star.</param>
	/// <param name="shorterSide">The length of the shorter side of the star.</param>
	/// <param name="color">The color of the star.</param>
	/// <param name="fill">Set to true to create a filled star, false for outline.</param>
	/// <returns>A pointer to the created Mesh.</returns>
	Mesh* CreateProjectile(const std::string& name,
						   int segments,
						   float longerSide, float shorterSide,
						   const glm::vec3 color, bool fill = true);


	/// <summary>
	/// Create a Mesh representing a "RHOMBUSES WITH A CENTER POINT" (Plants) with specified attributes.
	/// </summary>
	/// <param name="name">The unique name for the Mesh.</param>
	/// <param name="radius">The radius of the plant.</param>
	/// <param name="numTriangles">The number of triangles in the plant.</param>
	/// <param name="innerLength">The inner length of the triangles.</param>
	/// <param name="outerLength">The outer length of the triangles.</param>
	/// <param name="color">The color of the plant.</param>
	/// <param name="fill">Set to true to create a filled plant, false for outline.</param>
	/// <returns>A pointer to the created Mesh.</returns>
	Mesh* CreatePlant(const std::string& name,
					  float radius,
					  int numTriangles,
					  float innerLength, float outerLength,
					  const glm::vec3 color, bool fill = true);


	/// <summary>
	/// Create a Mesh representing a "2 HEXAGONS WITH SAME CENTER" (Zombies) with specified attributes.
	/// </summary>
	/// <param name="name">The unique name for the Mesh.</param>
	/// <param name="innerRadius">The inner radius of the zombie.</param>
	/// <param name="outerRadius">The outer radius of the zombie.</param>
	/// <param name="color">The color of the zombie.</param>
	/// <param name="fill">Set to true to create a filled zombie, false for outline.</param>
	/// <returns>A pointer to the created Mesh.</returns>
	Mesh* CreateZombie(const std::string& name,
					   float innerRadius, float outerRadius,
					   const glm::vec3 color, bool fill = true);

	
	/// <summary>
	/// Create a Mesh representing "7 SQUARES AND 1 RECTANGLE" (Inventory) with specified attributes.
	/// </summary>
	/// <param name="name">The unique name for the Mesh.</param>
	/// <param name="leftBottomCorner">The position of the bottom-left corner of the inventory slot.</param>
	/// <param name="width">The width of the inventory slot.</param>
	/// <param name="height">The height of the inventory slot.</param>
	/// <param name="fillColor">The fill color of the inventory slot.</param>
	/// <param name="fill">Set to true to create a filled inventory slot, false for outline.</param>
	/// <returns>A pointer to the created Mesh.</returns>
	Mesh* CreateInventory(const std::string& name,
						  glm::vec3 leftBottomCorner,
						  float width, float height,
						  const glm::vec3 color, bool fill = true);

} // namespace ObjectsGame
