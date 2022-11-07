// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   VBO.h
 * @brief:  Elements Buffer Object used for meshing Models
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// Structure to standardize the vertices used in the meshes
struct Vertex
{
    glm::vec3 position;
    // glm::vec3 normal;
    // glm::vec3 color;
    // glm::vec2 texUV;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    VBO(const std::vector<Vertex> &vertices);

    // Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif /* __VBO_CLASS_H__ */