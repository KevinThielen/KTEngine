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
	void unload() { glDeleteTextures(1, &texture); texture = 0;}
	void reload() { create(textureData); }
	
	
	int getWidth() { return width; }
	int getHeight() { return height; }
	
	bool hasAlpha() { return alpha; }
	std::vector<char> getData() { return data; }
	std::vector<char> getAlphaMap() { return alphaMap; }
	std::string getName() { return textureData.name; }
    private:
        GLuint texture;
	int width;
	int height;
	bool alpha; 
	std::vector<char> alphaMap;
	std::vector<char> data;
	TextureData textureData;
    };
}

#endif