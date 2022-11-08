// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   Mesh.h
 * @brief:  Mesh used for meshing Models
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include <glad/glad.h>

#include "VAO.h"
#include "EBO.h"
#include "../Shaders/Shader.h"

class Mesh
{
public:
    // Store VAO in public so it can be used in the Draw function
    VAO VAO;

    // Initializes the mesh
    Mesh(const GLfloat &vertices, const GLuint &indices);

    // Draws the mesh
    void Draw(Shader &shader);

    // Delete the mesh
    void Delete();
};
#endif /* __MESH_CLASS_H__ */