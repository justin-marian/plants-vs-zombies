#include "core/engine.h"
#include "utils/gl_utils.h"

#include "Transforms2D.h"

#include "Objects2D.h"
#include "ObjectsGame.h"

#include <vector>
#include <string>


constexpr float F_PI = static_cast<float>(M_PI);


Mesh* ObjectsGame::CreatePointScore(
    const std::string& name,
    float radius,
    int segments, int raySegments,
    float rayBigger, float raySmaller,
    const glm::vec3 color, bool fill)
{
    // Initialize vectors to store vertices and indices of the pointScore object.
    std::vector<VertexFormat> pointScoreVertices;
    std::vector<unsigned int> pointScoreIndices;

    // Define the center of the sun and add it as the first vertex.
    glm::vec3 center = glm::vec3(0, 0, 0);
    pointScoreVertices.push_back(VertexFormat(center, color));

    float theta, angle;
    float dx, dy;

    // Calculate and add vertices for the sun's core circle based on the number of segments.
    for (int i = 0; i < segments; ++i)
    {
        // Angle calculation for each segment.
        theta = static_cast<float>(i) / static_cast<float>(segments);
        angle = theta * 2.0f * F_PI;

        // Calculate the position of each vertex on the circle.
        dx = radius * cosf(angle);
        dy = radius * sinf(angle);

        // Add the vertex to the pointScoreVertices list.
        // Calculate the intermediate color between 'color' and white.
        float mixRatio = 0.5f;
        glm::vec3 tipColor = color * (1.0f - mixRatio) + mixRatio;
        pointScoreVertices.push_back(VertexFormat(glm::vec3(dx, dy, 0), tipColor));
    }

    // Generate triangle indices to form the core of the sun using triangle fan method.
    for (int i = 0; i < segments + 1; ++i)
    {
        pointScoreIndices.push_back(0);        // Center of the sun (shared vertex).
        pointScoreIndices.push_back(i);        // Current point on the circle.
        pointScoreIndices.push_back(i + 1);    // Next point on the circle.
    }

    // Alternate length rays.
    float variableRayLength;

    // Create rays around the sun with alternating lengths, forming triangles.
    for (int i = 0; i < segments + 1; ++i)
    {
        // Calculate the angle for each ray segment.
        theta = 2.0f * F_PI * static_cast<float>(i) / static_cast<float>(segments);
        angle = theta + F_PI / static_cast<float>(segments);  // Offset the rays to be in between segments

        // Choose the length of the ray: alternate between the two specified lengths.
        variableRayLength = ((i - 1) % 2 == 0) ? rayBigger : raySmaller;

        // Calculate the position of the end of the ray.
        dx = (radius + variableRayLength) * cosf(angle);
        dy = (radius + variableRayLength) * sinf(angle);

        // Add the vertex to the pointScoreVertices list.
        pointScoreVertices.push_back(VertexFormat(glm::vec3(dx, dy, 0), color));

        // Indices for the triangles of the rays.
        // The vertices at the tips of the rays are at positions
        // 1 + segments + (i-1) in the sunVertices list.
        int tipOfRayIndex = 1 + segments + (i - 1);
        int nextTipIndex = (i < segments) ? (1 + segments + i) : (1 + segments);

        // Create two triangles for each ray (as a quad)
        // to make them visible from both sides

        // Triangle 1
        pointScoreIndices.push_back(i);               // Current point on the core circle
        pointScoreIndices.push_back(tipOfRayIndex);   // Tip of the current ray
        pointScoreIndices.push_back(i + 1);           // Next point on the core circle

        // Triangle 2
        pointScoreIndices.push_back(i + 1);           // Next point on the core circle
        pointScoreIndices.push_back(tipOfRayIndex);   // Tip of the current ray
        pointScoreIndices.push_back(nextTipIndex);    // Tip of the next ray
        // the first one if it's the last ray
    }

    // Create a new mesh with the specified name.
    Mesh* sun = new Mesh(name);
    // Initialize the mesh with the vertices and indices created.
    sun->InitFromData(pointScoreVertices, pointScoreIndices);
    // Return the pointer to the new mesh.
    return sun;
}


Mesh* ObjectsGame::CreateHearth(
    const std::string& name,
    float scale,
    int segments,
    const glm::vec3 color, bool fill)
{
    // This color will be at the center of the heart.
    glm::vec3 tipColor = color - glm::vec3(0.5);

    // Initialize vectors to store vertices and indices of the hearth object.
    std::vector<VertexFormat> heartVertices;
    std::vector<unsigned int> heartIndices;

    // Define the center of the sun and add it as the first vertex.
    glm::vec3 center = glm::vec3(0, 0, 0);
    heartVertices.push_back(VertexFormat(center, tipColor));

    float theta, angle;
    float dx, dy;

    // Calculate and add vertices for the heart shape based on the number of segments.
    for (int i = 0; i <= segments; ++i)
    {
        // Convert the value to radians.
        theta = static_cast<float>(i) / static_cast<float>(segments);
        angle = theta * 2.0f * F_PI;

        // Use parametric equations to define the heart shape's outline.
        dx = scale *  16 * pow(sinf(angle), 3);
        dy = scale * (12 * cosf(1 * angle) - 
                       4 * cosf(2 * angle) -
                       2 * cosf(3 * angle) -
                       1 * cosf(4 * angle));

        // Add the calculated vertex for this segment of the heart.
        heartVertices.push_back(VertexFormat(glm::vec3(dx, dy, 0), color));

        // Indices to form the triangles
        if (i > 0)
        {
            heartIndices.push_back(0);     // Center of the heart (shared vertex).
            heartIndices.push_back(i);     // Current vertex on the outline.
            heartIndices.push_back(i + 1); // Next vertex on the outline.
        }
    }

    // Create a new mesh with the specified name.
    Mesh* heart = new Mesh(name);
    // Initialize the mesh with the vertices and indices created.
    heart->InitFromData(heartVertices, heartIndices);
    // Return the pointer to the new mesh.
    return heart;
}


Mesh* ObjectsGame::CreateProjectile(
    const std::string& name,
    int segments,
    float longerSide, float shorterSide,
    const glm::vec3 color, bool fill)
{
    // This color will be at the tip of the petals.
    glm::vec3 tipColor = glm::vec3(1.0f, 0.8f, 0.8f);

    // Initialize vectors to store vertices and indices of the hearth object.
    std::vector<VertexFormat> projectileVertices;
    std::vector<unsigned int> projecileIndices;

    // Define the center of the sun and add it as the first vertex.
    glm::vec3 center = glm::vec3(0, 0, 0);
    projectileVertices.push_back(VertexFormat(center, color));

    // 8 blades, so divide 360 degrees (in radians) by 8.
    float angleIncrement = 2 * F_PI / segments;
    
    float angle;
    float dxL, dyL;
    float dxS, dyS;

    // Calculate and add vertices for the projectile shape based on the number of segments.
    for (int i = 0; i < segments; ++i) {
        angle = i * angleIncrement;

        // Calculate positions for the longer side of the blade
        dxL = longerSide * cos(angle);
        dyL = longerSide * sin(angle);

        // Calculate positions for the shorter side of the blade (halfway point)
        dxS = shorterSide * cos(angle + angleIncrement / 2);
        dyS = shorterSide * sin(angle + angleIncrement / 2);

        // Add vertices for the blade
        projectileVertices.push_back(VertexFormat(glm::vec3(dxL, dyL, 0), color));
        projectileVertices.push_back(VertexFormat(glm::vec3(dxS, dyS, 0), tipColor));

        // Form the triangle with the center point and the two vertices of the blade
        projecileIndices.push_back(0);          // Center of the blades (shared vertex).
        projecileIndices.push_back(2 * i + 1);  // Current vertex on the blade.
        projecileIndices.push_back(2 * i + 2);  // Next vertex on the blade.
    }


    // Create a new mesh with the specified name
    Mesh* projectile = new Mesh(name);
    // Initialize the mesh with the vertices and indices created.
    projectile->InitFromData(projectileVertices, projecileIndices);
    // Return the pointer to the new mesh.
    return projectile;
}


Mesh* ObjectsGame::CreatePlant(
    const std::string& name,
    float radius,
    int numTriangles,
    float innerLength,
    float outerLength,
    const glm::vec3 color,
    bool fill)
{
    // This color will be at the tip of the petals.
    glm::vec3 tipColor = glm::vec3(1.0f, 0.8f, 0.8f);

    // Initialize vectors to store vertices and indices of the hearth object.
    std::vector<VertexFormat> plantVertices;
    std::vector<unsigned int> plantIndicies;

    if (color == glm::vec3(1, 1, 1) || color == glm::vec3(0, 0, 0))
        tipColor = color;

    // Define the center of the sun and add it as the first vertex.
    glm::vec3 center = glm::vec3(0, 0, 0);
    plantVertices.push_back(VertexFormat(center, color));

    // Calculate angle increment based on the number of triangles
    float angleIncrement = 2 * F_PI / numTriangles;

    for (int i = 0; i < numTriangles; ++i) {
        float angle = i * angleIncrement;

        // Calculate positions for the vertices of the triangles
        float xInner1 = innerLength * cos(angle - angleIncrement / 3);
        float yInner1 = innerLength * sin(angle - angleIncrement / 3);

        float xInner2 = innerLength * cos(angle + angleIncrement / 3);
        float yInner2 = innerLength * sin(angle + angleIncrement / 3);

        float xOuter = outerLength * cos(angle);
        float yOuter = outerLength * sin(angle);

        plantVertices.push_back(VertexFormat(glm::vec3(xInner1, yInner1, 0), color));
        plantVertices.push_back(VertexFormat(glm::vec3(xOuter, yOuter, 0), tipColor));
        plantVertices.push_back(VertexFormat(glm::vec3(xInner2, yInner2, 0), color));

        // Connect vertices to form the triangles
        plantIndicies.push_back(0);
        plantIndicies.push_back(3 * i + 1);
        plantIndicies.push_back(3 * i + 2);
        plantIndicies.push_back(0);
        plantIndicies.push_back(3 * i + 2);
        plantIndicies.push_back(3 * i + 3);
    }

    // Create a new mesh with the specified name
    Mesh* plant = new Mesh(name);
    // Initialize the mesh with the vertices and indices created.
    plant->InitFromData(plantVertices, plantIndicies);
    // Return the pointer to the new mesh.
    return plant;
}


Mesh* ObjectsGame::CreateZombie(
    const std::string& name,
    float innerRadius,  // Inner hexagon radius
    float outerRadius,  // Outer hexagon radius
    const glm::vec3 color,
    bool fill)
{
    glm::vec3 tipColor = glm::vec3(0.5f, 0.5f, 0.5f);

    glm::mat3 rotationMatrix = Transforms2D::Rotate(glm::radians(45.0f)); // Rotate by 45 degrees

    std::vector<VertexFormat> zombieVertices;
    std::vector<unsigned int> zombieIndices;

    glm::vec3 center = glm::vec3(0, 0, 0);

    // Create outer hexagon vertices and indices
    Mesh* outerHexagon = Objects2D::CreateHexagon(name + "_outer", center, outerRadius, color, fill);
    // Apply rotation to each vertex
    for (auto& vertex : outerHexagon->vertices) {
        glm::vec3 pos = glm::vec3(vertex.position.x, vertex.position.y, 1.0f);
        pos = rotationMatrix * pos;
        vertex.position.x = pos.x;
        vertex.position.y = pos.y;
    }
    zombieVertices.insert(zombieVertices.end(), outerHexagon->vertices.begin(), outerHexagon->vertices.end());
    zombieIndices.insert(zombieIndices.end(), outerHexagon->indices.begin(), outerHexagon->indices.end());

    // Create inner hexagon vertices and indices
    Mesh* innerHexagon = Objects2D::CreateHexagon(name + "_inner", center, innerRadius, tipColor, fill);
    // Apply rotation to each vertex
    for (auto& vertex : innerHexagon->vertices) {
        glm::vec3 pos = glm::vec3(vertex.position.x, vertex.position.y, 1.0f);
        pos = rotationMatrix * pos;
        vertex.position.x = pos.x;
        vertex.position.y = pos.y;
    }
    unsigned int indexOffset = static_cast<unsigned int>(zombieVertices.size());
    zombieVertices.insert(zombieVertices.end(), innerHexagon->vertices.begin(), innerHexagon->vertices.end());

    // Adjust indices for the inner hexagon
    for (auto index : innerHexagon->indices) {
        zombieIndices.push_back(index + indexOffset);
    }

    // Create and return the final mesh
    Mesh* zombie = new Mesh(name);
    zombie->InitFromData(zombieVertices, zombieIndices);
    return zombie;
}


Mesh* ObjectsGame::CreateInventory(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width, float height,
    const glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    // The center point of the rectangle
    glm::vec3 center = corner + glm::vec3(width / 2, height / 2, 0);

    // Black color for the outline
    glm::vec3 outlineColor = glm::vec3(0, 0, 0); // Black

    std::vector<VertexFormat> vertices = {
        // Center vertex for the fill
        VertexFormat(center, color),
        // Corner vertices for the fill
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color),
        // Corner vertices for the outline
        VertexFormat(corner, outlineColor),
        VertexFormat(corner + glm::vec3(width, 0, 0), outlineColor),
        VertexFormat(corner + glm::vec3(width, height, 0), outlineColor),
        VertexFormat(corner + glm::vec3(0, height, 0), outlineColor)
    };

    // Indices for the filled rectangle
    std::vector<unsigned int> fillIndices = {
        1, 2, 3,  // First triangle
        1, 3, 4   // Second triangle
    };

    // Indices for the rectangle outline
    std::vector<unsigned int> lineIndices = {
        5, 6, 7, 8, 5 // Loop back to the start for the outline
    };

    Mesh* rectangle = new Mesh(name);

    // Create the filled rectangle if fill is true
    if (fill) {
        rectangle->InitFromData(vertices, fillIndices);
        rectangle->SetDrawMode(GL_TRIANGLES);
    }

    // Overlay the outline on top of the fill
    rectangle->InitFromData(vertices, lineIndices);
    rectangle->SetDrawMode(GL_LINE_LOOP);

    return rectangle;
}
