#ifndef KTE_TEXTURE_DATA_H
#define KTE_TEXTURE_DATA_H

#include <vector>
#include "IResource.h"

namespace kte 
{	
    struct TextureData : public IResource 
    {
	std::string name;
	unsigned int height;
	unsigned int width;
	std::vector<char> data;
	bool hasAlpha;
    };
}



#endif