#ifndef FONT_H
#define FONT_H

#include <map>
#include "IResource.h"

namespace kte 
{
    struct GlyphInformation
	{
	    unsigned int advanceX, advanceY;
	    unsigned int bitmapWidth, bitmapHeight;
	    unsigned int bitmapLeft, bitmapTop;
	    unsigned int textureX;
	};

	
    struct Font : public IResource 
    {
	std::string name;
	float fontSize;
	unsigned int textureHeight;
	unsigned int textureWidth;
	std::map<char, GlyphInformation> glyphs;
	std::vector<unsigned char> data;
    };
}

#endif