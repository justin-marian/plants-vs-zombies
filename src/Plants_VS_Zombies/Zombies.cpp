#include "Zombies.h"

#include "GameConstants.h"
#include "Transforms2D.h"
#include "ObjectsGame.h"


constexpr int MAX_LIFE = 3; // MAX LIFE ZOMBIE

// Initialize static member for spawn timing
float Zombie::spawnTimer = 0.0f;


/// <summary>
/// Constructor for the Zombie class.
/// Initialize a Zombie with given properties.
/// </summary>
/// <param name="n">Name of the zombie.</param>
/// <param name="m">Mesh for the zombie.</param>
/// <param name="pos">Position of the zombie.</param>
/// <param name="sc">Scale of the zombie.</param>
/// <param name="inRadius">Inner radius of the zombie (for collision detection).</param>
/// <param name="outRadius">Outer radius of the zombie.</param>
/// <param name="col"> Color of the zombie.</param>
/// <param name="spd">Speed of the zombie.</param>
Zombie::Zombie(const std::string& name, Mesh* mesh, glm::vec2 position,
               float scale, float inRadius, float outRadius,
               glm::vec3 color, float speed, int row) :
               name(name), mesh(mesh), position(position),
               scale(scale), innerRadius(inRadius), outerRadius(outRadius),
               color(color), speed(speed), isActive(true), row(row)
               { /* Constructor initializes a Zombie with given properties */ }
Zombie::~Zombie() {}


/// <summary>
/// Update Zombie's position based on its speed.
/// Deactivate the zombie if it moves off-screen.
/// </summary>
/// <param name="deltaTime">Time elapsed since the last update.</param>
void Zombie::Move(float deltaTime)
{
    // Move the zombie leftward
    position.x -= speed * deltaTime;

    // Deactivate the zombie if it moves off-screen
    if (position.x < 0.0f)
    {
        isActive = false;
    }
}


/// <summary>
/// Determine whether it's time to spawn a new zombie based on the elapsed time.
/// </summary>
/// <param name="deltaTime">Time elapsed since the last update.</param>
/// <returns>True if it's time to spawn a new zombie, false otherwise.</returns>
bool Zombie::ShouldSpawnZombie(float deltaTime)
{
    // Increment the timer
    spawnTimer += deltaTime;

    if (spawnTimer >= GspawnDelay)
    {
        // Reset the timer for the next spawn
        spawnTimer -= GspawnDelay;
        // Indicates that is time to spawn a new zombie
        return true;
    }

    // Not enough time has passed to spawn a new zombie
    return false;
}


/// <summary>
/// Spawn a zombie at a specific row grid and adds it to the provided vector of zombies.
/// Calculate the spawning position based on the row and resolution.
/// </summary>
/// <param name="row">Row in which to spawn the zombie.</param>
/// <param name="resolution">Screen resolution (used to determine spawn position).</param>
/// <param name="zombies">Vector to which the new zombie will be added.</param>
void Zombie::SpawnZombieAtRow(int row, const glm::ivec2& resolution, std::vector<Zombie>& zombies)
{
    int colorIndex = rand() % Gcolors.size();
    glm::vec3 zombieColor = Gcolors[colorIndex];

    // Calculate the spawning position based on the row and resolution
    // Horizontal Position on the right edge of the screen
    float spawnX = static_cast<float>(resolution.x);
    // Vertical Position of each zombie to spawn, centered for each row
    float spawnY = Gcy + (GsideS * row) + (GspaceBetweenS * (row + 1)) + GsideS;

    // Generate a random speed for the zombie
    float randomSpeed = GminZombieSpeed +
                        static_cast<float>(rand()) / 
                        (static_cast<float>(RAND_MAX / (GmaxZombieSpeed - GminZombieSpeed)));

    // Generate a unique name for the zombie
    std::string zombieName = "zombie" + std::to_string(zombies.size() + 1);

    // Create the mesh for the zombie
    Mesh* zombieMesh = ObjectsGame::CreateZombie(zombieName, GinnerRadiusZ, GoutterRadiusZ, zombieColor);

    // Add the newly created zombie to the vector
    zombies.emplace_back(zombieName, zombieMesh, glm::vec2(spawnX, spawnY),
        1.0f, GinnerRadiusZ, GoutterRadiusZ, zombieColor, randomSpeed, row);
}


/// <summary>
/// Determine if zombies should be spawned based on the elapsed time and then randomly decides the number of zombies to spawn.
/// </summary>
/// <param name="deltaTimeSeconds">The time elapsed since the last frame.</param>
/// <param name="resolution">resolution The current resolution of the game window.</param>
/// <param name="zombies">Newly spawned zombies are added to this vector.</param>
void Zombie::SpawnRandomZombies(float deltaTimeSeconds, const glm::ivec2& resolution, std::vector<Zombie>& zombies)
{
    if (ShouldSpawnZombie(deltaTimeSeconds))
    {
        int zombiesToSpawn = rand() % GspawnZombies + 1;
        for (int i = 0; i < zombiesToSpawn; ++i)
        {
            int randomRow = rand() % GNUM_ROWS;
            SpawnZombieAtRow(randomRow, resolution, zombies);
        }
    }
}


/// <summary>
/// Check if the zombie is intersecting with the base rectangle.
/// Useful for detecting when the zombie reaches a certain area of the base RED rectangle.
/// </summary>
/// <param name="corner">Bottom-left corner of the rectangle.</param>
/// <param name="widthR">Width of the rectangle.</param>
/// <param name="heightR">Height of the rectangle.</param>
/// <returns>True if the zombie intersects with the rectangle, false otherwise.</returns>
bool Zombie::IsIntersectingWithRectangle(const glm::vec2& corner, float widthR, float heightR) const
{
    // Find the horizontal and vertical distances from the zombie's center to the rectangle's nearest edge
    float deltaX = position.x - std::max(corner.x, std::min(position.x, corner.x + widthR));
    float deltaY = position.y - std::max(corner.y, std::min(position.y, corner.y + heightR));

    // Check if the zombie is within its radius of the rectangle, collision check
    // point-circle distance calculation instead of rectangle-rectangle
    return (deltaX * deltaX + deltaY * deltaY) < (outerRadius / 2 * outerRadius / 2);
}

/// <summary>
/// Check for collision between the zombie and a given plant.
/// Use the positions and sizes of the zombie and plant to determine overlap.
/// </summary>
/// <param name="plant">The plant to check for collision with.</param>
/// <returns>True if the zombie collides with the plant, false otherwise.</returns>
bool Zombie::IsCollidingWithPlant(const Plant& plant) const
{
    glm::vec2 plantPos = plant.GetPosition();
    const float plantSize = plant.GetLength();

    return  (glm::abs(position.x - plantPos.x) < (outerRadius + plantSize)) &&
            (glm::abs(position.y - plantPos.y) < (outerRadius + plantSize));
}


/// <summary>
/// Check for collision between the zombie and a projectile.
/// Consider both position overlap and color matching for the collision.
/// </summary>
/// <param name="projectile">The projectile to check for collision with.</param>
/// <returns>True if the zombie collides with the projectile and the colors match, false otherwise.</returns>
bool Zombie::IsCollidingWithProjectile(const Projectile& projectile) const
{
    glm::vec2 projPos = projectile.GetPosition();
    float projSize = projectile.GetLongerSideLength();

    bool overlap =  (glm::abs(position.x - projPos.x) < (outerRadius + projSize)) &&
                    (glm::abs(position.y - projPos.y) < (outerRadius + projSize));
    bool sameCol =  glm::all(glm::equal(color, projectile.GetColor(), glm::epsilon<float>()));

    return overlap && sameCol;
}


// Getters & Setters for green square properties.

// Register a hit on the zombie.
void            Zombie::Hit()                           { hitCount++; }
// Getter for the number of hits on the zombie.
int             Zombie::GetHitCount() const             { return hitCount; }
// Check if the zombie is destroyed (hit count exceeds the limit).
bool            Zombie::IsDestroyed() const             { return hitCount >= MAX_LIFE; }
// Getter for the row of the zombie in the grid.
int             Zombie::GetRow() const                  { return row; }
// Setter for the row of the zombie in the grid.
void            Zombie::SetRow(int row)                 { this->row = row; }
// Getter for the active state of the zombie.
bool            Zombie::IsActive() const                { return isActive; }
// Setter for the zombie's active.
void            Zombie::SetActive(bool active)          { this->isActive = active; }
// Getter for the zombie's mesh.
Mesh*           Zombie::GetMesh() const                 { return mesh; }
// Getter for the zombie's color.
glm::vec3       Zombie::GetColor() const                { return color; }
// Getter for the zombie's position.
glm::vec2       Zombie::GetPosition() const             { return position; }
// Getter for the zombie's name.
std::string     Zombie::GetName() const                 { return name; }
// Getter for the zombie's scale.
float           Zombie::GetScale() const                { return scale; }
// Setter for the zombies's scale.
void            Zombie::SetScale(float scale)           { this->scale = scale; }
// Getter for the zombie's outterRadius.
float           Zombie::GetOutRadius() const            { return outerRadius; }
// Setter for the zombie's mesh.
void            Zombie::SetMesh(Mesh* mesh)             { this->mesh = mesh; }
