#include "./MeshStore.h"
#include "../Logger/Logger.h"

MeshStore::MeshStore()
{
    Logger::Log("MeshStore created");
};

MeshStore::~MeshStore()
{
    ClearMeshes();
    Logger::Log("MeshStore destroyed");
};

void MeshStore::ClearMeshes()
{
    for (auto mesh : meshes)
    {
        mesh.second->Delete();
    };
    meshes.clear();
};

MeshStore *MeshStore::AddMesh(const std::string &meshId, const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
{
    meshes.insert(
        std::make_pair(
            meshId,
            std::make_shared<Mesh>(vertices, indices)));

    Logger::Log("mesh added to store with id = " + meshId);
    return this;
};

Mesh &MeshStore::GetMesh(const std::string &meshId)
{
    return *(
        std::static_pointer_cast<Mesh>(
            meshes.find(meshId)->second));
};