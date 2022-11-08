// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   Texture.h
 * @brief:  Texture class used for meshing Models
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>

#include "../Shaders/Shader.h"

class Texture
{
public:
    GLuint ID;
    const char *type;
    GLuint unit;

    Texture(const char *image, const char *texType, GLuint slot);

    // Assigns a texture unit to a texture
    void texUnit(Shader &shader, const char *uniform, GLuint unit);
    // Binds a texture
    void Bind();
    // Unbinds a texture
    void Unbind();
    // Deletes a texture
    void Delete();
};

#endif /* __TEXTURE_CLASS_H__ */