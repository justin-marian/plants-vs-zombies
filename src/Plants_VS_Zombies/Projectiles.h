#pragma once

#ifndef PROJECTILES_H
#define PROJECTILES_H

#include <glm/glm.hpp>

#include <string>


class Mesh;

class Projectile 
{
public:
    // Constructor for Projectiles.
    Projectile(Mesh* mesh, const glm::vec3& color, float longerSideLength,
        float shorterSideLength, int numSegments, const std::string& name,
        const glm::vec2& position, float rotation, bool isActive, float speed);
    ~Projectile();

    // Move the projectile based on the current speed and deltaTime.
    void Move(float deltaTime, const glm::ivec2& resolution);

    // Getters.
    std::string GetName() const;
    Mesh* GetMesh() const;
    glm::vec3 GetColor() const;

    float GetLongerSideLength() const;
    float GetShorterSideLength() const;

    glm::vec2 GetPosition() const;
    bool IsActive() const;
    float GetSpeed() const;
    float GetRotation() const;

    // Setters.
    void SetPosition(const glm::vec2& newPosition);
    void SetActive(bool active);
    void SetSpeed(float newSpeed);
    void SetRotation(float newRotation);

private:
    Mesh* mesh;  
    std::string name;
    glm::vec2 position;
    glm::vec3 color;      

    float longerSideLength;     // Length of the longer side of the projectile's bounding rectangle.
    float shorterSideLength;    // Length of the shorter side of the projectile's bounding rectangle.
    int numSegments;            // The number of segments used to create the projectile's mesh.

    float rotation;             // The rotation angle (in degrees) of the projectile.
    bool isActive;              // A flag indicating whether the projectile is active or not.
    float speed;                // The speed at which the projectile is moving.

};

#endif // PROJECTILES_H
