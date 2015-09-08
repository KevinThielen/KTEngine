#ifndef KTE_TEXTURE_H
#define KTE_TEXTURE_H

#include <string>
#include <GL/glew.h>

namespace kte
{
    class Font;
    class Texture
    {
    public:
	~Texture()
	{
	  
	    
	}
	GLuint getTexture()
        {
            return texture;
        }

        bool loadFromFile(std::string path);
	void unload() { glDeleteTextures(1, &texture); }
    private:
        GLuint texture;
    };
}

#endif