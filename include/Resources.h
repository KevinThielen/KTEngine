#ifndef RESOURCES_H
#define RESOURCES_H

#include <Graphics/Texture.h>
#include <Graphics/Animation.h>
#include <initializer_list>
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
            if(!texture.loadFromFile(path+name))
            {
                std::cout<<"Error loading "<<path+name<<std::endl;
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

        //TODO: load animation from file
        bool loadAnimation(std::string name, std::string spriteSheet, std::initializer_list<glm::vec4> frames)
        {
            animations[name].name = name;
            animations[name].spriteSheet = spriteSheet;

            unsigned int frameCounter = 0;
            for(auto frame : frames)
            {
                animations[name].frames[frameCounter++] = frame;
            }
            return true;
        }

        Texture* getTexture(std::string name) { return &textures[name];}
        Animation* getAnimation(std::string name) { return &animations[name]; }

    private:
        std::map<std::string, Texture> textures;
        std::map<std::string, Animation> animations;
    };
}

#endif