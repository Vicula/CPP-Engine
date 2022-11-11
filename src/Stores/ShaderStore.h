// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: ShaderStore.h
 * @brief: Shader management for rendering
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef SHADERSTORE_H
#define SHADERSTORE_H

#include <unordered_map>
#include <string>

#include "../Rendering/Shaders/Shader.h"

class ShaderStore
{
private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;

public:
    ShaderStore();
    ~ShaderStore();

    void ClearShaders();
    ShaderStore *AddShader(const std::string &shaderId, const std::string &vertShader, const std::string &fragShader);
    Shader &GetShader(const std::string &shaderId);
};

#endif /* __SHADERSTORE_H__ */
