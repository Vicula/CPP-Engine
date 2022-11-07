// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   EBO.h
 * @brief:  Elements Buffer Object used for meshing Models
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
    // Constructor that generates a Elements Buffer Object and links it to indices
    EBO(const std::vector<GLuint> &indices);

    // Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif /* __EBO_CLASS_H__ */