#include "Projectiles.h"


/// <summary>
/// Construct a new Projectile object with the specified properties.
/// </summary>
/// <param name="mesh">A pointer to the Mesh object associated with the projectile.</param>
/// <param name="color">The color of the projectile.</param>
/// <param name="longerSideLength">The length of the longer side of the projectile.</param>
/// <param name="shorterSideLength">The length of the shorter side of the projectile.</param>
/// <param name="numSegments">The number of segments used for rendering the projectile.</param>
/// <param name="name">The name of the projectile.</param>
/// <param name="position">The initial position of the projectile.</param>
/// <param name="rotation">The initial rotation angle of the projectile (in degrees).</param>
/// <param name="isActive">A flag indicating whether the projectile is active.</param>
/// <param name="speed">The speed at which the projectile moves.</param>
Projectile::Projectile(Mesh* mesh, const glm::vec3& color,
                       float longerSideLength, float shorterSideLength,
                       int numSegments,
                       const std::string& name, const glm::vec2& position,
                       float rotation, bool isActive, float speed) :
                       mesh(mesh), color(color),
                       longerSideLength(longerSideLength), shorterSideLength(shorterSideLength),
                       numSegments(numSegments),
                       name(name), position(position),
                       rotation(rotation), isActive(isActive), speed(speed)
                       { /* Constructor initializes a Projectile with given properties. */ }
Projectile::~Projectile() {}


/// <summary>
/// Move the projectile based on its current speed and deltaTime.
/// </summary>
/// <param name="deltaTime">The time elapsed since the last frame (in seconds).</param>
/// <param name="resolution">The resolution of the rendering window (width and height).</param>
void Projectile::Move(float deltaTime, const glm::ivec2& resolution)
{
    // Make the projectile move on OX (velocity * time).
    position.x += speed * deltaTime;
    // Make the projectile rotate.
    rotation += 5 * deltaTime;

    if (rotation >= 360.0f)
    {
        rotation -= 360.0f;
    }

    // Deactivate the projectile instead of resetting its position.
    if (position.x > resolution.x)
    {
        isActive = false;
    }
}

// Getters & Setters for projectile properties.

// Getter for the name of the projectile.
std::string         Projectile::GetName() const                             { return name; }
// Getter for the Mesh object associated with the projectile.
Mesh* Projectile::GetMesh() const                                           { return mesh; }
// Getter for the color of the projectile.
glm::vec3           Projectile::GetColor() const                            { return color; }
// Getter for the current position of the projectile.
glm::vec2           Projectile::GetPosition() const                         { return position; }
// Setter for the position of the projectile.
void                Projectile::SetPosition(const glm::vec2& newPosition)   { position = newPosition; }
// Getter for the speed of the projectile.
float               Projectile::GetSpeed() const                            { return speed; }
// Setter for the speed of the projectile.
void                Projectile::SetSpeed(float newSpeed)                    { speed = newSpeed; }
// Getter for the rotation angle of the projectile.
float               Projectile::GetRotation() const                         { return rotation; }
// Setter for the rotation angle of the projectile.
void                Projectile::SetRotation(float newRotation)              { rotation = newRotation; }
// Check if the projectile is active.
bool                Projectile::IsActive() const                            { return isActive; }
// Setter for the active state of the projectile.
void                Projectile::SetActive(bool active)                      { isActive = active; }
// Getter for the length of the longer side of the projectile.
float               Projectile::GetLongerSideLength() const                 { return longerSideLength; }
// Getter for the length of the shorter side of the projectile.
float               Projectile::GetShorterSideLength() const                { return shorterSideLength; }
