#ifndef KTE_SAVE_TEXTURE_H
#define KTE_SAVE_TEXTURE_H

#include <iostream>
#include <fstream>
#include "Graphics/Texture.h"

namespace kte 
{
    
    inline void saveData(std::string filename, int width, int height, std::vector<char> data)
    {
	int x = width;
	int y = height;
	

	long imageSize = x * y;

	//   write header and data to file  
	int xa= x % 256;
	int xb= (x-xa)/256;int ya= y % 256;
	int yb= (y-ya)/256;//assemble the header
	
	
	
	unsigned char header[18]={0,0,2,0,0,0,0,0,0,0,0,0,(unsigned char)xa,(unsigned char)xb,(unsigned char)ya,(unsigned char)yb,24,0};
	std::fstream File(filename, std::ios::out | std::ios::binary);
	File.write (reinterpret_cast<char *>(header), sizeof (char)*18);
	File.write (reinterpret_cast<char *>(&data[0]), sizeof (char)*imageSize*3);
	File.close();
	
    }
    
  
    inline void saveTextureAsTGA(std::string filename, GLuint texture, int w, int h)
    {	

	std::vector<char> data;
	data.resize(w*h*3);
	
	glReadPixels(0.0, 0.0, w, h, GL_BGR, GL_UNSIGNED_BYTE, &data[0]);
	


 saveData(filename, w, h, data); 
    }
    
inline    void saveTextureAsTGA(std::string filename, Texture* texture)
    {	

	std::vector<char> data;
	
	for(int i = 0; i<texture->getData().size(); i++)
	{
 	    if(!texture->hasAlpha() || i%4 == 0)
	    {
		// reverse order, because texture is bgr format
		data.push_back(texture->getData()[i+2]);
		data.push_back(texture->getData()[i+1]);
		data.push_back(texture->getData()[i]);
	    }
	}

	saveData(filename, texture->getWidth(), texture->getHeight(), data); 
    }
    
inline    void saveAlphaMapAsTGA(std::string filename, Texture* texture)
    {	
	//remove the alpha value
	std::vector<char> data;
	
	if(!texture->hasAlpha())
	{
	    std::cout<<"Texture "<<filename<<"has no Alpha values."<<std::endl;
	    return;
	}
	for(int i = 0; i<texture->getAlphaMap().size(); i++)
	{
		data.push_back(texture->getAlphaMap()[i]);
		data.push_back(texture->getAlphaMap()[i]);
		data.push_back(texture->getAlphaMap()[i]);
	}
	saveData(filename, texture->getWidth(), texture->getHeight(), data); 
    }
}

#endif