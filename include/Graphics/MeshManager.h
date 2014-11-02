#ifndef KTE_MESH_MANAGER_H
#define KTE_MESH_MANAGER_H

#include <map>
#include "Mesh.h"

namespace kte
{
    class MeshManager
    {
    public:
        ~MeshManager();
        static MeshManager* getInstance();
        Mesh* getMesh(std::string name);
        bool initializeDefaultMeshes();

    private:
        MeshManager(){}
        std::map<std::string, Mesh*> meshes;
    };
}

#endif