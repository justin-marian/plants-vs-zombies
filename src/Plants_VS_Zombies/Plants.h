#pragma once

#ifndef PLANTS_H
#define PLANTS_H

#include <glm/glm.hpp>

#include <string>


class Mesh;
class Projectile;

class Plant 
{
public:
    // Constructor for Plants
    Plant(Mesh* mesh, const std::string& name, const glm::vec3& position,
            const glm::vec3& color, float radius, int numTriangles,
            float innerLength, float outerLength,
            int row, int col, int cost);
    ~Plant();

    bool IsMouseOver(float worldMouseX, float worldMouseY) const;

    void UpdateShootTimer(float deltaTime);
    bool CanShoot() const { return shootTimer >= shootCooldown; }
    void ResetShootTimer();

    // Getters
    bool IsActive() const;
    std::string GetName() const;
    Mesh* GetMesh() const;
    glm::vec2 GetPosition() const;
    glm::vec3 GetColor() const;
    float GetLength() const;
    float GetScale() const;
    int GetRow() const;
    int GetColumn() const;
    int GetCost() const;

    bool IsPlaced() const { return placed; }
    float GetShootCooldown() const { return shootCooldown; }

    // Setters
    void SetActive(bool newActive);
    void SetName(std::string name);
    void SetMesh(Mesh* newMesh);
    void SetPosition(const glm::vec2& position);
    void SetScale(float newScale);
    void SetRow(int row);
    void SetColumn(int col);
    void SetCost(int cost);

    void SetPlaced(bool state) { placed = state; }
    void SetShootCooldown(float cooldown) { shootCooldown = cooldown; }

private:
    Mesh* mesh;
    std::string name;
    glm::vec2 position;
    glm::vec3 color;

    float radius;
    int numTriangles;
    float innerLength;
    float outerLength;

    int row;              // Green row where plant is placed
    int col;              // Green col where plant is placed
    int cost;             // Cost to buy a plant from inventory

    float shootCooldown;  // Time interval between projectile generations
    float shootTimer;     // Timer to track time since last projectile
    float scale = 1;

    bool placed = false;  // By default, a plant is not placed
    bool active = true;   // By default, a plant is active
};

#endif // PLANTS_H
