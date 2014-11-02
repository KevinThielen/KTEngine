#ifndef KTE_TEXTURE_MANAGER_H
#define KTE_TEXTURE_MANAGER_H

#include <map>
#include "Texture.h"

namespace kte
{
    class TextureManager
    {
    public:
        ~TextureManager();
        static TextureManager* getInstance();
        Texture* getTexture(std::string name);
        bool initializeDefaultTextures();
        bool loadTexture(std::string path);

    private:
        TextureManager(){}
        std::map<std::string, Texture> textures;
    };
}

#endif