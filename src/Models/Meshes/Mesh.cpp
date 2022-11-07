#include "Mesh.h"

// std::vector<Texture> &textures
Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
{
	this->vertices = vertices;
	this->indices = indices;
	// Mesh::textures = textures;

	// Generates Vertex Array Object and binds it
	_VAO = std::make_unique<VAO>();
	_VAO->Bind();

	// Generates Vertex Buffer Object and links it to vertices
	_VBO = std::make_unique<VBO>(vertices);
	// // Generates Element Buffer Object and links it to indices
	_EBO = std::make_unique<EBO>(indices);

	// Links VBO attributes such as coordinates and colors to VAO
	_VAO->LinkAttrib(*_VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
	_VAO->LinkAttrib(*_VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float)));
	_VAO->LinkAttrib(*_VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float)));
	_VAO->LinkAttrib(*_VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void *)(9 * sizeof(float)));

	// // Unbind all to prevent accidentally modifying them
	_VAO->Unbind();
	_VBO->Unbind();
	_EBO->Unbind();
}

void Mesh::Draw(Shader &shader, Camera &camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	_VAO->Bind();

	// Keep track of how many of each type of textures we have
	// unsigned int numDiffuse = 0;
	// unsigned int numSpecular = 0;

	// for (unsigned int i = 0; i < textures.size(); i++)
	// {
	// 	std::string num;
	// 	std::string type = textures[i].type;
	// 	if (type == "diffuse")
	// 	{
	// 		num = std::to_string(numDiffuse++);
	// 	}
	// 	else if (type == "specular")
	// 	{
	// 		num = std::to_string(numSpecular++);
	// 	}
	// 	textures[i].texUnit(shader, (type + num).c_str(), i);
	// 	textures[i].Bind();
	// }

	// Take care of the camera Matrix
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the actual mesh
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::Delete()
{
	_VAO->Delete();
	_VBO->Delete();
	_EBO->Delete();
}