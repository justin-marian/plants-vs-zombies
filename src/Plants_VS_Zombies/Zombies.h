#pragma once

#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <glm/glm.hpp>

#include "Plants.h"
#include "Projectiles.h"

#include <string>
#include <vector>


class Mesh;

class Zombie 
{
public:
    // Constructor for Zombies
    Zombie(const std::string& name, Mesh* mesh, glm::vec2 position,
            float scale, float inRadius, float outRadius,
            glm::vec3 color, float speed, int row);
    ~Zombie();

    // Zombie position is changing based on its speed & the elapsed time.
    void Move(float deltaTime);
    // Zombie is hit by a projectile.
    void Hit();
    // Zombie has been destroyed, hit by 3 times.
    bool IsDestroyed() const;

    // Determine if a new zombie should be spawned.
    static bool ShouldSpawnZombie(float deltaTime);
    // Spawn a zombie at a specific row.
    static void SpawnZombieAtRow(int row, const glm::ivec2& resolution, std::vector<Zombie>& zombies);
    // Spawn zombies at random rows.
    static void SpawnRandomZombies(float deltaTimeSeconds, const glm::ivec2& resolution, std::vector<Zombie>& zombies);

    // Collision detection methods
    bool IsIntersectingWithRectangle(const glm::vec2& corner, float widthR, float heightR) const;
    bool IsCollidingWithProjectile(const Projectile& projectile) const;
    bool IsCollidingWithPlant(const Plant& plant) const;

    // Getters
    glm::vec2 GetPosition() const;
    glm::vec3 GetColor() const;
    Mesh* GetMesh() const;
    float GetScale() const;
    float GetOutRadius() const;
    std::string GetName() const;
    bool IsActive() const;
    int GetRow() const;
    int GetHitCount() const;

    // Setters
    void SetScale(float newScale);
    void SetMesh(Mesh* newMesh);
    void SetActive(bool isActive);
    void SetRow(int row);

private:
    std::string name;
    Mesh* mesh;
    glm::vec2 position;
    glm::vec3 color;

    int row;                 // Row where the zombie is located
        
    int hitCount = 0;        // Number of times the zombie has been hit
    float scale =  1;        // Scale of the zombie
        
    float speed;             // Movement speed of the zombie
    bool isActive;           // Flag to check if the zombie is active

    float innerRadius;       // Inner radius for collision detection
    float outerRadius;       // Outer radius for collision detection

    static float spawnTimer; // Timer for controlling zombie spawn
};

#endif // ZOMBIES_H
