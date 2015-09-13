#ifndef KTE_FONT_TEXTURE_H
#define KTE_FONT_TEXTURE_H

#include <GL/glew.h>
#include "Resources/Font.h"
#include <fstream>
#include <iostream>
namespace kte  
{
    class FontTexture 
    {
    public:

	
    bool loadFromFont(Font font)
    {
	this->font = font;

	 //create the texture atlas
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 ) ;
        glPixelStorei ( GL_PACK_ALIGNMENT, 1 ) ;
	
	std::vector<unsigned char> fontData;
	
	for(int i = 0; i<font.data.size(); i++)
	{
	    fontData.push_back(font.data[i]);
	    fontData.push_back(0);
	    fontData.push_back(0);

	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, font.textureWidth, font.textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, &fontData[0]);
 

	return (texture>0);
    }
    
    Font getFont() { return font; }
    GLuint getTexture() { return texture; }
    
    private:
	GLuint texture;
	Font font;
    };
}
#endif