#include "RenderScene.h"

#include <iostream>
#include <random>


//////////////////////////////// GAME SCENE IMPORTANT ELEMENTS ////////////////////////////////
/// <summary>
/// Render inventory slots at the specified location with the given parameters.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="cx">The X-coordinate of the center of the inventory.</param>
/// <param name="cy">The Y-coordinate of the center of the inventory.</param>
/// <param name="spaceBetweenS">The spacing between inventory slots.</param>
/// <param name="slotsINV">The number of inventory slots to render.</param>
void RenderScene::RenderInventorySlots(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    float cx, float cy, float spaceBetweenS, int slotsINV
) {
    for (int i = 0; i < slotsINV; ++i)
    {
        std::string inventorySlotName = "inventorySlot" + std::to_string(i);
        glm::mat3 modelMatrix = glm::mat3(1); // Identity matrix for no transformation
        modelMatrix *= Transforms2D::Translate(cx + 0, cy - 2 * spaceBetweenS);
        RenderMesh2D(meshes.at(inventorySlotName), shaders.at("VertexColor"), modelMatrix);
    }
}


/// <summary>
/// Render plant objects in the inventory with their corresponding positions and scales.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="newMeshes">A map of newly created plant meshes.</param>
void RenderScene::RenderPlantsForInventory(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    std::unordered_map<std::string, Mesh*>& newMeshes,
    std::vector<Plant>& inventoryPlants
) {
    // Create plant meshes for each inventory slot
    for (int i = 0; i < GslotsINV - 1; ++i)
    {
        std::string plantName = "plant" + std::to_string(i);
        Mesh* plantMesh = ObjectsGame::CreatePlant(
            plantName,
            GradiusPT, GnumTrianglesPT, GtriangleInnerLenPT, GtriangleOuterLenPT,
            Gcolors[i] // Use the i-th color for this plant
        );
        addMeshToList(plantMesh);

        // Render each plant mesh in its inventory slot with scaling
        std::string inventorySlotName = "inventorySlot" + std::to_string(i);
        glm::mat3 modelMatrix = glm::mat3(1); // Start with the identity matrix

        // Compute the position within the inventory slot
        float plantPosX = GstartXINV + i * (GslotWidthINV + GpaddingINV) + GslotWidthINV - GspaceBetweenS / 3;
        float plantPosY = GstartYINV + GslotHeightINV / 2 + GspaceBetweenS / 2;
        glm::vec3 plantPosition = glm::vec3(plantPosX, plantPosY, 0);

        // Create plant object and add it to the plants vector
        Plant newPlant(plantMesh, inventorySlotName, plantPosition, Gcolors[i], GradiusPT,
            GnumTrianglesPT, GtriangleInnerLenPT, GtriangleOuterLenPT,
            -1, -1, GcostPlantsINV[i]);

        newPlant.SetPlaced(false);
        newPlant.SetActive(true);
        inventoryPlants.push_back(newPlant);
        
        // Add the new plant's mesh to the newMeshes map
        newMeshes[plantName] = plantMesh;

        modelMatrix *= Transforms2D::Translate(plantPosX, plantPosY);
        modelMatrix *= Transforms2D::Scale(GscalePlantsInINV, GscalePlantsInINV);
        renderMesh2D(meshes.at(plantName), shaders.at("VertexColor"), modelMatrix);
    }
}


/// <summary>
/// Render sun objects in the inventory with their corresponding positions and scales.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="startXINV">The X-coordinate of the starting position for rendering suns in the inventory.</param>
/// <param name="slotWidthINV">The width of each inventory slot.</param>
/// <param name="paddingINV">The padding between inventory slots.</param>
/// <param name="horizontalOffsetSUN">The horizontal offset for rendering suns within each slot.</param>
/// <param name="startYINV">The Y-coordinate of the starting position for rendering suns in the inventory.</param>
/// <param name="slotHeightINV">The height of each inventory slot.</param>
/// <param name="verticalOffsetSUN">The vertical offset for rendering suns within each slot.</param>
/// <param name="scaleSunInINV">The scale factor for rendering suns in the inventory.</param>
/// <param name="radiusPST">The radius of sun objects.</param>
/// <param name="horizontalGapSUN">The horizontal gap between suns within each slot.</param>
void RenderScene::RenderSunsForInventory(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    float startXINV, float slotWidthINV, float paddingINV, float horizontalOffsetSUN,
    float startYINV, float slotHeightINV, float verticalOffsetSUN,
    float scaleSunInINV, float radiusPST, float horizontalGapSUN)
{
    // Render suns in the first eight inventory slots
    for (int i = 0; i < GslotsINV - 1; ++i)
    {
        // Horizontal center position of the first sun in the slot
        float firstSunPosX = startXINV + i * (slotWidthINV + paddingINV) + horizontalOffsetSUN;

        for (int j = 0; j < GMaxCost; ++j)
        {
            std::string sunName = "sun" + std::to_string(i * 3 + j);

            // Calculate horizontal position for each sun within the slot
            float sunPosX = firstSunPosX + j * ((radiusPST * scaleSunInINV) + horizontalGapSUN);
            // Calculate vertical position for each sun within the slot
            float sunPosY = startYINV + slotHeightINV - verticalOffsetSUN;

            if (meshes.find(sunName) != meshes.end() && shaders.find("VertexColor") != shaders.end()) {
                glm::mat3 modelMatrix = glm::mat3(1);
                modelMatrix *= Transforms2D::Translate(sunPosX, sunPosY);
                modelMatrix *= Transforms2D::Scale(scaleSunInINV, scaleSunInINV);
                RenderMesh2D(meshes.at(sunName), shaders.at("VertexColor"), modelMatrix);
            }
        }
    }
}


/// <summary>
/// Render heart objects in the inventory based on the number of lives left.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="livesLeft">The number of lives left to be represented by hearts.</param>
void RenderScene::RenderHearthsForInventory(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    int livesLeft
) {
    // Calculate the firstHeartX so that hearts are aligned to the right within the last slot
    float firstHeartX = GstartXHS + GslotWidthLIV - GtotalWidthHS / 1.05;
    // Calculate the heartY so that hearts are vertically centered in the slot
    float heartY = GstartYHS + (GslotHeightLIV - GscaleH * GspaceBetweenS) / 2;

    for (int i = 0; i < livesLeft; ++i)
    {
        std::string heartName = "heart" + std::to_string(i);
        glm::mat3 modelMatrix = glm::mat3(1);
        float heartX = firstHeartX + i * (GscaleH * GspaceBetweenS + GspaceBetweenHS * 2.5);
        modelMatrix *= Transforms2D::Translate(heartX, heartY);
        modelMatrix *= Transforms2D::Scale(GscaleHearthInINV, GscaleHearthInINV);

        // Assuming that you have a mesh for each heart and a map of meshes
        renderMesh2D(meshes.at(heartName), shaders.at("VertexColor"), modelMatrix);
    }
}

/// <summary>
/// Render green squares for plant placement in the game grid.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="cx">The X-coordinate of the center of the grid.</param>
/// <param name="cy">The Y-coordinate of the center of the grid.</param>
/// <param name="spaceBetweenS">The spacing between green squares.</param>
/// <param name="sideS">The side length of each green square.</param>
void RenderScene::RenderGreenSquaresForPlants(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    float cx, float cy, float spaceBetweenS, float sideS)
{
    for (int col = 0; col < GNUM_COLS; ++col)
    {
        for (int row = 0; row < GNUM_ROWS; ++row)
        {
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= Transforms2D::Translate(
                cx + sideS * (col + 1) + col * spaceBetweenS,
                cy + sideS * row + spaceBetweenS * (row + 1)
            );
            std::string squareName = "square" + std::to_string(col * GNUM_ROWS + row + 1);
            renderMesh2D(meshes.at(squareName), shaders.at("VertexColor"), modelMatrix);
        }
    }
}


/// <summary>
/// Render the base rectangle in the game.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="cx">The X-coordinate of the center of the base rectangle.</param>
/// <param name="cy">The Y-coordinate of the center of the base rectangle.</param>
/// <param name="spaceBetweenS">The spacing between the base rectangle and other objects.</param>
void RenderScene::RenderBaseRectangle(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    float cx, float cy, float spaceBetweenS
)
{
    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= Transforms2D::Translate(cx, cy + spaceBetweenS);
    RenderMesh2D(meshes.at("rectangle"), shaders.at("VertexColor"), modelMatrix);
}


/// <summary>
/// Render point scores in the inventory based on collected point score objects.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="inventoryPointScores">A vector of PointScore objects to render.</param>
/// <param name="pointScoreCounter">The number of point scores to render.</param>
void RenderScene::RenderPointScoresForInventory(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    std::vector<PointScore> inventoryPointScores,
    int pointScoreCounter
)
{
    // The horizontal spacing between the PointScores
    float spaceBetweenPST = GspaceBetweenHS * 2.5;

    // Total width needed for all PointScores including the spaces between them
    float totalPointScoresWidth = pointScoreCounter * GscaleHearthInINV + (pointScoreCounter - 1) * spaceBetweenPST + 0.25;

    // Center the PointScores within the inventory slot horizontally
    float startPosX = GstartXHS + GslotWidthLIV / 3 - 5.f;

    // Vertical position to place the PointScores directly below the hearts
    float posY = GstartYHS + GscaleHearthInINV - spaceBetweenPST / 2.;

    // Number of pointScores to render in the Inventory
    int renderPoints = pointScoreCounter > 3 ? 3 : pointScoreCounter;

    for (int i = 0; i < renderPoints; ++i)
    {
        glm::mat3 modelMatrix = glm::mat3(1);

        // X position of each PointScore
        float posX = startPosX + i * (GscaleHearthInINV + spaceBetweenPST * 2);

        modelMatrix *= Transforms2D::Translate(posX, posY);
        modelMatrix *= Transforms2D::Scale(GscaleHearthInINV, GscaleHearthInINV);
        RenderMesh2D(inventoryPointScores[i].GetMesh(), shaders.at("VertexColor"), modelMatrix);
    }
}

/////////////////////////////// GAME SCENE IMPORTANT ELEMENTS ///////////////////////////////
/////////////////////////////// GAME SPAWN IMPORTANT ELEMENTS ///////////////////////////////
/// <summary>
/// Render a zombie object if it is active.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="zombie">The Zombie object to render.</param>
void RenderScene::RenderZombie(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    Zombie& zombie
) 
{
    if (zombie.IsActive())
    {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= Transforms2D::Translate(zombie.GetPosition().x, zombie.GetPosition().y);
        modelMatrix *= Transforms2D::Scale(zombie.GetScale(), zombie.GetScale());
        RenderMesh2D(zombie.GetMesh(), shaders.at("VertexColor"), modelMatrix);
    }
}



/// <summary>
/// Render active point score objects with their positions and scales.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="pointScores">A vector of PointScore objects to render.</param>
void RenderScene::RenderPointScores(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    std::vector<PointScore> pointScores
) 
{
    for (auto& pointScore : pointScores)
    {
        if (pointScore.IsActive()) 
        {
            Mesh* mesh = pointScore.GetMesh();
            if (mesh)
            {
                glm::mat3 modelMatrix = glm::mat3(1);
                modelMatrix *= Transforms2D::Translate(pointScore.GetPosition().x, pointScore.GetPosition().y);
                RenderMesh2D(mesh, shaders.at("VertexColor"), modelMatrix);
            }
            else 
            {
                std::cerr << "Error: Mesh not found for PointScore: " << pointScore.GetName() << std::endl;
            }
        }
    }
}
/////////////////////////////// GAME SPAWN IMPORTANT ELEMENTS ///////////////////////////////
///////////////////////////////   PLANT PROJECTILE MOVEMENT   ///////////////////////////////
/// <summary>
/// Render active projectile objects with their positions and scales.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="deltaTime">The time elapsed since the last frame.</param>
/// <param name="resolution">The resolution of the rendering window.</param>
/// <param name="projectiles">A vector of Projectile objects to render.</param>
void RenderScene::RenderProjectiles(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    float deltaTime, glm::ivec2 resolution,
    std::vector<Projectile>& projectiles)
{
    for (auto& projectile : projectiles)
    {
        if (projectile.IsActive())
        {
            // Update the projectile's position
            projectile.Move(deltaTime, resolution);

            // Check if the projectile is off-screen and deactivate it
            if (projectile.GetPosition().x > resolution.x || projectile.GetPosition().y > resolution.y)
            {
                projectile.SetActive(false);
            }
            else
            {
                // Render the projectile if it's active and on-screen
                glm::mat3 modelMatrix = glm::mat3(1);
                glm::vec2 position = projectile.GetPosition();
                modelMatrix *= Transforms2D::Translate(position.x, position.y);
                modelMatrix *= Transforms2D::Rotate(projectile.GetRotation());
                modelMatrix *= Transforms2D::Scale(projectile.GetShorterSideLength(), projectile.GetShorterSideLength());

                renderMesh2D(projectile.GetMesh(), shaders.at("VertexColor"), modelMatrix);
            }
        }
    }
}


/// <summary>
/// Render plant and projectile objects, checking for interactions and shooting capability.
/// </summary>
/// <param name="meshes">A map of mesh names to their corresponding Mesh objects.</param>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="plants">A vector of Plant objects to render.</param>
/// <param name="zombies">A vector of Zombie objects for interaction checking.</param>
/// <param name="projectiles">A vector of Projectile objects for rendering and interaction.</param>
/// <param name="numSegmentsPJ">The number of segments in the projectile.</param>
/// <param name="lengthLongerSidePJ">The length of the longer side of the projectile.</param>
/// <param name="lengthShorterSidePJ">The length of the shorter side of the projectile.</param>
/// <param name="eng">A random number generator engine.</param>
/// <param name="distr">A uniform real distribution for generating projectile speed.</param>
/// <param name="deltaTime">The time elapsed since the last frame.</param>
void RenderScene::RenderPlantsProjectiles(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    std::vector<Plant>& plants,
    std::vector<Zombie>& zombies,
    std::vector<Projectile>& projectiles,
    //
    float numSegmentsPJ, float lengthLongerSidePJ, float lengthShorterSidePJ,
    std::mt19937& eng, std::uniform_real_distribution<>& distr,
    float deltaTime
)
{
    for (auto& plant : plants)
    {
        if (plant.IsActive() && plant.IsPlaced())
        {
            plant.UpdateShootTimer(deltaTime);

            bool canShoot = false;
            for (auto& zombie : zombies)
            {
                if (zombie.IsActive() && zombie.GetRow() == plant.GetRow() &&
                    glm::all(glm::equal(zombie.GetColor(), plant.GetColor(), glm::epsilon<float>())))
                {
                    canShoot = true;
                    break;
                }
            }

            if (canShoot && plant.CanShoot())
            {
                std::string name = "Projectile_" + plant.GetName(); // Construct a unique name for the projectile
                float rotation = 30.0f;                             // Arbitrary rotation value for projectile
                float speed = distr(eng);                           // Speed for the projectile

                Mesh* mesh = ObjectsGame::CreateProjectile(name, 
                                                           numSegmentsPJ,
                                                           lengthLongerSidePJ / 5, lengthShorterSidePJ / 5,
                                                           plant.GetColor());
                Projectile newProjectile(mesh, plant.GetColor(), 
                                         lengthLongerSidePJ / 5, lengthShorterSidePJ / 5,
                                         numSegmentsPJ, name, plant.GetPosition(), rotation, true, speed);
                projectiles.push_back(newProjectile);

                plant.ResetShootTimer();
            }

            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= Transforms2D::Translate(plant.GetPosition().x, plant.GetPosition().y);
            renderMesh2D(plant.GetMesh(), shaders.at("VertexColor"), modelMatrix);
        }
    }
}


///////////////////////////////   PLANT PROJECTILE MOVEMENT   ///////////////////////////////
/////////////////////////////////////  DRAG AND DROP  ///////////////////////////////////////
/// <summary>
/// Render a plant that is being dragged from the inventory.
/// It checks if a plant is currently being dragged(based on the drag state)
/// and, if so, renders the plant at the mouse cursor's position.
/// </summary>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="dragState">The current state of drag-and-drop in the game, including the plant being dragged.</param>
void RenderScene::RenderDraggedPlant( /* PROBLEM CAN COME FROM HERE AT DRAG & DROP INVENTORY PLANTS */
    const std::unordered_map<std::string, Shader*>& shaders,
    const DragState& dragState
) {
    if (dragState.isDragging && dragState.selectedPlant)
    {
        Plant draggedPlant = *dragState.selectedPlant;
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= Transforms2D::Translate(draggedPlant.GetPosition().x, draggedPlant.GetPosition().y);
        modelMatrix *= Transforms2D::Scale(draggedPlant.GetScale(), draggedPlant.GetScale());
        renderMesh2D(draggedPlant.GetMesh(), shaders.at("VertexColor"), modelMatrix);
    }
}


/// <summary>
/// 
/// </summary>
/// <param name="meshes"></param>
/// <param name="shaders"></param>
/// <param name="plants"></param>
/// <param name="zombies"></param>
/// <param name="projectiles"></param>
/// <param name="numSegmentsPJ"></param>
/// <param name="lengthLongerSidePJ"></param>
/// <param name="lengthShorterSidePJ"></param>
/// <param name="eng"></param>
/// <param name="distr"></param>
/// <param name="resolution"></param>
/// <param name="deltaTime"></param>
void RenderScene::RenderDroppedPlant(
    const std::unordered_map<std::string, Mesh*>& meshes,
    const std::unordered_map<std::string, Shader*>& shaders,
    std::vector<Plant>& plants,
    std::vector<Zombie>& zombies,
    std::vector<Projectile>& projectiles,
    //
    float numSegmentsPJ, float lengthLongerSidePJ, float lengthShorterSidePJ,
    std::mt19937& eng, std::uniform_real_distribution<>& distr,
    glm::ivec2 resolution, float deltaTime
) {
    if (shaders.find("VertexColor") == shaders.end()) {
        std::cerr << "Shader 'VertexColor' not found." << std::endl;
        return;
    }

    // Iterate over plants
    for (auto& plant : plants) {
        if (!plant.IsActive()) continue; // Skip inactive plants

        // Check if the plant can shoot projectiles
        bool canShoot = false;
        for (auto& zombie : zombies) {
            if (zombie.IsActive() && zombie.GetRow() == plant.GetRow() &&
                glm::all(glm::equal(zombie.GetColor(), plant.GetColor(), glm::epsilon<float>()))) {
                canShoot = true;
                break;
            }
        }

        if (canShoot && plant.CanShoot()) {
            // Construct a unique name for the projectile
            std::string name = "Projectile_" + plant.GetName();
            // Arbitrary rotation value for projectile
            float rotation = 30.0f;
            // Speed for the projectile
            float speed = distr(eng);

            // Create projectile mesh
            Mesh* mesh = ObjectsGame::CreateProjectile(name,
                numSegmentsPJ,
                lengthLongerSidePJ / 5, lengthShorterSidePJ / 5,
                plant.GetColor());
            // Create and add new projectile
            Projectile newProjectile(mesh, plant.GetColor(),
                lengthLongerSidePJ / 5, lengthShorterSidePJ / 5,
                numSegmentsPJ, name, plant.GetPosition(), rotation, true, speed);
            projectiles.push_back(newProjectile);

            // Reset plant shoot timer
            plant.ResetShootTimer();
        }

        // Render the plant
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= Transforms2D::Translate(plant.GetPosition().x, plant.GetPosition().y);
        modelMatrix *= Transforms2D::Scale(plant.GetScale(), plant.GetScale());

        renderMesh2D(plant.GetMesh(), shaders.at("VertexColor"), modelMatrix);
    }
}
/////////////////////////////////////  DRAG AND DROP  ///////////////////////////////////////
/////////////////////////////// ANIMATE DISSAPEARANCE OBJECTS ///////////////////////////////

/// <summary>
/// Animate the disappearance of a zombie by gradually scaling it down and rendering it.
/// </summary>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="zombie">The Zombie object to animate.</param>
/// <param name="deltaTime">The time elapsed since the last frame.</param>
void RenderScene::AnimateZombieDisappearance(
    const std::unordered_map<std::string, Shader*>& shaders,
    Zombie& zombie, float deltaTime
) 
{
    if (!zombie.IsActive() && zombie.GetScale() > 0.0f)
    {
        float newScale = zombie.GetScale() - GfadeOutSpeedZ * deltaTime;
        zombie.SetScale(std::max(newScale, 0.0f));

        if (zombie.GetScale() <= 0.0f)
        {
            MarkForDeletion(zombie.GetName());
        }
        else 
        {
            // Render the zombie with reduced scale
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= Transforms2D::Translate(zombie.GetPosition().x, zombie.GetPosition().y);
            modelMatrix *= Transforms2D::Scale(zombie.GetScale(), zombie.GetScale());
            RenderMesh2D(zombie.GetMesh(), shaders.at("VertexColor"), modelMatrix);
        }
    }
}


/// <summary>
/// Animate the disappearance of a plant by gradually scaling it down and rendering it.
/// </summary>
/// <param name="shaders">A map of shader names to their corresponding Shader objects.</param>
/// <param name="plant">The Plant object to animate.</param>
/// <param name="deltaTime">The time elapsed since the last frame.</param>
void RenderScene::AnimatePlantDisappearance(
    const std::unordered_map<std::string, Shader*>& shaders,
    Plant& plant, float deltaTime
)
{
    if (!plant.IsActive() && plant.GetScale() > 0.0f)
    {
        float newScale = plant.GetScale() - GfadeOutSpeedP * deltaTime;
        plant.SetScale(std::max(newScale, 0.0f));

        if (plant.GetScale() <= 0.0f)
        {
            MarkForDeletion(plant.GetName());
        }
        else
        {
            // Render the plant with reduced scale
            glm::mat3 modelMatrix = glm::mat3(1);
            modelMatrix *= Transforms2D::Translate(plant.GetPosition().x, plant.GetPosition().y);
            modelMatrix *= Transforms2D::Scale(plant.GetScale(), plant.GetScale());
            RenderMesh2D(plant.GetMesh(), shaders.at("VertexColor"), modelMatrix);
        }
    }
}


/// <summary>
/// Mark an object for deferred deletion, which will be performed later.
/// </summary>
/// <param name="name">The name of the object to mark for deletion.</param>
void RenderScene::MarkForDeletion(const std::string& name) { objectsToDelete.insert(name); }


/// <summary>
/// Perform free memory for the marked objects in the game scene.
/// </summary>
void RenderScene::DeferredDeletion()
{
    for (const auto& name : objectsToDelete)
    {
        auto meshIter = meshes.find(name);
        if (meshIter != meshes.end())
        {
            if (meshIter->second)
            {
                delete meshIter->second;
                meshIter->second = nullptr;
            }
            meshes.erase(meshIter);
        }
    }
    objectsToDelete.clear();
}
/////////////////////////////// ANIMATE DISSAPEARANCE OBJECTS ///////////////////////////////
