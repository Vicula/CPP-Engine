// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   MeshComponent.h
 * @brief:  Component used to add a mesh to an Entity for rendering
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef MESHCOMPONENT_H
#define MESHCOMPONENT_H

#include <string>
#include <glad/glad.h>
#include <vector>

#include "../Models/Shaders/Shader.h"
#include "../Models/Meshes/VAO.h"
#include "../Models/Meshes/VBO.h"
#include "../Models/Meshes/EBO.h"

struct MeshComponent
{
public:
    std::string shaderId;
    std::string meshId;

    MeshComponent(std::string meshId = "default" , std::string shaderId = "default")
    {
        this->meshId = meshId;
        this->shaderId = shaderId;
    }
};

#endif /* __MESHCOMPONENT_H__ */