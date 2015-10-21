
#include <iostream>
#include <Graphics/Texture.h>
#include <Resources/Font.h>
#include <vector>
#include "Utility/SaveTexture.h"
#include <Systems/RenderSystem.h>

namespace kte
{
    bool Texture::create(TextureData textureData)
    {
	glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );


	data = textureData.data;
	
        if(!textureData.hasAlpha)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, &textureData.data[0]);
        else
	{
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width, textureData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textureData.data[0]);
	    
	    for(int i = 3; i<data.size(); i+=4)
	    {
		   alphaMap.push_back(data[i]);
	    }
	}
        glBindTexture(GL_TEXTURE_2D, 0);
	
	RenderSystem::checkGLError("Texture creation "+textureData.name);
    
	this->textureData = textureData;
	alpha = textureData.hasAlpha;
	width = textureData.width;
	height = textureData.height;
	
	return (texture>0);
    }

}