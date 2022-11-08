// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: AssetStore.h
 * @brief: Asset management for rendering
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef ASSETSTORE_H
#define ASSETSTORE_H

#include <map>
#include <string>
// #include <SDL2/SDL.h>

class AssetStore
{
private:
    // std::map<std::string, SDL_Texture *> textures;

public:
    AssetStore();
    ~AssetStore();

    void ClearAssets();
    // AssetStore *AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath);
    // SDL_Texture *GetTexture(const std::string &assetId);
};

#endif /* __ASSETSTORE_H__ */
