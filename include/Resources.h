#ifndef RESOURCES_H
#define RESOURCES_H

#include <Graphics/Texture.h>

namespace kte
{
    class Resources
    {
    public:
        //Textures
        bool loadTextureFromFile(std::string name, std::string path)
        {
            Texture texture;
            if(!texture.loadFromFile(path))
                return false;

            textures[name]  = texture;
            return true;
        }
        Texture* getTexture(std::string name) { return &textures[name];}

    private:
        std::map<std::string, Texture> textures;
    };
}

#endif