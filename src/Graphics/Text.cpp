#include <Graphics/Text.h>

namespace kte
{
    void Text::setString(std::string text)
    {
        textString = text;
	    
        float xOffset = 0.0f;
        float yOffset = 0.0f;
	deltaY = 0.0f;
        length = text.length();

	rectangles.clear();
	textureRectangles.clear();
	
        for (unsigned int i = 0; i < text.length(); i++)
        {
            char c = text[i];

            if (c == '\n')
            {
                xOffset = 0.0f;
                yOffset += fontTexture->getFont().textureHeight;
            }

            else
            {
                GlyphInformation g = fontTexture->getFont().glyphs[c];

                //if (!textureRectangles[c])
                //{
		    float textureX = (float)g.textureX / fontTexture->getFont().textureWidth;
                    int positionY = fontTexture->getFont().textureHeight - g.bitmapTop;
		    
		    rectangles[i].x = xOffset + g.bitmapLeft + textureX;
                    rectangles[i].y = yOffset + positionY;
                    rectangles[i].z = g.bitmapWidth;
                    rectangles[i].a = g.bitmapHeight;
		    if(deltaY+10 < -positionY || deltaY >= 0.0f)
			deltaY = -positionY;
	
                    textureRectangles[i].x = textureX;
                    textureRectangles[i].y = 0;
                    textureRectangles[i].z = (float)(g.bitmapWidth) /  fontTexture->getFont().textureWidth;
                    textureRectangles[i].a = (float)(g.bitmapHeight) /  fontTexture->getFont().textureHeight;
	    		    

                    xOffset += g.advanceX;
            //    }
            }
        }
    }
}