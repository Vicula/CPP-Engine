#include "./AssetStore.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL_image.h>

AssetStore::AssetStore()
{
    Logger::Log("AssetStore created");
};

AssetStore::~AssetStore()
{
    ClearAssets();
    Logger::Log("AssetStore destroyed");
};

void AssetStore::ClearAssets()
{
    for (auto texture : textures)
    {
        SDL_DestroyTexture(texture.second);
    };
    textures.clear();
};

AssetStore *AssetStore::AddTexture(SDL_Renderer *renderer, const std::string &assetId, const std::string &filePath)
{
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    textures.emplace(assetId, texture);
    Logger::Log("asset added with id = " + assetId);
    return this;
};

SDL_Texture *AssetStore::GetTexture(const std::string &assetId)
{
    return textures[assetId];
};