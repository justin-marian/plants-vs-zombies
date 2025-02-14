#include "Plants_VS_Zombies.h"

#include "RenderScene.h"
#include "GameInit.h"

#include "GameConstants.h"
#include "Transforms2D.h"
#include "Objects2D.h"
#include "ObjectsGame.h"
#include "GreenSquares.h"

#include "Zombies.h"
#include "PointScore.h"
#include "Plants.h"

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>
#include <random>


using namespace std;

// Type alias represents a function pointer that points to any function.
// Providing flexibility in how meshes are rendered and managed at RUN TIME.
using RenderMesh2DFunction = std::function<void(Mesh*, Shader*, const glm::mat3&)>;
using AddMeshToList = std::function<void(Mesh*)>;


/// <summary>
/// Handle game initialization, rendering, updates, and user input.
/// Manage game objects like zombies, plants, projectiles, and pointscores.
/// </summary>
Plants_VS_Zombies::Plants_VS_Zombies() :
    renderScene(nullptr),                              // Manages rendering of all game objects.
    resolution(window->GetResolution()),               // Current screen resolution.
    windowWidth(static_cast<float>(resolution.x)),     // Width of the game window.
    windowHeight(static_cast<float>(resolution.y)),    // Height of the game window.
    aspectRatio(windowWidth / windowHeight),           // Aspect ratio of the game window.

    // Model matrix for transformations.
    // Current OpenGL polygon mode.
    // State of the currently dragged object.
    modelMatrix(), polygonMode(GL_FILL), dragState(),

    // Random device for generating random numbers.
    // Random number engine.
    // Distribution for random values.
    rd(), eng(rd()), distr(),

    // Flag indicating if the game is currently running.
    // Flag for if a life was lost in the current frame.
    isGameRunning(false), lifeLostThisFrame(false),
    // Number of lives left in the game.
    // Counter for the player's score.
    livesLeft(GNumLives), pointScoreCounter(0),
    // Center coordinates for positioning.
    cx(0.0f), cy(0.0f), corner(0.f),

    // List of objects to delete.
    objectsToDelete(),
    // List of zombies, projectiles, pointScores and squares in the game.
    zombies(), plants(), projectiles(), pointScores(), squares(),
    // List of inventoryPlants, inventoryPointScores
    inventoryPlants(), inventoryPointScores()
{
    renderScene = new RenderScene(
        [this](Mesh* mesh, Shader* shader, const glm::mat3& modelMatrix) 
              { RenderMesh2D(mesh, shader, modelMatrix); },
        [this](Mesh* mesh)
              { AddMeshToList(mesh); },
        meshes, shaders
    );
}
Plants_VS_Zombies::~Plants_VS_Zombies() {}


/// <summary>
/// Stop the game by setting the isGameRunning flag to false.
/// </summary>
void Plants_VS_Zombies::StopGame() { isGameRunning = false; }


/// <summary>
/// Decrease the player's lives by one and stops the game if player has 0 lives.
/// </summary>
void Plants_VS_Zombies::LoseLife() 
{
    if (livesLeft > 0)
    {
        livesLeft--;
        std::cout << "\t================================" << std::endl;
        std::cout <<  "\t LIFE LOST. LIVES REMAINING:  "  << livesLeft << std::endl;
        std::cout << "\t================================" << std::endl;
        // Remove the last rendered heart from the screen
        std::string heartName = "heart" + std::to_string(livesLeft);
        renderScene->MarkForDeletion(heartName);
    }

    if (livesLeft == 0)
    {
        std::cout << "\t==========" << std::endl;
        std::cout << "\tGAME OVER!" << std::endl;
        std::cout << "\t==========" << std::endl;
        Plants_VS_Zombies::StopGame();
    }
}


void Plants_VS_Zombies::FrameStart()
{
    // Clear the color buffer and depth buffer
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // Clear the screen content, prepare for rendering.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    resolution = window->GetResolution();
    // Set the screen area where the rendering take place.
    glViewport(0, 0, resolution.x, resolution.y);
}


/// <summary>
/// Initialize the game elements including the camera, inventory, and game objects.
/// </summary>
void Plants_VS_Zombies::Init()
{
    // Start the game, random generator plants in grid at begging,
    // zombies, speed for projectiles and otehr properties...
    srand(static_cast<unsigned int>(time(nullptr)));
    isGameRunning = true;

    /// CONTINUA PARTEA DE RENDERED TEXT

    // Then initialize and load the FreeType library
 //   FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
//    if (FT_Init_FreeType(&ft))
//        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    // Load font as face
//    FT_Face face;
//    if (FT_New_Face(ft, font.c_str(), 0, &face))
//        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    // Set size to load glyphs as
//    FT_Set_Pixel_Sizes(face, 0, fontSize);

    cx = corner.x + GsideS / 2;
    cy = corner.y + GsideS / 2;
    // Initial corner point of the window, typically set to the origin.
    corner = glm::vec3(cx, cy + 1.5 * GsideS, 0);

    // Camera and polygon mode
    polygonMode = GL_FILL;
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, windowWidth, 0, windowHeight, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    GameInit gameInitInstance([this](Mesh* mesh) { this->AddMeshToList(mesh); });
    gameInitInstance.InitializeInventorySlots();
    gameInitInstance.InitializePlantsForInventory();
    gameInitInstance.InitializeSunsForInventory();
    gameInitInstance.InitializeHeartsForInventory();
    gameInitInstance.InitializeBaseRectangle();
    gameInitInstance.InitializeGreenSquaresForPlants(this->squares);
    gameInitInstance.InitializeRandomGridPlants(this->plants, cx, cy, GsideS, GspaceBetweenS);
    GameInit::PrintMeshNames();
}


/// <summary>
///  Handle the logic to update the position and state of point scores.
/// </summary>
/// <param name="deltaTimeSeconds">Time elapsed since the last update.</param>
void Plants_VS_Zombies::UpdatePointScores(float deltaTimeSeconds)
{
    for (auto& pointScore : pointScores)
    {
        if (pointScore.IsActive())
        {
            float lifespan = pointScore.GetLifeSpan();
            lifespan -= deltaTimeSeconds;
            pointScore.SetLifeSpan(lifespan);
            if (pointScore.GetLifeSpan() <= 0)
            {
                renderScene->MarkForDeletion(pointScore.GetName());
                pointScore.SetActive(false);
            }
        }
    }
}


/// <summary>
/// Update the state and position of all active zombies.
/// Check for collisions and handles interactions.
/// </summary>
/// <param name="deltaTimeSeconds">Time elapsed since the last update.</param>
void Plants_VS_Zombies::UpdateZombies(float deltaTimeSeconds)
{
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(), [&](Zombie& zombie) -> bool {
        if (!zombie.IsActive()) {
            return false; // Keep inactive zombies
        }

        zombie.Move(deltaTimeSeconds);

        if (zombie.IsIntersectingWithRectangle(corner, GwidthR, GheightR)) {
            Plants_VS_Zombies::LoseLife();
            renderScene->MarkForDeletion(zombie.GetName());
            return true; // Remove zombie if it intersects with the rectangle
        }

        return false; // Keep the zombie if it doesn't intersect
    }), zombies.end());

    // Now handle rendering separately for active zombies
    for (auto& zombie : zombies)
    {
        if (zombie.IsActive())
        {
            renderScene->RenderZombie(meshes, shaders, zombie);
        }
    }
}


/// <summary>
/// Handle collisions between plants and zombies.
/// If an active plant collides with an active zombie, the plant is set to inactive, effectively 'destroying' it.
/// If a plant is already inactive, this method triggers its disappearance animation.
/// </summary>
/// <param name="deltaTimeSeconds">The time elapsed since the last frame, used for animations</param>
void Plants_VS_Zombies::HandlePlantZombieCollisions(float deltaTimeSeconds) {
    for (auto& plant : plants)
    {
        if (plant.IsActive())
        {
            for (auto& zombie : zombies)
            {
                if (zombie.IsActive() && zombie.IsCollidingWithPlant(plant))
                {
                    plant.SetActive(false);
                    plant.SetPlaced(false);
                    plant.~Plant();
                    break;
                }
            }
        }
        else
        {
            renderScene->AnimatePlantDisappearance(shaders, plant, deltaTimeSeconds);
        }
    }
}


/// <summary>
/// Handle each active projectile for collisions with active zombies.
/// If a collision occurs, the zombie takes a hit, and the projectile is marked for deletion.
/// Additionally, if the zombie is destroyed as a result of the hit, it is also marked for deletion.
/// Trigger the disappearance animation for inactive zombies.
/// </summary>
/// <param name="deltaTimeSeconds">The time elapsed since the last frame, used for animations.</param>
void Plants_VS_Zombies::HandleProjectileZombieCollisions(float deltaTimeSeconds)
{
    for (auto& projectile : projectiles)
    {
        if (!projectile.IsActive())
        {
            continue;
        }
        for (auto& zombie : zombies)
        {
            if (zombie.IsActive() && zombie.IsCollidingWithProjectile(projectile))
            {
                zombie.Hit();
                renderScene->MarkForDeletion(projectile.GetName());
                projectile.SetActive(false);

                if (zombie.IsDestroyed())
                {
                    zombie.SetActive(false);
                    renderScene->MarkForDeletion(zombie.GetName());
                }
                break;
            }
            if (!zombie.IsActive())
            {
                renderScene->AnimateZombieDisappearance(shaders, zombie, deltaTimeSeconds);
            }
        }
    }
}

/// <summary>
/// Update the game state for each frame.
/// Progresses the game state based on the elapsed time(deltaTimeSeconds).
/// Handle various game functionalities such as 
/// spawning zombies, moving and checking collisions, updating point scores, 
/// rendering game elements, and managing plant projectile mechanics.
/// Check whether the game is running and performs cleanup if the game has stopped.
/// </summary>
/// <param name="deltaTimeSeconds">The time elapsed since the last frame update.</param>
void Plants_VS_Zombies::Update(float deltaTimeSeconds)
{
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    // Reset the flag at the start of the update
    lifeLostThisFrame = false;
    // Random device signal HW
    std::random_device rd;    
    // Seed the generator
    std::mt19937 eng(rd());
    // Define the range if speed
    std::uniform_real_distribution<> distr(GMINSPEED, GMAXSPEED);

    /// CHECK IF THE GAME IS STILL RUNNING (STOP RENDERING)!
    if (!isGameRunning)
    {
        // Perform deletion of objects marked for deletion
        renderScene->DeferredDeletion();
        // Skip updating if the game is not running
        return;
    }

    /// RANDOMLY DECIDE WHEN A ZOMBIE SHOULD BE SPAWNED
    Zombie::SpawnRandomZombies(deltaTimeSeconds, resolution, zombies);
    /// ALL ACTIVE ZOMBIES MOVE THEM AND CHECK FOR COLLISIONS
    Plants_VS_Zombies::UpdateZombies(deltaTimeSeconds);

    /// SPAWN NEW POINTSCORES IF NEEDED
    PointScore::SpawnPointScores(deltaTimeSeconds, windowWidth, windowHeight, pointScores, meshes);
    /// UPDATE LIFE AND POINTSCORE
    Plants_VS_Zombies::UpdatePointScores(deltaTimeSeconds);

    /// COLLISION: PLANTS + ZOMBIES
    Plants_VS_Zombies::HandlePlantZombieCollisions(deltaTimeSeconds);
    /// COLLISION: PROJECTILES + ZOMBIES
    Plants_VS_Zombies::HandleProjectileZombieCollisions(deltaTimeSeconds);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RENDER ACTIVE POINTSCORES ON SCREEN
    renderScene->RenderPointScores(meshes, shaders, pointScores);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// POINTSCORE INVENTORY
    renderScene->RenderPointScoresForInventory(meshes, shaders, inventoryPointScores, pointScoreCounter);
    /// INVENTORY SLOTS
    renderScene->RenderInventorySlots(meshes, shaders, cx, cy, GspaceBetweenS, GslotsINV);
    /// PLANTS INSIDE OF THE INVENTORY
    renderScene->RenderPlantsForInventory(meshes, shaders, meshes, inventoryPlants);
    /// SUNS INSIDE OF THE INVENTORY
    renderScene->RenderSunsForInventory(meshes, shaders,
                                        GstartXINV, GslotWidthINV, GpaddingINV,
                                        GhorizontalOffsetSUN, GstartYINV, GslotHeightINV,
                                        GverticalOffsetSUN, GscaleSunInINV, GradiusPST, GhorizontalGapSUN);
    /// HEARTHS INSIDE OF THE INVENTORY
    renderScene->RenderHearthsForInventory(meshes, shaders, livesLeft);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RENDER DROPPED WITHIN THE GREEN SQUARES -> HANDLE SHOOTING
    renderScene->RenderDroppedPlant(meshes, shaders,
                                     plants, zombies, projectiles,
                                     GnumSegmentsPJ, GlengthLongerSidePJ, GlengthShorterSidePJ,
                                     eng, distr, resolution, deltaTimeSeconds);

    /// RENDER THE DRAGGED PLANT
    renderScene->RenderDraggedPlant(shaders, dragState);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// PLANTS WITHIN THE GREEN SQUARES -> HANDLE SHOOTING
    renderScene->RenderPlantsProjectiles(meshes, shaders, 
                                         plants, zombies, projectiles,
                                         GnumSegmentsPJ, GlengthLongerSidePJ, GlengthShorterSidePJ,
                                         eng, distr, deltaTimeSeconds);

    /// RENDER PROJECTILES EXISTENT
    renderScene->RenderProjectiles(meshes, shaders, deltaTimeSeconds, resolution, projectiles);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /// RECTANGLE RED BASE
    renderScene->RenderBaseRectangle(meshes, shaders, cx, cy, GspaceBetweenS);
    /// GREEN SQUARES 
    renderScene->RenderGreenSquaresForPlants(meshes, shaders, cx, cy, GspaceBetweenS, GsideS);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
}


/// <summary>
/// Screen Space -> Normalized Device Coordinates (NDC) -> World Space
/// --------------------------------------------------------------------------------------------------------
/// Coordinates as they appear on your screen, typically in pixels.
/// The origin (0,0) is usually the top-left corner of the canvas
/// --------------------------------------------------------------------------------------------------------
/// A homogeneous coordinate system where each axis ranges from -1.0 to 1.0.
/// The conversion from screen space to NDC involves translating and scaling the coordinates.
/// --------------------------------------------------------------------------------------------------------
/// The coordinate system in which objects are defined the 2D world.
/// https://olegvaraksin.medium.com/convert-world-to-screen-coordinates-and-vice-versa-in-webgl-c1d3f2868086
/// </summary>
/// <param name="mouseX">The X-coordinate of the mouse on the screen (in pixels).</param>
/// <param name="mouseY">The Y-coordinate of the mouse on the screen (in pixels).</param>
/// <returns>World coordinates corresponding to the given screen coordinates.</returns>
glm::vec2 Plants_VS_Zombies::ConvertScreenToWorldCoords(int mouseX, int mouseY)
{
    auto camera = GetSceneCamera();
    glm::vec2 screen = window->GetResolution();

    // Convert screen coordinates to normalized device coordinates.
    glm::vec2 ndc = glm::vec2(
        (2.0f * mouseX) / screen.x - 1.0f, // -1,0
        1.0f - (2.0f * mouseY) / screen.y  // 0,+1
    );

    // Convert NDC to clip space
    glm::vec4 clipSpacePos = glm::vec4(ndc.x, ndc.y, -1.0f, 1.0f);

    // Apply inverse projection and view transformations to get world coordinates.
    glm::mat4 invProjMat = glm::inverse(camera->GetProjectionMatrix());
    glm::mat4 invViewMat = glm::inverse(camera->GetViewMatrix());
    glm::vec4 worldSpacePos = invProjMat * clipSpacePos;

    // Return the x and y components as world coordinates.
    return glm::vec2(worldSpacePos.x, worldSpacePos.y);
}


void Plants_VS_Zombies::OnKeyRelease(int key, int mods) {}
void Plants_VS_Zombies::OnWindowResize(int width, int height) {}
void Plants_VS_Zombies::OnInputUpdate(float deltaTime, int mods) {}
void Plants_VS_Zombies::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}
void Plants_VS_Zombies::FrameEnd() {}


void Plants_VS_Zombies::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
}


/// <summary>
/// Move the plant and rendering on the screen when is dragged.
/// </summary>
/// <param name="mouseX">X - coordinate of the mouse.</param>
/// <param name="mouseY">Y - coordinate of the mouse.</param>
/// <param name="deltaX">Change in X - coordinate since last event</param>
/// <param name="deltaY">Change in Y - coordinate since last event.</param>
void Plants_VS_Zombies::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (dragState.isDragging && dragState.selectedPlant)
    {
        glm::vec2 worldMousePos = ConvertScreenToWorldCoords(mouseX, mouseY);
        dragState.selectedPlant->SetPosition(worldMousePos);
    }
}


/// <summary>
/// For the LEFT mouse button(GLFW_MOUSE_BUTTON_RIGHT), it checks for point scores and plants in the inventory to interact with.
///   If a point score is clicked, it is added to the inventory, and if a plant is clicked, it initiates the dragging process.
/// For the middle mouse button(GLFW_MOUSE_BUTTON_MIDDLE), it removes the plant from the game if clicked and eliberates grid cell.
/// </summary>
/// <param name="mouseX">X - coordinate of the mouse cursor.</param>
/// <param name="mouseY"> Y - coordinate of the mouse cursor.</param>
/// <param name="button">The mouse button that was pressed.</param>
/// <param name="mods">Modifier keys pressed during the mouse event.</param>
void Plants_VS_Zombies::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) 
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    { // MOUSE LEFT
        glm::vec2 worldMousePos = ConvertScreenToWorldCoords(mouseX, mouseY);
        for (auto& pointScore : pointScores)
        {
            if (pointScore.IsMouseOver(worldMousePos.x, worldMousePos.y))
            {
                std::cout << "POINTSCORE CLICKED: " << pointScore.GetName() << std::endl;
                std::cout << "COORDONATES ( "
                    << pointScore.GetPosition().x << " , "
                    << pointScore.GetPosition().y << " ) " << std::endl;
                if (inventoryPointScores.size() < 3)
                {
                    std::cout << "POINTSCORE MODIFIED: " << pointScoreCounter << std::endl;
                    // Clone the PointScore for the inventory
                    PointScore inventoryPointScore = pointScore;
                    // Set the disappearing flag
                    inventoryPointScore.SetDissapearing(true);
                    inventoryPointScores.push_back(inventoryPointScore);
                }

                pointScoreCounter++;  // Increment the inventory counter
                // Mark the original PointScore for deletion
                pointScore.SetDissapearing(true);
                renderScene->MarkForDeletion(pointScore.GetName());
            }
        }

        // Remove PointScores that are marked for deletion
        pointScores.erase(
            std::remove_if(pointScores.begin(), pointScores.end(),
                [](const PointScore& ps) { return ps.IsDissapearing(); }),
            pointScores.end()
        );

        for (auto& plant : inventoryPlants) {
            if (plant.IsActive() && plant.IsMouseOver(worldMousePos.x, worldMousePos.y)) {
                int plantCost = plant.GetCost();

                // Ensure pointScoreCounter is checked here before proceeding
                if (pointScoreCounter >= plantCost) {
                    if (plant.GetMesh() && shaders.find("VertexColor") != shaders.end()) {
                        dragState.isDragging = true;
                        dragState.selectedPlant = new Plant(plant);
                        dragState.originalPosition = plant.GetPosition();
                        break; // Break if a plant has been selected for dragging
                    }
                }
                else {
                    std::cout << "Not enough points to drag this plant." << std::endl;
                    break; // Break the loop as the plant cannot be dragged due to insufficient points
                }
            }
        }
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE) // CLICK RIGHT removes the plant
    {
        glm::vec2 worldMousePos = ConvertScreenToWorldCoords(mouseX, mouseY);
        for (auto it = plants.begin(); it != plants.end();) {
            if (it->IsMouseOver(worldMousePos.x, worldMousePos.y)) {
                std::cout << "PLANT CLICKED: " << it->GetName() << std::endl;

                // Iterate over squares to find the one containing the clicked plant
                for (auto& square : squares) {
                    if (square.ContainsPlantAt(it->GetPosition())) {
                        // Mark the square as unoccupied
                        square.SetOccupied(false);
                        break; // Exit the loop once the correct square is found and updated
                    }
                }

                // Mark the plant for deletion and remove it from the collection
                renderScene->MarkForDeletion(it->GetName());
                it = plants.erase(it); // Erase returns the iterator following the last removed element
            }
            else {
                ++it; // Continue if not erasing the plant
            }
        }
    }
}

/// <summary>
/// When the LEFT mouse button(GLFW_MOUSE_BUTTON_RIGHT) is released while dragging a plant,
/// it checks if the plant can be placed in a selected grid square.
/// The plant is only placed if the square is unoccupied and the
/// player has enough point scores to 'purchase' the plant.
/// Update the inventory and game state based on the placement.
/// </summary>
/// <param name="mouseX">X - coordinate of the mouse cursor upon release.</param>
/// <param name="mouseY">Y - coordinate of the mouse cursor upon release.</param>
/// <param name="button">The mouse button that was released.</param>
/// <param name="mods">Modifier keys pressed during the mouse event.</param>
void Plants_VS_Zombies::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && dragState.isDragging) {
        glm::vec2 worldMousePos = ConvertScreenToWorldCoords(mouseX, mouseY);
        bool placed = false;

        for (auto& square : squares) {
            float distance = glm::distance(worldMousePos, square.GetCenterPosition());
            if (!square.IsOccupied() && distance < DROP_TOLL && pointScoreCounter >= dragState.selectedPlant->GetCost()) {

                // Update plant properties
                dragState.selectedPlant->SetPosition(square.GetCenterPosition());
                dragState.selectedPlant->SetActive(true);
                dragState.selectedPlant->SetRow(square.GetRow());
                dragState.selectedPlant->SetColumn(square.GetCol());

                // Assuming ResetShootTimer and other methods are properly defined
                dragState.selectedPlant->ResetShootTimer();
                placed = true;

                pointScoreCounter -= dragState.selectedPlant->GetCost();
                std::cout << "POINTSCORE MODIFIED: " << pointScoreCounter << std::endl;

                dragState.selectedPlant->SetActive(true);
                dragState.selectedPlant->SetPlaced(true);

                // Add the plant to the rendering list
                plants.push_back(std::move(*dragState.selectedPlant));
                delete dragState.selectedPlant;
                break; // Plant placed successfully
            }
        }

        if (!placed) {
            // Revert changes if plant is not placed
            delete dragState.selectedPlant;
        }

        dragState.Reset();
    }
}
