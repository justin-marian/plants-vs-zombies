#pragma once

#ifndef POINTSCORES_H
#define POINTSCORES_H

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <unordered_map>


class Mesh;

class PointScore 
{
public:
    // Constructor for PointScores
    PointScore(const std::string& name, const glm::vec3& position, const glm::vec3& color,
        float radius, int numSegments, int raySegments,
        float biggerRayLength, float smallerRayLength);
    ~PointScore();

    // Animates the disappearance of the PointScore when collected or expired
    void AnimateDisappearance(float deltaTime);

    // Spawn PointScores at random locations
    static void SpawnPointScores(float deltaTime,
        float windowWidth, float windowHeight,
        std::vector<PointScore>& pointScores,
        std::unordered_map<std::string, Mesh*>& meshes);

    // Checks if the mouse cursor is over the PointScore
    bool IsMouseOver(float mouseX, float mouseY) const;

    // Getters and Setters
    std::string GetName() const;
    glm::vec3 GetPosition() const;

    float GetLifeSpan() const;
    void SetLifeSpan(float newLifeSpan);

    bool IsActive() const;
    void SetActive(bool active);

    bool IsDissapearing() const;
    void SetDissapearing(bool dissapearing);

    Mesh* GetMesh() const;
    void SetMesh(Mesh* newMesh);

private:
    Mesh* mesh;
    std::string name;
    glm::vec3 position;
    glm::vec3 color;

    float radius;                   // Radius of the PointScore

    int numSegments;                // Number of Segments to create a SUN shape
    int raySegments;                // Number of Segments for the SUN rays
        
    float biggerRayLength;          // Bigger Ray for Outer Sun PointScore collision
    float smallerRayLength;         // Smaller Ray for Inner Sun PointScore collision

    float lifespan;                 // Time that a PointScore appears on the Screen
    bool isActive;                  // Flag to check if the pointScore is active

    bool isDisappearing;            // Check if the pointScore dissapeared
    float disappearanceProgress;    // Progress of 
};

#endif // POINTSCORES_H
