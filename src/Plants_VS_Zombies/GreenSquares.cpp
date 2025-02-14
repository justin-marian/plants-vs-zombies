#include "GreenSquares.h"

#include <string>


/// <summary>
/// Constructor for creating a GreenSquare object with specified properties.
/// </summary>
/// <param name="name">The name of the GreenSquare.</param>
/// <param name="mesh">A pointer to the Mesh representing the square's visual appearance.</param>
/// <param name="position">The position of the GreenSquare.</param>
/// <param name="occupied">A boolean flag indicating whether the square is occupied.</param>
/// <param name="sideLength">The length of each side of the square.</param>
/// <param name="row">The row index of the square in a grid or layout.</param>
/// <param name="col">The column index of the square in a grid or layout.</param>
GreenSquare::GreenSquare(const std::string& name, Mesh* mesh,
                         const glm::vec2& position, bool occupied, 
                         float sideLength, int row, int col) : 
                         name(name), mesh(mesh),
                         position(position), occupied(occupied),
                         sideLength(sideLength), row(row), col(col)
                         { /* Constructor initializes a GreenSquare with given properties */ }
GreenSquare::~GreenSquare() {}


/// <summary>
/// Check if the mouse is over this green square.
/// </summary>
/// <param name="worldMouseX">X coordinate of the mouse in the world space.</param>
/// <param name="worldMouseY">Y coordinate of the mouse in the world space.</param>
/// <returns>True if the mouse is over the square, false otherwise.</returns>
bool GreenSquare::IsMouseOverGS(float worldMouseX, float worldMouseY) const /* PROBLEM CAN COME FROM HERE AT DRAG & DROP INVENTORY PLANTS */
{
    glm::vec2 center = GetCenterPosition();
    float halfW  = this->sideLength / 2;
    float halfH = this->sideLength / 2;
    return  (worldMouseX >= center.x - halfW && worldMouseX <= center.x + halfW) &&
            (worldMouseY >= center.y - halfH && worldMouseY <= center.y + halfH);
}

/// <summary>
/// Check if a square contains a plant inside of it.
/// </summary>
/// <param name="plantPos">Coordonates of the plant in 2D space.</param>
/// <returns>True if the plant is inside of the square, false othewise.</returns>
bool GreenSquare::ContainsPlantAt(const glm::vec2& plantPos) const
{
    float tolerance = 1.f;
    return glm::abs(plantPos.x - position.x) < tolerance && glm::abs(plantPos.y - position.y) < tolerance;
}

// Getters & Setters for green square properties

// Getter the center associated with the green square.
glm::vec2               GreenSquare::GetCenterPosition() const
{ 
    return glm::vec2(position.x + sideLength / 2.0f,
                     position.y + sideLength / 2.0f); 
}

// Determine if the square is not occupied.
bool                    GreenSquare::IsFree() const                 { return !occupied; }
// Check if the square is currently occupied.
bool                    GreenSquare::IsOccupied() const             { return occupied; }
// Setter the occupied status of the square.
void                    GreenSquare::SetOccupied(bool occupied)     { this->occupied = occupied; }
// Mark the square as occupied.
void                    GreenSquare::Occupy()                       { this->occupied = true; }
// Getter the name of the square.
const std::string&      GreenSquare::GetName() const                { return name; }
// Getter the mesh associated with the square.
Mesh*                   GreenSquare::GetMesh() const                { return mesh; }
// Getter the position of the square in the world space.
const glm::vec2&        GreenSquare::GetPosition() const            { return position; }
// Getter the side length of the square.
float                   GreenSquare::GetSideLength() const          { return sideLength; }
// Getter the row index of the green square in a grid.
const int               GreenSquare::GetRow() const                 { return row; }
// Setter the row index of the green square in a grid.
void                    GreenSquare::SetRow(int row)                { this->row = row; }
// Getter the column index of the green square in a grid.
const int               GreenSquare::GetCol() const                 { return col; }
// Setter the column index of the green square in a grid.
void                    GreenSquare::SetCol(int col)                { this->col = col; }
