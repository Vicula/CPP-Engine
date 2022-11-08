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

MeshStore *MeshStore::AddMesh(const std::string &meshId, const GLfloat &vertices, const GLuint &indices)
{
    Mesh *mesh = new Mesh(vertices, indices);
    meshes.emplace(meshId, mesh);

    Logger::Log("mesh added to store with id = " + meshId);
    return this;
};

Mesh *MeshStore::GetMesh(const std::string &meshId)
{
    return meshes[meshId];
};