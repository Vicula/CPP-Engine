#include "./ShaderStore.h"
#include "../Logger/Logger.h"

ShaderStore::ShaderStore()
{
    Logger::Log("ShaderStore created");
};

ShaderStore::~ShaderStore()
{
    ClearShaders();
    Logger::Log("ShaderStore destroyed");
};

void ShaderStore::ClearShaders()
{
    for (auto shader : shaders)
    {
        shader.second->Delete();
    };
    shaders.clear();
};

ShaderStore *ShaderStore::AddShader(const std::string &shaderId, const std::string &vertShader, const std::string &fragShader)
{
    shaders.insert(
        std::make_pair(
            shaderId,
            std::make_shared<Shader>(vertShader, fragShader)));

    Logger::Log("shader program added to store with id = " + shaderId);
    return this;
};

Shader &ShaderStore::GetShader(const std::string &shaderId)
{
    return *(
        std::static_pointer_cast<Shader>(
            shaders.find(shaderId)->second));
};