#pragma once

#ifndef GREEN_SQUARES_H
#define GREEN_SQUARES_H

#include <glm/glm.hpp>

#include <string>

class Mesh;

class GreenSquare 
{
public:
    // Constructor for GreenSquare.
    GreenSquare(const std::string& name, Mesh* mesh, 
                const glm::vec2& position, bool occupied,
                float sideLength, int row, int col);
    ~GreenSquare();

    // Mouse interaction method.
    bool IsMouseOverGS(float worldMouseX, float worldMouseY) const;
    bool ContainsPlantAt(const glm::vec2& plantPos) const;

    // (NOT) OCCUPIED.
    bool IsFree() const;
    void Occupy();
    bool IsOccupied() const;
    void SetOccupied(bool occupied);

    // Position and mesh methods.
    glm::vec2 GetCenterPosition() const;
    const std::string& GetName() const;
    Mesh* GetMesh() const;
    const glm::vec2& GetPosition() const;
    float GetSideLength() const;

    // Grid location methods.
    const int GetRow() const;
    void SetRow(int row);
    const int GetCol() const;
    void SetCol(int col);

private:
    std::string name;
    Mesh* mesh;
    glm::vec2 position;    

    bool occupied;           // Flag to indicate whether the square is occupied.

    float sideLength;        // The length of the sides of the square.
    int row;                 // The row index of the square in a grid layout.
    int col;                 // The column index of the square in a grid layout.
};

#endif // GREEN_SQUARES_H
