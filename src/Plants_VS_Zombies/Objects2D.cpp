#include "core/engine.h"
#include "utils/gl_utils.h"

#include "Objects2D.h"

#include <vector>


Mesh* Objects2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    const glm::vec3& color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    // Calculate the center of the square
    glm::vec3 center = corner + glm::vec3(length / 2, length / 2, 0);

    std::vector<VertexFormat> vertices;

    // Add the center vertex for the square
    vertices.push_back(VertexFormat(center, color));

    // Add the corner vertices for the square
    vertices.push_back(VertexFormat(corner, color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length, 0, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(length, length, 0), color));
    vertices.push_back(VertexFormat(corner + glm::vec3(0, length, 0), color));

    // Create a new mesh object for the square
    Mesh* square = new Mesh(name);

    // Define the indices for drawing the square
    std::vector<unsigned int> indices;

    if (fill) {
        // Use a triangle fan starting from the center to fill the square
        indices = { 0, 1, 2, 3, 4, 1 }; // Last index connects to the first corner vertex
        square->SetDrawMode(GL_TRIANGLE_FAN);
    }
    else {
        // Use a line loop for the outline
        indices = { 1, 2, 3, 4 }; // Loop back to the start for the border
        square->SetDrawMode(GL_LINE_LOOP);
    }

    // Initialize the square mesh with the vertices and indices
    square->InitFromData(vertices, indices);

    return square;
}


Mesh* Objects2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    const glm::vec3& color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> rectangleVertices;
    rectangleVertices.push_back(VertexFormat(corner, color));
    rectangleVertices.push_back(VertexFormat(corner + glm::vec3(width, 0, 0), color));
    rectangleVertices.push_back(VertexFormat(corner + glm::vec3(width, height, 0), color));
    rectangleVertices.push_back(VertexFormat(corner + glm::vec3(0, height, 0), color));

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> rectangleIndices;

    if (!fill) {
        // If not filled, draw as a line loop.
        rectangle->SetDrawMode(GL_LINE_LOOP);
        rectangleIndices = { 0, 1, 2, 3 }; // Indices for drawing a rectangle as a line loop
    }
    else {
        // If filled, draw as two triangles.
        rectangle->SetDrawMode(GL_TRIANGLES);
        rectangleIndices = { 0, 1, 2, 0, 2, 3 }; // Indices for drawing a filled rectangle
    }

    rectangle->InitFromData(rectangleVertices, rectangleIndices);
    return rectangle;
}


Mesh* Objects2D::CreateCircle(
    const std::string& name,
    glm::vec3 center,
    float numSegments,
    float radius,
    const glm::vec3& color,
    bool fill)
{
    std::vector<VertexFormat> circleVertices;

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> circleIndices;

    circleVertices.push_back(VertexFormat(center, 
                                          glm::vec3(0.5f, 0.5f, 1.0f),
                                          glm::vec3(0.5f, 0.5f, 1.0f)));

    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);

        circleVertices.push_back(VertexFormat(glm::vec3(x, y, 0.5f),
                                              glm::vec3(0.5f, 0.5f, 1.0f),
                                              glm::vec3(0.5f, 0.5f, 1.0f)));
    }

    for (int i = 1; i <= numSegments; ++i)
    {
        circleIndices.push_back(0); // Center vertex
        circleIndices.push_back(i);
        circleIndices.push_back(i + 1);
    }

    // Connect the last vertex to close the circle
    circleIndices.push_back(0); // Center vertex
    circleIndices.push_back(numSegments);
    circleIndices.push_back(1);

    circle->InitFromData(circleVertices, circleIndices);
    return circle;
}


Mesh* Objects2D::CreateHexagon(
    const std::string& name,
    glm::vec3 center,
    float radius,
    const glm::vec3& color,
    bool fill)
{
    std::vector<VertexFormat> hexagonVertices;
    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> hexagonIndices;

    const float numSegments = 6;

    hexagonVertices.push_back(VertexFormat(center, color, color));

    for (int i = 0; i <= numSegments; ++i)
    {
        float theta = 2.0f * M_PI * float(i) / float(numSegments);
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);

        // Use the provided color argument for the hexagon's vertices
        hexagonVertices.push_back(VertexFormat(glm::vec3(x, y, 0.5f), color, color));
    }

    for (int i = 1; i <= numSegments; ++i)
    {
        hexagonIndices.push_back(0); // Center vertex
        hexagonIndices.push_back(i);
        hexagonIndices.push_back(i + 1);
    }

    // Connect the last vertex to close the circle
    hexagonIndices.push_back(0); // Center vertex
    hexagonIndices.push_back(numSegments);
    hexagonIndices.push_back(1);

    hexagon->InitFromData(hexagonVertices, hexagonIndices);
    return hexagon;
}


Mesh* Objects2D::CreateTriangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    glm::vec3 rightBottomCorner,
    glm::vec3 upCorner,
    const glm::vec3& color,
    bool fill)
{
    std::vector<VertexFormat> triangleVertices;
    triangleVertices.push_back(VertexFormat(leftBottomCorner, color));
    triangleVertices.push_back(VertexFormat(rightBottomCorner, color));
    triangleVertices.push_back(VertexFormat(upCorner, color));

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> triangleIndices;

    if (!fill) {
        // If not filled, draw as a line loop.
        triangle->SetDrawMode(GL_LINE_LOOP);
        triangleIndices = { 0, 1, 2 }; // Indices for drawing a triangle as a line loop
    }
    else {
        // If filled, draw as a single triangle.
        triangle->SetDrawMode(GL_TRIANGLES);
        triangleIndices = { 0, 1, 2 }; // Indices for drawing a filled triangle
    }

    triangle->InitFromData(triangleVertices, triangleIndices);
    return triangle;
}


Mesh* Objects2D::CreateIsoscelesTriangle(
    const std::string& name,
    glm::vec3 vertex,
    float width,
    float height,
    const glm::vec3& color,
    bool fill)
{
    // Calculate the positions of the other two vertices to create an isosceles triangle
    glm::vec3 vertex1 = vertex + glm::vec3(-width / 2.0f, 0, 0);    // Left Corner
    glm::vec3 vertex2 = vertex + glm::vec3(width / 2.0f, 0, 0);     // Right Corner
    glm::vec3 vertex3 = vertex + glm::vec3(0, height, 0);           // Up Corner

    std::vector<VertexFormat> triangleVertices;
    triangleVertices.push_back(VertexFormat(vertex1, color));
    triangleVertices.push_back(VertexFormat(vertex2, color));
    triangleVertices.push_back(VertexFormat(vertex3, color));

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> triangleIndices;

    if (!fill) {
        // If not filled, draw as a line loop.
        triangle->SetDrawMode(GL_LINE_LOOP);
        triangleIndices = { 0, 1, 2 }; // Indices for drawing an isosceles triangle as a line loop
    }
    else {
        // If filled, draw as a single triangle.
        triangle->SetDrawMode(GL_TRIANGLES);
        triangleIndices = { 0, 1, 2 }; // Indices for drawing a filled isosceles triangle
    }

    triangle->InitFromData(triangleVertices, triangleIndices);
    return triangle;
}


Mesh* Objects2D::CreateEquilateralTriangle(
    const std::string& name,
    glm::vec3 vertex,
    float length,
    const glm::vec3& color,
    bool fill)
{
    // Calculate the positions of the other two vertices to create an equilateral triangle
    glm::vec3 vertex1 = vertex + glm::vec3(-length / 2.0f, 0, 0);               // Left Corner
    glm::vec3 vertex2 = vertex + glm::vec3(length / 2.0f, 0, 0);                // Right Corner
    glm::vec3 vertex3 = vertex + glm::vec3(0, length * sqrt(3.0) / 2.0f, 0);    // Up Corner

    std::vector<VertexFormat> triangleVertices;
    triangleVertices.push_back(VertexFormat(vertex1, color));
    triangleVertices.push_back(VertexFormat(vertex2, color));
    triangleVertices.push_back(VertexFormat(vertex3, color));

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> triangleIndices;

    if (!fill) {
        // If not filled, draw as a line loop.
        triangle->SetDrawMode(GL_LINE_LOOP);
        triangleIndices = { 0, 1, 2 }; // Indices for drawing an equilateral triangle as a line loop
    }
    else {
        // If filled, draw as a single triangle.
        triangle->SetDrawMode(GL_TRIANGLES);
        triangleIndices = { 0, 1, 2 }; // Indices for drawing a filled equilateral triangle
    }

    triangle->InitFromData(triangleVertices, triangleIndices);
    return triangle;
}


Mesh* Objects2D::CreateRhombus(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    const glm::vec3& color,
    bool fill)
{
    // Calculate the other three vertices based on the left bottom corner and side length
    glm::vec3 rightBottomCorner = leftBottomCorner + glm::vec3(length, 0, 0);
    glm::vec3 upCorner = leftBottomCorner + glm::vec3(length / 2.0f, length / 2.0f * sqrt(3.0), 0);
    glm::vec3 downCorner = rightBottomCorner - glm::vec3(length / 2.0f, length / 2.0f * sqrt(3.0), 0);

    std::vector<VertexFormat> rhombusVertices;
    rhombusVertices.push_back(VertexFormat(leftBottomCorner, color));
    rhombusVertices.push_back(VertexFormat(rightBottomCorner, color));
    rhombusVertices.push_back(VertexFormat(upCorner, color));
    rhombusVertices.push_back(VertexFormat(downCorner, color));

    Mesh* rhombus = new Mesh(name);
    std::vector<unsigned int> rhombusIndices;

    if (!fill) {
        // If not filled, draw as a line loop.
        rhombus->SetDrawMode(GL_LINE_LOOP);
        rhombusIndices = { 0, 1, 2, 3, 0 }; // Indices for drawing a rhombus as a line loop
    }
    else {
        // If filled, draw as two triangles.
        rhombus->SetDrawMode(GL_TRIANGLES);
        rhombusIndices = { 0, 1, 2, 0, 2, 3, 0, 3, 1 }; // Indices for drawing two filled triangles
    }

    rhombus->InitFromData(rhombusVertices, rhombusIndices);
    return rhombus;
}
