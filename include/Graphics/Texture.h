#include <GL/glew.h>

#ifndef KTE_TEXTURE_H
#define KTE_TEXTURE_H


#include <string>
#include <GL/glew.h>

namespace kte
{
    class Texture
    {
    public:
        GLuint getTexture() { return texture; }
        bool loadFromFile(std::string path);
    private:
        GLuint texture;
    };
}


#endif