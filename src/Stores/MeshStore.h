// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: MeshStore.h
 * @brief: Mesh management for rendering
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MESHSTORE_H
#define MESHSTORE_H

#include <map>
#include <string>
#include <glad/glad.h>

#include "../Rendering/Meshes/Mesh.h"

class MeshStore
{
private:
    std::map<std::string, Mesh *> meshes;

public:
    MeshStore();
    ~MeshStore();

    void ClearMeshes();
    MeshStore *AddMesh(const std::string &meshId, const GLfloat &vertices, const GLuint &indices);
    Mesh *GetMesh(const std::string &meshId);
};

#endif /* __MESHSTORE_H__ */
