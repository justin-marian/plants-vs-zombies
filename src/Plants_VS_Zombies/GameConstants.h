#pragma once

#include "components/simple_scene.h"
#include <glm/glm.hpp>

#include "Plants.h"

#include <vector>
#include <unordered_set>
#include <unordered_map>


struct DragState
{
    bool isDragging;
    Plant* selectedPlant;
    glm::vec2 originalPosition;

    void Reset() {
        isDragging = false;
        selectedPlant = nullptr;
        originalPosition = glm::vec2(0);
    }
};

// ---------------------------
// Window and Scene Constants
// ---------------------------

// Corner Window Point (0,0)
extern const glm::vec3 Gcorner;

extern const float Gcx;
extern const float Gcy;

// Number of squares, rows, and columns in the game grid
extern const int GNUM_SQUARES;
extern const int GNUM_ROWS;
extern const int GNUM_COLS;

// Dimensions for the base rectangle
extern const float GwidthR;
extern const float GheightR;

// Space between elements in the scene
extern const float GspaceBetweenS;

// Reference size constant for scaling elements
extern const float GsideS;

extern const float GMINSPEED;
extern const float GMAXSPEED;

extern const float DROP_TOLL;

// ----------------------
// Zombie-related Constants
// ----------------------

// Speed range and spawning parameters for zombies
extern const int GspawnZombies;
extern const float GfadeOutSpeedZ;
extern const float GminZombieSpeed;
extern const float GmaxZombieSpeed;
extern const float GspawnProbability;
extern const float GspawnDelay;

// Zombie size parameters
extern const float GinnerRadiusZ;
extern const float GoutterRadiusZ;

// ---------------------
// Plant-related Constants
// ---------------------

// Plant geometry and appearance parameters
extern const float GfadeOutSpeedP;
extern const int GplantSlots;
extern const float GradiusPT;
extern const int GnumTrianglesPT;
extern const float GtriangleInnerLenPT;
extern const float GtriangleOuterLenPT;

// Colors Pallete
extern const std::vector<glm::vec3> Gcolors;
// Color Fill Zombies Inner Hexagon
extern const glm::vec3 GslotFillColor;
// Color Fill Zombies Outer Hexagon
extern const glm::vec3 GslotOutlineColor;

// Inventory costs for different plants
extern const std::vector<int> GcostPlantsINV;

// -------------------------
// Projectile-related Constants
// -------------------------

// Projectile geometry parameters
extern const int GnumSegmentsPJ;
extern const float GlengthLongerSidePJ;
extern const float GlengthShorterSidePJ;

// ----------------------------
// PointScore-related Constants
// ----------------------------

// PointScore appearance and geometry parameters
extern const float GradiusPST;
extern const int GnumSegmentsPST;
extern const int GraySegmentsPST;
extern const float GrayLengthBiggerPST;
extern const float GrayLengthSmallerPST;

// --------------------
// Hearth-related Constants
// --------------------

// Hearth appearance and scaling parameters
extern const float GscaleH;
extern const int GnumSegmentsH;

// ---------------------------
// Inventory-related Constants
// ---------------------------

// Inventory slot dimensions and padding
extern const int GslotsINV;
extern const float GpaddingINV;
extern const float GslotWidthINV;
extern const float GslotHeightINV;
extern const float GslotWidthLIV;
extern const float GslotHeightLIV;

// Starting positions for inventory slots
extern const float GstartXINV;
extern const float GstartYINV;
extern const float GlastXINV;
extern const float GlastYINV;

// Scaling factors for elements within inventory
extern const float GscaleHearthInINV;
extern const float GscalePlantsInINV;
extern const float GscaleSunInINV;

// Colors for slot outlines and fills
extern const glm::vec3 GslotOutlineColor;
extern const glm::vec3 GslotFillColor;

// --------------------
// Sun-related Constants
// --------------------

// Sun geometry and appearance parameters
extern const float GradiusSUN;
extern const int GnumSegmentsSUN;
extern const int GnumRaySUN;
extern const float GlenRayBiggerSUN;
extern const float GlenRaySmallerSUN;

// Sun positioning within inventory slots
extern const float GhorizontalOffsetSUN;
extern const float GverticalOffsetSUN;
extern const float GhorizontalGapSUN;

extern const int GsunsPerSlot[];

// ------------------------
// Heart (Lives) Constants
// ------------------------

extern const int GMaxCost;

extern const int GNumLives;

// The space between individual heart icons in the inventory
extern const float GspaceBetweenHS;

// Starting X and Y positions for the hearts in the inventory
extern const float GstartXHS;
extern const float GstartYHS;

// The available width for rendering hearts
// taking into account padding on both sides
extern const float GavWidthForHS;

// The total width occupied by all heart icons
// including the space between them
extern const float GtotalWidthHS;

extern const int GNameWidth;
extern const int GNumberWidth;
    
// -------------------------
// Color Palette Constants
// -------------------------

// Commonly used colors in the game
extern const glm::vec3 GORANGE;
extern const glm::vec3 GPURPLE;
extern const glm::vec3 GBLUE;
extern const glm::vec3 GYELLOW;
extern const glm::vec3 GRED;
extern const glm::vec3 GGREEN;
extern const glm::vec3 GBACKGROUND;
