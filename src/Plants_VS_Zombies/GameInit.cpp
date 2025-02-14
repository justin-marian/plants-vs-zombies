#include "GameInit.h"
#include "GameConstants.h"

#include "Objects2D.h"
#include "ObjectsGame.h"

#include "GreenSquares.h"
#include "Plants_VS_Zombies.h"

#include <iostream>


// Map to hold the created mesh objects, accessible by their names.
std::unordered_map<std::string, Mesh*> GameInit::meshMap;


/// <summary>
/// Initialize the inventory slots and adds them to the mesh list.
/// Each slot is represented by a rectangle mesh where plants & pointScores will be placed.
/// </summary>
void GameInit::InitializeInventorySlots()
{
    Mesh* inventorySlotMesh;

    // Loop to create multiple inventory slots. Excludes the last special slot.
    for (int i = 0; i < GslotsINV - 1; ++i)
    {
        // Calculate the X and Y position for each slot based on its index.
        float slotX = GstartXINV + i * (GslotWidthINV + GpaddingINV);
        float slotY = GstartYINV;

        // Generate a unique name for each slot using its index.
        std::string inventorySlotName = "inventorySlot" + std::to_string(i);

        // Create a rectangular mesh for the inventory slot with specified dimensions and fill color.
        inventorySlotMesh = ObjectsGame::CreateInventory(
            inventorySlotName,                          // Unique name for each standard inventory slot, based on its index.
            glm::vec3(slotX, slotY, 0.0f),              // Calculated position for the slot, ensuring even spacing and alignment.
            GslotWidthINV,                              // Standard width for all inventory slots (except the last one).
            GslotHeightINV,                             // Standard height for all inventory slots.
            GslotFillColor                              // Consistent fill color used for all standard slots.
        );

        // Store the created mesh in a map for easy access and add it to the list of meshes for rendering.
        meshMap[inventorySlotName] = inventorySlotMesh;
        addMeshToList(inventorySlotMesh);
    }

    // Create and add the last inventory slot, which might differ in size.
    std::string lastInventorySlotName = "inventorySlot" + std::to_string(GslotsINV - 1);

    inventorySlotMesh = ObjectsGame::CreateInventory(
        lastInventorySlotName,                          // Unique name for the last inventory slot.
        glm::vec3(GlastXINV, GlastYINV, 0.0f),          // Position for the last slot, typically at the end of the inventory row.
        GslotWidthLIV,                                  // Width of the last slot, lives and pointscores accumulated.
        GslotHeightLIV,                                 // Height of the last slot, lives and pointscores accumulated.
        GslotFillColor                                  // Same fill color as the standard slots.
    );

    // Add the last slot mesh to the map and the list of meshes.
    meshMap[lastInventorySlotName] = inventorySlotMesh;
    addMeshToList(inventorySlotMesh);
}


/// <summary>
/// Initialize plant meshes and adds them to the inventory slots.
/// </summary>
void GameInit::InitializePlantsForInventory()
{
    // Create the initial plants inventory slots
    for (int i = 0; i < GslotsINV - 1; ++i)
    {
        // Construct a unique name for each plant based on its index
        std::string plantSlotName = "plantSlot" + std::to_string(i);

        // Determine the color for the plant from the predefined colors
        glm::vec3 color = Gcolors[i % Gcolors.size()];

        // Create the plant mesh using the predefined parameters and color
        Mesh* plantMesh = ObjectsGame::CreatePlant(
            plantSlotName,             // Unique name for of each standard inventory plant, based on its index.
            GradiusPT,                 // Radius of the plant.
            GnumTrianglesPT,           // Number of triangles for the plant mesh.
            GtriangleInnerLenPT,       // Inner length of the triangles (\/).
            GtriangleOuterLenPT,       // Outer length of the triangles (/\).
            color                      // Color of the plant.
        );

        // Add the last slot mesh to the map and the list of meshes.
        meshMap[plantSlotName] = plantMesh;
        addMeshToList(plantMesh);
    }
}


/// <summary>
/// Initialize pointScoresInventory icons for inventory slots,
/// varyfing the number of pointScores per slot.
/// Each slot contains a different number of pointScores.
/// </summary>
void GameInit::InitializeSunsForInventory()
{
    // Initialize the sun meshes with varying counts per inventory slot
    for (int i = 0; i < GplantSlots; ++i) // Assuming you have 8 slots in total
    {
        int sunCount = GsunsPerSlot[i]; // Get the number of suns for the current slot

        for (int j = 0; j < sunCount; ++j) // Loop over the number of suns for this slot
        {
            // Construct a unique name for each sun based on its position in the inventory
            std::string sunName = "sun" + std::to_string(i * 3 + j);

            // Create the sun mesh using the predefined parameters
            Mesh* sunMesh = ObjectsGame::CreatePointScore(
                sunName,              // Name of the mesh
                GradiusSUN,            // Radius of the sun
                GnumSegmentsPST,       // Number of segments for the sun mesh
                GnumRaySUN,            // Number of rays for the sun mesh
                GlenRayBiggerSUN,      // Length of the bigger rays
                GlenRaySmallerSUN,     // Length of the smaller rays
                GBACKGROUND            // Color of the sun
            );

            // Add the last slot mesh to the map and the list of meshes.
            meshMap[sunName] = sunMesh;
            addMeshToList(sunMesh);
        }
    }
}


/// <summary>
/// Initialize heart objects for representing game lives in the inventory.
/// </summary>
void GameInit::InitializeHeartsForInventory()
{
    for (int i = 0; i < GNumLives; ++i)
    {
        // Construct a unique name for each heart
        std::string heartName = "heart" + std::to_string(i);

        // Create the heart mesh using the predefined parameters
        Mesh* heartMesh = ObjectsGame::CreateHearth(
            heartName,        // Name of the mesh
            GscaleH,          // Scale factor for the heart
            GnumSegmentsH,    // Number of segments for the heart mesh
            GRED              // Color of the heart
        );

        // Add the last slot mesh to the map and the list of meshes.
        meshMap[heartName] = heartMesh;
        addMeshToList(heartMesh);
    }
}


/// <summary>
/// Initialize the base RED rectangle object.
/// </summary>
void GameInit::InitializeBaseRectangle()
{
    std::string rectangleName = "rectangle";

    // Create a rectangle mesh
    Mesh* rectangle = Objects2D::CreateRectangle(
        rectangleName,     // Name of the mesh
        Gcorner,           // Position (bottom-left corner of the rectangle)
        GwidthR,           // Width of the rectangle
        GheightR,          // Height of the rectangle
        GRED               // Color of the rectangle
    );

    // Add the last slot mesh to the map and the list of meshes.
    meshMap[rectangleName] = rectangle;
    addMeshToList(rectangle);
}


/// <summary>
/// Initialize green squares for plants in a game grid.
/// </summary>
/// <param name="squares">A vector to store GreenSquare objects representing the grid cells.</param>
void GameInit::InitializeGreenSquaresForPlants(std::vector<GreenSquare>& squares)
{
    for (int col = 0; col < GNUM_COLS; ++col)
    {
        for (int row = 0; row < GNUM_ROWS; ++row)
        {
            // Calculate the square number based on column and row
            int squareNumber = col * GNUM_ROWS + row + 1;

            // Create a unique square name based on its number
            std::string squareName = "square" + std::to_string(squareNumber);

            // Create a square mesh and add it to the mesh map
            Mesh* square = Objects2D::CreateSquare(squareName, Gcorner, GsideS, GGREEN);
            meshMap[squareName] = square;
            addMeshToList(square);

            // Calculate the position of the square in 2D space
            glm::vec3 squarePosition = glm::vec3(
                Gcx + GsideS * (col + 1) + col * GspaceBetweenS,
                Gcy + GsideS * row + GspaceBetweenS * (row + 1),
                0.0f
            );

            // Create a GreenSquare object with relevant data
            GreenSquare greenSquare(squareName, square,
                squarePosition + glm::vec3(GsideS / 2, GsideS / 2, 0.0f),
                false, GsideS, row, col);

            // Set the row and column data for the GreenSquare
            greenSquare.SetRow(row);
            greenSquare.SetCol(col);

            // Add the GreenSquare object to the vector
            squares.push_back(greenSquare);
        }
    }
}



/// <summary>
/// Initialize a grid of plants randomly distributed across the defined rows and columns.
/// Plants are placed based on a 50% chance in each grid square. Each plant's position,
/// type, and other attributes are calculated and assigned BASED ON RANDOM.
/// </summary>
/// <param name="plants">A reference to a vector of Plant objects to which the initialized plants will be added.</param>
/// <param name="cx">The x-coordinate of the starting point of the grid.</param>
/// <param name="cy">The y-coordinate of the starting point of the grid.</param>
/// <param name="sideS">The side length of each square in the grid.</param>
/// <param name="spaceBetweenS">The space between each square in the grid.</param>
void GameInit::InitializeRandomGridPlants(
    std::vector<Plant>& plants,
    float cx, float cy,
    float sideS, float spaceBetweenS)
{
    for (int col = 0; col < GNUM_COLS; ++col)
    {
        for (int row = 0; row < GNUM_ROWS; ++row)
        {
            // Randomly decide whether to place a plant in this square - 50% chance.
            if (rand() % 2 == 0)
            {
                // Calculate the position for each square
                glm::vec3 squarePosition = glm::vec3(
                    cx + sideS * (col + 1) + col * spaceBetweenS,
                    cy + sideS * row + spaceBetweenS * (row + 1),
                    0.0f
                );

                // Calculate the center position for the plant in this square.
                glm::vec3 plantPosition = squarePosition + glm::vec3(sideS / 2, sideS / 2, 0.0f);
                // Corresponding index color and cost plant from the inventory.
                int colorIndex = rand() % 8;
                int costIndex = colorIndex;

                // Randomly select color and type for this plant.
                std::string plantType = "plant" + std::to_string(colorIndex);

                // Create and add each plant mesh.
                std::string plantName = plantType + "_" + std::to_string(col * GNUM_ROWS + row);

                // Create plant mesh and add it to the list of meshes
                Mesh* plantMesh = ObjectsGame::CreatePlant(plantName, GradiusPT,
                    GnumTrianglesPT, GtriangleInnerLenPT, GtriangleOuterLenPT,
                    Gcolors[colorIndex]);

                addMeshToList(plantMesh);

                // Create plant object and add it to the plants vector
                Plant newPlant(plantMesh, plantName, plantPosition, Gcolors[colorIndex], GradiusPT,
                    GnumTrianglesPT, GtriangleInnerLenPT, GtriangleOuterLenPT,
                    row, col, GcostPlantsINV[costIndex]);

                newPlant.SetPlaced(true);
                newPlant.SetActive(true);
                plants.push_back(newPlant);
            }
        }
    }
}

/// <summary>
/// PRINT THE NAME AND NUMBER OF ALL MESHES INITIALIZED AT INIT() PHASE.
/// </summary>
void GameInit::PrintMeshNames()
{
    static int k = 0;
    std::cout << "\t===========================" << std::endl;
    std::cout << "\t  (INIT) : MESH MAP NAMES  " << std::endl;
    std::cout << "\t===========================" << std::endl;

    for (const auto& pair : meshMap)
    {
        k++;

        std::string meshName = pair.first;
        int namePaddingLength = GNameWidth - meshName.length();
        // Ensure paddingLength is not negative
        namePaddingLength = std::max(0, namePaddingLength);

        // Create padding string for name with spaces
        std::string namePadding(namePaddingLength, ' ');

        // Number padding
        std::string meshNumber = std::to_string(k);
        int numberPaddingLength = GNumberWidth - meshNumber.length();
        // Ensure paddingLength is not negative
        numberPaddingLength = std::max(0, numberPaddingLength);

        // Create padding string for number with spaces
        std::string numberPadding(numberPaddingLength, ' ');

        std::cout << "( NR : " << numberPadding << k
            << " | MESH NAME : " << meshName << namePadding
            << ")" << std::endl;
    }

    std::cout << "\t=========================" << std::endl;
}
