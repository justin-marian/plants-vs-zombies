#include "GameConstants.h"
#include "ObjectsGame.h"

#include "Plants.h"

#include <iostream>


/// <summary>
/// Constructor for creating a Plant object with specified properties.
/// </summary>
/// <param name="mesh">A pointer to the Mesh representing the plant's visual appearance.</param>
/// <param name="name">The name of the Plant.</param>
/// <param name="position">The position of the Plant in 3D space.</param>
/// <param name="color">The color of the Plant.</param>
/// <param name="radius">The radius of the Plant's circular shape.</param>
/// <param name="numTriangles">The number of triangles used to create the plant's shape.</param>
/// <param name="innerLength">The inner length of the Plant's shape.</param>
/// <param name="outerLength">The outer length of the Plant's shape.</param>
/// <param name="row">The row index of the Plant in a grid or layout.</param>
/// <param name="col">The column index of the Plant in a grid or layout.</param>
/// <param name="cost">The cost associated with the Plant.</param>
Plant::Plant(Mesh* mesh, const std::string& name, const glm::vec3& position,
    const glm::vec3& color, float radius, int numTriangles,
    float innerLength, float outerLength, int row, int col, int cost)
    : mesh(mesh), name(name), position(position), color(color), radius(radius),
    numTriangles(numTriangles), innerLength(innerLength), outerLength(outerLength),
    shootCooldown(5.0f), shootTimer(0.0f), row(row), col(col), cost(cost)
    { /* Constructor initializes a Plant with given properties */ }
Plant::~Plant() {}


/// <summary>
/// Check if the mouse is over this plant.
/// </summary>
/// <param name="worldMouseX">X coordinate of the mouse in the world space.</param>
/// <param name="worldMouseY">Y coordinate of the mouse in the world space.</param>
/// <returns>True if the mouse is over the plant, false otherwise.</returns>
bool Plant::IsMouseOver(float worldMouseX, float worldMouseY) const
{
    float dx = worldMouseX - position.x;
    float dy = worldMouseY - position.y;
    float distanceSquared = dx * dx + dy * dy;
    return distanceSquared <= (radius * radius);
}


// Getters & Setters for plants properties

/* PROBLEM COME FROM HERE AT DRAG & DROP INVENTORY PLANTS */
void    Plant::SetPosition(const glm::vec2& newPosition)    { this->position = newPosition; }
// Getter for the row grid index.
int             Plant::GetRow() const                       { return row; }
// Setter for the row grid index.
void            Plant::SetRow(int row)                      { this->row = row; }
// Getter for the column grid index.
int             Plant::GetColumn() const                    { return col; }
// Setter for the column grid index.
void            Plant::SetColumn(int col)                   { this->col = col; }
// Getter for the cost to buy the plant.
int             Plant::GetCost() const                      { return cost; }
// Setter for the cost to buy the plant.
void            Plant::SetCost(int cost)                    { this->cost = cost; }
// Getter for the mesh associated with the plant.
Mesh*           Plant::GetMesh() const                      { return mesh; }
// Getter for the name of the plant.
std::string     Plant::GetName() const                      { return name; }
// Setter for the name of the plant.
void            Plant::SetName(std::string name)            { this->name = name; }
// Getter for the position of the plant in 2D space.
glm::vec2       Plant::GetPosition() const                  { return position; }
// Setter for the mesh associated with the plant.
void            Plant::SetMesh(Mesh* mesh)                  { this->mesh = mesh; }
// Getter for the color of the plant.
glm::vec3       Plant::GetColor() const                     { return color; }
// Getter for the outer length of the plant's shape.
float           Plant::GetLength() const                    { return outerLength; }
// Getter for the scale factor of the plant.
float           Plant::GetScale() const                     { return scale; }
// Setter for the scale factor of the plant.
void            Plant::SetScale(float scale)                { this->scale = scale; }
// Update the shoot timer for the plant.
void            Plant::UpdateShootTimer(float deltaTime)    { shootTimer += deltaTime; }
// Reset the shoot timer for the plant.
void            Plant::ResetShootTimer()                    { shootTimer = 0.0f; }
// Check if the plant is currently active.
bool            Plant::IsActive() const                     { return active; }
// Set the active status of the plant.
void            Plant::SetActive(bool active)               { this->active = active; }
