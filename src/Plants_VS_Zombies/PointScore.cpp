#include "PointScore.h"

#include <iostream>
#include <cstdlib>

#include "GameConstants.h"
#include "ObjectsGame.h"
#include "Transforms2D.h"


/// <summary>
/// Constructor for creating a PointScore object with specified properties.
/// </summary>
/// <param name="name">The name of the PointScore.</param>
/// <param name="position">The position of the PointScore in 3D space.</param>
/// <param name="color">The color of the PointScore.</param>
/// <param name="radius">The radius of the PointScore.</param>
/// <param name="numSegments">The number of segments used to render the PointScore.</param>
/// <param name="raySegments">The number of ray segments for the PointScore.</param>
/// <param name="biggerRayLength">The length of the bigger ray for the PointScore.</param>
/// <param name="smallerRayLength">The length of the smaller ray for the PointScore.</param>
PointScore::PointScore(const std::string& name, const glm::vec3& position, const glm::vec3& color,
    float radius, int numSegments, int raySegments,
    float biggerRayLength, float smallerRayLength) :
    mesh(nullptr), name(name), position(position), color(color),
    radius(radius), numSegments(numSegments), raySegments(raySegments),
    biggerRayLength(biggerRayLength), smallerRayLength(smallerRayLength),
    lifespan(5.0f), isActive(true), isDisappearing(false), disappearanceProgress(0.0f)
    { /* Constructor initializes a PointScore with given properties */ }
PointScore::~PointScore() {}


/// <summary>
/// Check if the mouse is over this PointScore.
/// </summary>
/// <param name="worldMouseX">X coordinate of the mouse in the world space.</param>
/// <param name="worldMouseY">Y coordinate of the mouse in the world space.</param>
/// <returns>True if the mouse is over the PointScore, false otherwise.</returns>
bool PointScore::IsMouseOver(float worldMouseX, float worldMouseY) const
{
    float dx = worldMouseX - position.x;
    float dy = worldMouseY - position.y;
    float distanceSquared = dx * dx + dy * dy;
    return distanceSquared <= (radius * radius);
}


/// <summary>
/// Spawn PointScores at random positions within the window.
/// </summary>
/// <param name="deltaTime">Time elapsed since the last frame.</param>
/// <param name="windowWidth">Width of the rendering window.</param>
/// <param name="windowHeight">Height of the rendering window.</param>
/// <param name="pointScores">A vector to store the spawned PointScores.</param>
/// <param name="meshes">A map of mesh names to Mesh objects.</param>
void PointScore::SpawnPointScores(float deltaTime, float windowWidth, float windowHeight,
    std::vector<PointScore>& pointScores, std::unordered_map<std::string, Mesh*>& meshes)
{
    /// TIMER TO DETERMINE IF I CAN SPAWN MORE
    static float spawnTimer = 0.0f;
    /// FIX SPAWN INTERVAL FOR POINTSCORES
    static const float spawnInterval = 5.0f;

    spawnTimer += deltaTime;

    if (spawnTimer >= spawnInterval)
    {
        spawnTimer -= spawnInterval;
        // Generates numbers between 3 and 6
        int numberOfPointScoresToSpawn = rand() % 4 + 3;

        for (int i = 0; i < numberOfPointScoresToSpawn; ++i) {
            float randomX = static_cast<float>(rand()) / RAND_MAX * windowWidth;
            float randomY = static_cast<float>(rand()) / RAND_MAX * windowHeight;
            glm::vec3 randomPosition = glm::vec3(randomX, randomY, 0.0f);

            // Generate a unique name for each PointScore
            std::string pointScoreName = "pointScore" + std::to_string(pointScores.size() + i);
            PointScore newPointScore(pointScoreName,                // unique name of the plant
                                     randomPosition,                // plant random position
                                     glm::vec3(1.0f, 1.0f, 0.0f),   // color
                                     20.0f,                         // radius
                                     30, 75,                        // segments, raySegments
                                     20.0f, 10.0f);                 // rayBigger, raySmaller

            // Create mesh for the PointScore
            Mesh* pointScoreMesh = ObjectsGame::CreatePointScore(pointScoreName, 
                                                                 20.0f,                         // radius
                                                                 30, 75,                        // segments, raySegments
                                                                 20.0f, 10.0f,                  // rayBigger, raySmaller
                                                                 glm::vec3(1.0f, 1.0f, 0.0f));  // color

            // Check if mesh is valid
            if (pointScoreMesh)
            {
                newPointScore.SetMesh(pointScoreMesh);
                meshes[pointScoreName] = pointScoreMesh;
                pointScores.push_back(newPointScore);
            }
            else 
            {
                // Log an error message if mesh creation fails
                std::cerr << "FAILED TO CREATE POINTSCORE MESH: " << pointScoreName << std::endl;
            }
        }
    }
}


/// <summary>
/// Animate the disappearance of a PointScore.
/// </summary>
/// <param name="deltaTime">Time elapsed since the last frame.</param>
void PointScore::AnimateDisappearance(float deltaTime)
{
    disappearanceProgress += deltaTime * 0.3f;

    if (disappearanceProgress >= 1.0f)
    {
        isActive = false;
    }
}


// Getters & Setters for pointScore properties

// Getter for the name of the PointScore.
std::string     PointScore::GetName() const                             { return name; }
// Getter for the position of the PointScore.
glm::vec3       PointScore::GetPosition() const                         { return position; }
// Getter for the lifespan of the PointScore.
float           PointScore::GetLifeSpan() const                         { return lifespan; }
// Setter for the lifespan of the PointScore.
void            PointScore::SetLifeSpan(float lifesoan)                 { this->lifespan = lifesoan; }
// Check if the PointScore has dissapeared or not.
bool            PointScore::IsDissapearing() const                      { return isDisappearing; }
// Setter for the PointScore is disappearing.
void            PointScore::SetDissapearing(bool dissapearing)          { this->isDisappearing = dissapearing; }
// Getter for the PointScore is active.
bool            PointScore::IsActive() const                            { return isActive; }
// Setter for the active status of the PointScore.
void            PointScore::SetActive(bool active)                      { this->isActive = active; }
// Setter for the mesh associated with the PointScore.
void            PointScore::SetMesh(Mesh* mesh)                         { this->mesh = mesh; }
// Getter for the mesh associated with the PointScore.
Mesh*           PointScore::GetMesh() const                             { return mesh; }
