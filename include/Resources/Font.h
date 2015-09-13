#ifndef KTE_FONT_H
#define KTE_FONT_H

#include <map>
#include <vector>
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
	float fontSize;
	unsigned int textureHeight;
	unsigned int textureWidth;
	std::map<char, GlyphInformation> glyphs;
	std::vector<char> data;
    };
}

#endif