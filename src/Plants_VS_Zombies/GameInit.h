#pragma once

#ifndef GAME_INIT_H
#define GAME_INIT_H

#include "components/simple_scene.h"

#include "Plants.h"
#include "GreenSquares.h"

#include <unordered_map>


class GameInit 
{
public:
    // Constructor accepts a function that knows how to add a Mesh to the rendering list!
    GameInit(std::function<void(Mesh*)> addMeshFunc) : addMeshToList(std::move(addMeshFunc)) {}

    // Initialize at Init phase different parts of the game scene.
    void InitializeInventorySlots();                                                        // Initialize the inventory slots where items will be placed.
    void InitializePlantsForInventory();                                                    // Initialize the plant objects for the inventory.
    void InitializeSunsForInventory();                                                      // Initialize the sun cost plant objects for inventory.
    void InitializeHeartsForInventory();                                                    // Initialize the health/heart objects for inventory.
    void InitializeBaseRectangle();                                                         // Initialize the base playing field rectangle.
    //////////////////////////////////////////////////////////////////////////////////////////
    void InitializeRandomGridPlants(std::vector<Plant>& plants,                             // Initialize the green squares where plants will be placed.
                                    float cx, float cy, float sideS, float spaceBetweenS);
    void InitializeGreenSquaresForPlants(std::vector<GreenSquare>& squares);                // Initialize the green squares where plants will be placed.
    //////////////////////////////////////////////////////////////////////////////////////////

    static void PrintMeshNames();

private:
    // Container for all meshes used in the game.
    static std::unordered_map<std::string, Mesh*> meshMap;
    // Function pointer to add a Mesh to the scene.
    std::function<void(Mesh*)> addMeshToList;
};

#endif // GAME_INIT_H
