// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file:   Input.h
 * @brief:  Class used to represent a Key Input
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <vector>

class IInput
{
protected:
    // If disabled, KeyInput.getIsKeyDown always returns false
    bool _isEnabled{};
    // Map from monitored keyes to their pressed states
    std::vector<int> _keys;

    // Main KeyInput functionality
public:
    // Takes a list of which keys to keep state for
    IInput(std::vector<int> keysToMonitor) : _isEnabled{true}, _keys{keysToMonitor} {}

    ~IInput() = default;

    // See _isEnabled for details
    bool getIsEnabled() { return _isEnabled; }
    void setIsEnabled(bool value) { _isEnabled = value; }
};

template <typename TEvent>
class Input : public IInput
{
};

#endif /* __INPUT_CLASS_H__ */