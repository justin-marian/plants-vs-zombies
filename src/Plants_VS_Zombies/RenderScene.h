#pragma once

#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H

#include "components/simple_scene.h"

#include "Plants_VS_Zombies.h"
#include "GameConstants.h"

#include "Transforms2D.h"
#include "ObjectsGame.h"

#include "Zombies.h"
#include "Plants.h"
#include "Projectiles.h"
#include "PointScore.h"
#include "GreenSquares.h"

#include <random>
#include <memory>
#include <unordered_set>
#include <unordered_map>


class Plants_VS_Zombies;

class RenderScene : public gfxc::SimpleScene {
public:
    using RenderMesh2DFunction = std::function<void(Mesh*, Shader*, const glm::mat3&)>;
    using AddMeshToList = std::function<void(Mesh*)>;
 
    // Constructor for RenderScene
    RenderScene(
        RenderMesh2DFunction renderMesh2D,                  // RenderMesh2D
        AddMeshToList addMeshToList,                        // AddMeshToList
        std::unordered_map<std::string, Mesh*>& meshes,
        std::unordered_map<std::string, Shader*>& shaders
    ) :
        renderMesh2D(std::move(renderMesh2D)),
        addMeshToList(std::move(addMeshToList)),
        meshes(meshes), shaders(shaders) {}

    // Access to RenderMesh2D function
    void RenderMesh2D(Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix) {
        renderMesh2D(mesh, shader, modelMatrix); 
    }

    // Render inventory slots based on provided parameters.
    void RenderInventorySlots(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        float cx, float cy, float spaceBetweenS, int slotsINV
    );

    // Render plants for the inventory based on provided parameters.
    void RenderPlantsForInventory(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        std::unordered_map<std::string, Mesh*>& newMeshes,
        std::vector<Plant>& inventoryPlants
    );

    // Render suns cost for plants in the inventory
    void RenderSunsForInventory(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        float startXINV, float slotWidthINV, float paddingINV, float horizontalOffsetSUN,
        float radiusPST, float scaleSunInINV, float horizontalGapSUN,
        float startYINV, float slotHeightINV, float verticalOffsetSUN
    );


    // Render point scores in the inventory
    void RenderPointScoresForInventory(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        std::vector<PointScore> inventoryPointScores,
        int pointScoreCounter
    );

    // Render heart icons to represent remaining lives in the 
    void RenderHearthsForInventory(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        int livesLeft
    );

    // Render projectiles in the game 
    void RenderProjectiles(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        float deltaTime, glm::ivec2 resolution,
        std::vector<Projectile>& projectiles
    );

    // Render green squares for placing plants in the game scene
    void RenderGreenSquaresForPlants(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        float cx, float cy, float spaceBetweenS, float sideS
    );

    // Render the base rectangle in the game scene
    void RenderBaseRectangle(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        float cx, float cy, float spaceBetweenS
    );

    // Render a zombie in the game scene
    void RenderZombie(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        Zombie& zombie
    );

    // Render point scores in the game scene
    void RenderPointScores(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        std::vector<PointScore> pointScores
    );

    // Render plant projectiles in the game scene
    void RenderPlantsProjectiles(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        std::vector<Plant>& plants,
        std::vector<Zombie>& zombies,
        std::vector<Projectile>& projectiles,
        float numSegmentsPJ, float lengthLongerSidePJ, float lengthShorterSidePJ,
        std::mt19937& eng, std::uniform_real_distribution<>& distr, float deltaTime
    );

    // Render plant from inventory dragged in the game scene
    void RenderDraggedPlant(
        const std::unordered_map<std::string, Shader*>& shaders,
        const DragState& dragState
    );

    void RenderDroppedPlant(
        const std::unordered_map<std::string, Mesh*>& meshes,
        const std::unordered_map<std::string, Shader*>& shaders,
        std::vector<Plant>& plants,
        std::vector<Zombie>& zombies,
        std::vector<Projectile>& projectiles,
        float numSegmentsPJ, float lengthLongerSidePJ, float lengthShorterSidePJ,
        std::mt19937& eng, std::uniform_real_distribution<>& distr, glm::ivec2 resolution, float deltaTime
    );

    // Animate the disappearance of a zombie in the game scene
    void AnimateZombieDisappearance(
        const std::unordered_map<std::string, Shader*>& shaders,
        Zombie& zombie, float deltaTime
    );

    // Animate the disappearance of a plant in the game scene
    void AnimatePlantDisappearance(
        const std::unordered_map<std::string, Shader*>& shaders,
        Plant& plant,
        float deltaTime
    );

    // Mark an object for deferred deletion by name
    void MarkForDeletion(const std::string& name);
    // Perform deferred deletion of marked objects
    void DeferredDeletion();

private:
    AddMeshToList addMeshToList;
    RenderMesh2DFunction renderMesh2D;
    std::unordered_map<std::string, Mesh*> meshes;
    std::unordered_map<std::string, Shader*> shaders;
    std::unordered_set<std::string> objectsToDelete;
};

#endif // RENDER_SCENE_H
