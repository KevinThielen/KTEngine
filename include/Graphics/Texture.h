#ifndef KTE_TEXTURE_H
#define KTE_TEXTURE_H

#include <string>
#include <GL/glew.h>

namespace kte
{
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
	bool loadFromData(std::string data);
	void unload() { glDeleteTextures(1, &texture); }
    private:
        GLuint texture;
    };
}

#endif