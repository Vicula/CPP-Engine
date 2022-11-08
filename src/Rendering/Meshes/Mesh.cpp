#include "Mesh.h"

Mesh::Mesh(const GLfloat &vertices, const GLuint &indices)
{
    // Generates Vertex Array Object and binds it
    // VAO1.Bind();

    // // Generates Vertex Buffer Object and links it to vertices
    // VBO VBO1(vertices, sizeof(vertices));
    // // Generates Element Buffer Object and links it to indices
    // EBO EBO1(indices, sizeof(indices));

    // // Links VBO to VAO
    // VAO1.LinkVBO(VBO1, 0);
    // // Unbind all to prevent accidentally modifying them
    // VAO1.Unbind();
    // VBO1.Unbind();
    // EBO1.Unbind();
}

void Mesh::Draw(Shader &shader)
{
    shader.Activate();
    // VAO1.Bind();
}

void Mesh::Delete()
{
    // VAO1.Delete();
}