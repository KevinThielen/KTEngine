#ifndef RESOURCES_H
#define RESOURCES_H

#include <Graphics/Texture.h>
#include <iostream>
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
            {
                std::cout<<"Error loading "<<path<<std::endl;
                return false;
            }
            textures[name]  = texture;
            return true;
        }

        bool loadTextureFromFile(std::string name)
        {
            Texture texture;
            static std::string ressourcePath = RESOURCE_PATH;

            if(!texture.loadFromFile(ressourcePath+"Textures/"+name))
            {
                std::cout<<"Error loading "<<ressourcePath+"Textures/"+name<<std::endl;
                return false;
            }
            textures[name]  = texture;
            return true;
        }
        Texture* getTexture(std::string name) { return &textures[name];}

    private:
        std::map<std::string, Texture> textures;
    };
}

#endif