#ifndef KTE_TEXTURE_H
#define KTE_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "Resources/TextureData.h"

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

        bool create(TextureData textureData);
	void unload() { glDeleteTextures(1, &texture); }
	
    private:
        GLuint texture;
    };
}

#endif