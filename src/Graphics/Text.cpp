#include <Graphics/Text.h>

namespace kte
{
    void Text::setString(std::string text)
    {
        textString = text;

        float xOffset = 0.0f;
        float yOffset = 0.0f;

        length = text.length();

        for (unsigned int i = 0; i < text.length(); i++)
        {
            char c = text[i];

            if (c == '\n')
            {
                xOffset = 0.0f;
                yOffset += font->getTextureHeight();
            }

            else
            {
                GlyphInformation g = font->getGlyph(c);

                //if (!textureRectangles[c])
                //{
                    rectangles[i].x = xOffset + g.bitmapLeft;
                    rectangles[i].y = yOffset + (font->getTextureHeight() - g.bitmapTop);
                    rectangles[i].z = g.bitmapLeft + g.bitmapWidth;
                    rectangles[i].a = font->getTextureHeight();

                    textureRectangles[i].x = g.textureX;
                    textureRectangles[i].y = 0;
                    textureRectangles[i].z = (g.textureX + g.bitmapWidth) / font->getTextureWidth();
                    textureRectangles[i].a = 1;
                    xOffset += g.advanceX;
            //    }
            }

        }
    }
}