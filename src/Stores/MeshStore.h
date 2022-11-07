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

#include <unordered_map>
#include <string>

#include "../Models/Meshes/Mesh.h"

class MeshStore
{
private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes;

public:
    MeshStore();
    ~MeshStore();

    void ClearMeshes();
    MeshStore *AddMesh(const std::string &meshId, const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
    Mesh &GetMesh(const std::string &meshId);
};

#endif /* __MESHSTORE_H__ */
