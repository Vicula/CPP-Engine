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

#include "VAO.h"
#include "EBO.h"
#include "../../Camera/Camera.h"
#include "Texture.h"

class Mesh
{
private:
    std::unique_ptr<VBO> _VBO;
    std::unique_ptr<EBO> _EBO;

public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    // std::vector<Texture> textures;

    // Store VAO in public so it can be used in the Draw function
    std::unique_ptr <VAO> _VAO;

    // Initializes the mesh
    // std::vector<Texture> &textures
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);

    // Draws the mesh
    void Draw(Shader &shader, Camera &camera);

    // Delete the mesh
    void Delete();
};
#endif /* __MESH_CLASS_H__ */