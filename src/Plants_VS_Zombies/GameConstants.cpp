#include "GameConstants.h"


// ---------------------------
// Window and Scene Constants
// ---------------------------

// Initial corner point of the window, typically set to the origin.
const glm::vec3 Gcorner = glm::vec3(0, 0, 0);

// Constants defining the scene layout
const float Gcx = 0.0f;                  // X-coordinate for the scene center
const float Gcy = 0.0f;                  // Y-coordinate for the scene center
const int GNUM_ROWS = 5;                 // Number of rows in the green squares grid
const int GNUM_COLS = 4;                 // Number of columns in the green squares grid

// Plant/Zombies/Projectile/InventoryPlants colors.
const std::vector<glm::vec3> Gcolors = {
    glm::vec3(0.0f, 0.0f, 1.0f),       // Blue
    glm::vec3(0.0f, 1.0f, 0.5f),       // Cyan
    glm::vec3(0.5f, 1.0f, 1.0f),       // Green
    glm::vec3(1.0f, 0.8f, 0.0f),       // Yellow
    glm::vec3(1.0f, 0.0f, 0.8f),       // Purple
    glm::vec3(1.0f, 0.0f, 0.0f),       // Red
    glm::vec3(1.0f, 1.0f, 1.0f),       // White
    glm::vec3(0.0f, 0.0f, 0.0f)        // Black
};

// Side length for each green square in the game grid.
const float GsideS = 85.f;
// Space between squares in the game grid
const float GspaceBetweenS = GsideS / float(GNUM_COLS);

// Width and height of the base area rectangle.
const float GwidthR = GsideS;
const float GheightR = GsideS * (GNUM_ROWS + 1);

// Speed for objects range.
const float GMINSPEED = 30.f;
const float GMAXSPEED = 60.f;

// Drop tollerance distance mouse position and center green square.
const float DROP_TOLL = 15.0f;

// ----------------------
// Zombie-related Constants
// ----------------------

// Zombie size constants
const int GspawnZombies = 4;             // Number of MAXIMUM zombies that can be spawned at a time.
const float GfadeOutSpeedZ = 0.25f;      // Constant factor for scalling down dissapearance zombie.
const float GinnerRadiusZ = 25.f;        // Inner radius for zombie collision detection
const float GoutterRadiusZ = 35.f;       // Outer radius for zombie collision detection

// Zombie movement and spawning constants
const float GminZombieSpeed = 25.0f;     // Minimum speed at which zombies move
const float GmaxZombieSpeed = 50.0f;     // Maximum speed for zombies
const float GspawnProbability = 0.1f;    // Probability of zombie spawning at each interval
const float GspawnDelay = 8.0f;          // Delay in seconds between zombie spawn attempts

// ---------------------
// Plant-related Constants
// ---------------------

// Plant rendering constants
const float GfadeOutSpeedP = 0.25f;      // Constant factor for scalling down dissapearance plant.
const int GplantSlots = 8;               // All existing Plant Inventory Slots.
const float GradiusPT = 55.f;            // Radius of the circular base for plants
const int GnumTrianglesPT = 8;           // Number of triangles used to render each plant
const float GtriangleInnerLenPT = 25.f;  // Length of the inner side of plant triangles
const float GtriangleOuterLenPT = 40.f;  // Length of the outer side of plant triangles

// Cost of plants for drag-and-drop functionality
// Costs associated with each plant from inventory from left->right
const std::vector<int> GcostPlantsINV = { 1, 1, 1, 1, 2, 2, 3, 3 };

// -------------------------
// Projectile-related Constants
// -------------------------

// Projectile constants
const int GnumSegmentsPJ = 8;            // Number of segments to render each projectile
const float GlengthLongerSidePJ = 25.f;  // Length of the longer side of a projectile
const float GlengthShorterSidePJ = 15.f; // Length of the shorter side of a projectile

// ----------------------------
// PointScore-related Constants
// ----------------------------

// PointScore (points system) constants
const float GradiusPST = 20.f;           // Radius for rendering PointScore
const int GnumSegmentsPST = 30;          // Number of segments in each PointScore
const int GraySegmentsPST = 75;          // Number of ray segments in PointScore
const float GrayLengthBiggerPST = 20.f;  // Length of larger rays in PointScore
const float GrayLengthSmallerPST = 10.f; // Length of smaller rays in PointScore

// --------------------
// Hearth-related Constants
// --------------------

// Max Plant COST.
const int GMaxCost = 3;

// Heart constants
const int GNumLives = 3;

const float GscaleH = 2.f;               // Scale factor for rendering heart objects
const int GnumSegmentsH = 200;           // Number of segments used to render each heart

// Hearth constants for Lives
const float GspaceBetweenHS = GspaceBetweenS * 0.7f;

// Starting positions for the hearts representing lives
const float GstartXHS = GstartXINV + (GslotWidthINV + GpaddingINV) * (GslotsINV - 1);
const float GstartYHS = GstartYINV + (GslotWidthINV - GpaddingINV) / 1.75f;

// Width available for hearts after considering padding
const float GavWidthForHS = GslotWidthLIV - 2 * GspaceBetweenHS * 0.7f;
// Total width occupied by hearts including spacing
const float GtotalWidthHS = 3 * GscaleH * GspaceBetweenS + 2 * GspaceBetweenHS * 1.5f;

// --------------------
// Inventory-related Constants
// --------------------

const int GslotsINV = 9;                    // Total number of slots in the inventory.
const float GpaddingINV = GspaceBetweenS;   // Padding between inventory slots.

const float GslotWidthINV = 100.f;          // Width of PLANTS & COSTS inventory slot.
const float GslotHeightINV = 100.f;         // Height of PLANTS & COSTS inventory slot.
const float GslotWidthLIV = 250.f;          // Width of a POINTSCORES & HEARTS inventory slot.
const float GslotHeightLIV = 100.f;         // Height of a POINTSCORES & HEARTS inventory slot.

// Starting X-coordinate for the inventory.
const float GstartXINV = 0;
// Starting Y-coordinate for the inventory.
const float GstartYINV = 720.f - GslotHeightINV - GpaddingINV;

// X-coordinate of the last inventory slot.
const float GlastXINV = GstartXINV + (GslotsINV - 1) * (GslotWidthINV + GpaddingINV);
// Y-coordinate of the last inventory slot.
const float GlastYINV = GstartYINV;

// General scaling factor for the inventory.
const float GscaleFactorINV = 0.8f;

// Colors for the inventory
const glm::vec3 GslotFillColor = glm::vec3(0.3f, 0.3f, 0.3f);   // Background color for inventory slots.
const glm::vec3 GslotOutlineColor = glm::vec3(0, 0, 0);         // Outline color for inventory slots.

// Scaling constants for different elements within the inventory
const float GscaleHearthInINV = 0.65f; // Scale factor for heart icons in inventory
const float GscalePlantsInINV = 0.7f;  // Scale factor for plant icons in inventory
const float GscaleSunInINV = 0.5f;     // Scale factor for sun icons in inventory

// Number of suns for each slot
const int GsunsPerSlot[] = { 1, 1, 1, 1, 2, 2, 3, 3 };

// Sun drawing constants
const float GradiusSUN = 10.f;  // Radius of sun icons.

const int GnumSegmentsSUN = 20; // Number of segments for drawing suns.
const int GnumRaySUN = 27;      // Number of rays for each sun icon.

const float GlenRayBiggerSUN = 20.f;    // Length of the bigger rays in sun icons.
const float GlenRaySmallerSUN = 10.f;   // Length of the smaller rays in sun icons.

// Horizontal offset for sun icons in inventory.
const float GhorizontalOffsetSUN = GslotWidthINV / 2 + 1.35 * (GradiusPST * GscaleSunInINV);
// Vertical offset for sun icons in inventory.
const float GverticalOffsetSUN = GslotWidthINV - GslotWidthINV / 6;
// Horizontal gap between sun icons in inventory.
const float GhorizontalGapSUN = 20.0f;

const int GNameWidth = 20;  // Width for MESH NAME for debugging.
const int GNumberWidth = 5; // Width for MESH NUMBER for debugging.

// Color constants
const glm::vec3 GRED         = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GGREEN       = glm::vec3(0.0f, 0.5f, 0.5f);
const glm::vec3 GBLUE        = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 GORANGE      = glm::vec3(1.0f, 0.5f, 0.0f);
const glm::vec3 GPURPLE      = glm::vec3(0.5f, 0.0f, 0.5f);
const glm::vec3 GYELLOW      = glm::vec3(1.0f, 1.0f, 0.0f);
const glm::vec3 GBACKGROUND  = glm::vec3(0.6f, 0.6f, 0.6f);
