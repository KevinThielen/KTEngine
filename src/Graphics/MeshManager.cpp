
#include "Graphics/MeshManager.h"
#include "Graphics/Quad.h"

namespace kte
{
    MeshManager::~MeshManager()
    {
        for(auto iterator = meshes.begin(); iterator!=meshes.end(); iterator++)
            delete iterator->second;
    }
    MeshManager* MeshManager::getInstance()
    {
        static MeshManager meshManager;
        return &meshManager;
    }

    Mesh* MeshManager::getMesh(std::string name)
    {
        return meshes[name];
    }

    bool MeshManager::initializeDefaultMeshes()
    {
        meshes["Quad"] = new Quad();
        return true;
    }

}