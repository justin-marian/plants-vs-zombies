#pragma once

#ifndef PLANTS_VS_ZOMBIES_H
#define PLANTS_VS_ZOMBIES_H

#include "components/simple_scene.h"

#include "GameConstants.h"
#include "RenderScene.h"

#include "Zombies.h"
#include "Plants.h"
#include "Projectiles.h"
#include "PointScore.h"
#include "GreenSquares.h"

#include <random>
#include <functional>
#include <unordered_map>
#include <unordered_set>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


class RenderScene;

class Plants_VS_Zombies : public gfxc::SimpleScene
{
public:
    Plants_VS_Zombies();            // Constructor for Plants_VS_Zombies
    ~Plants_VS_Zombies();           // Destructor for Plants_VS_Zombies

    void Init() override;

    int GetLivesLeft() const { return livesLeft; }
    void SetLivesLeft(int newLivesLeft) { livesLeft = newLivesLeft; }
    std::vector<Plant>& GetInventoryPlants() { return inventoryPlants; }
    void SetInventoryPlants(const std::vector<Plant>& newInventoryPlants) { inventoryPlants = newInventoryPlants; }

private:
    RenderScene* renderScene;

    void StopGame();
    void LoseLife();
    glm::vec2 ConvertScreenToWorldCoords(int mouseX, int mouseY);

    void HandlePlantZombieCollisions(float deltaTimeSeconds);
    void HandleProjectileZombieCollisions(float deltaTimeSeconds);

    void UpdatePointScores(float deltaTimeSeconds);
    void UpdateZombies(float deltaTimeSeconds);

    ///
    void FrameStart() override;
    void Update(float deltaTimeSeconds) override;
    void FrameEnd() override;

    void OnInputUpdate(float deltaTime, int mods) override;

    void OnWindowResize(int width, int height) override;

    void OnKeyPress(int key, int mods) override;
    void OnKeyRelease(int key, int mods) override;

    void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

    void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    ///

protected:
    DragState dragState;

    glm::ivec2 resolution;
    const float windowWidth;
    const float windowHeight;
    const float aspectRatio;

    glm::mat3 modelMatrix;
    GLenum polygonMode;

    std::random_device rd;
    std::mt19937 eng;
    std::uniform_real_distribution<> distr;

    bool isGameRunning;
    bool lifeLostThisFrame;

    int livesLeft = 3;
    int pointScoreCounter = 0;

    float cx, cy;
    glm::vec3 corner;

    std::unordered_set<std::string> objectsToDelete;

    std::vector<Zombie> zombies;
    std::vector<Plant> plants;

    std::vector<Projectile> projectiles;
    std::vector<PointScore> pointScores;

    std::vector<GreenSquare> squares;
    std::vector<Plant> inventoryPlants;
    std::vector<PointScore> inventoryPointScores;
};

#endif // PLANTS_VS_ZOMBIES_H
