#include <Graphics/TextureManager.h>

namespace kte
{
    TextureManager::~TextureManager()
    {

    }

    TextureManager* TextureManager::getInstance()
    {
        static TextureManager textureManager;
        return &textureManager;
    }

    Texture* TextureManager::getTexture(std::string name)
    {
        return &textures[name];
    }

    bool TextureManager::initializeDefaultTextures()
    {
        Texture defaultTexture;
        if(!defaultTexture.loadFromFile("Textures/default.png"))
            return false;
        textures["default.png"] = defaultTexture;
        return true;
    }

    bool TextureManager::loadTexture(std::string name)
    {
        Texture tex;
        if(!tex.loadFromFile("Textures/"+name))
            return false;
        textures[name] = tex;
        return true;
    }

}