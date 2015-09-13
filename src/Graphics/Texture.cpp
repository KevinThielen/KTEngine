
#include <iostream>
#include <Graphics/Texture.h>
#include <Resources/Font.h>

namespace kte
{
    bool Texture::create(TextureData textureData)
    {
	glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
     //   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );


	
        if(!textureData.hasAlpha)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData.width, textureData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, &textureData.data[0]);
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureData.width, textureData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &textureData.data[0]);

        glBindTexture(GL_TEXTURE_2D, 0);
	return (texture>0);
    }
    
//     bool Texture::loadFromFile(std::string path)
//     {
//         int w,h,comp;
//         unsigned char *data = stbi_load(path.c_str(), &w, &h, &comp, 0);
// 
//         if(data == NULL)
// 	{
// 	    std::cout<<path<< "not found."<<std::endl;
// 	    return false;
// 	}
//         glGenTextures(1, &texture);
// 
//         glBindTexture(GL_TEXTURE_2D, texture);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT);
//         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
//         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
// 
//         if(comp == 3)
//             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//         else if(comp == 4)
//             glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
// 
//         glBindTexture(GL_TEXTURE_2D, 0);
// 
//         stbi_image_free(data);
// 
//         return (texture>0);
//     }
}