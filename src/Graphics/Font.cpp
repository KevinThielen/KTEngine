#include "Graphics/Font.h"

namespace kte
{
    bool Font::loadFromFile(std::string path, unsigned int fontSize)
    {
        textureWidth = 0;
        textureHeight = 0;

        if (FT_Init_FreeType(&fontLibrary)) {
            std::cout << "Could not initialize freetype library"<<std::endl;
            return false;
        }

        if (FT_New_Face(fontLibrary, path.c_str(), 0, &fontFace)) {
            std::cout <<  "Failed to load font: \"" << path <<std::endl;
            return false;
        }

        FT_Set_Pixel_Sizes(fontFace, 0, fontSize);
        this->fontSize = fontSize;

        //calc the width and height of the font texture atlas
        FT_GlyphSlot g = fontFace->glyph;

        textureHeight = 0;
        for (int i = 32; i <128; i++)
        {
            if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER))
            {
                std::cout << "Error loading character " << (char)i << " in " << path<<std::endl;
                continue;
            }

            textureWidth += g->bitmap.width;

            unsigned int charHeight = g->bitmap.rows;
            if (charHeight > textureHeight)
                textureHeight = charHeight;
        }

        //create the texture atlas

        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &textureAtlas);
        glBindTexture(GL_TEXTURE_2D, textureAtlas);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, textureWidth, textureHeight, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

        //load the glyphs and put them in the texture
        int x = 0;

        for (int i = 32; i < 128; i++) {
            if (FT_Load_Char(fontFace, i, FT_LOAD_RENDER))
                continue;

            glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);



            //add the glyph information
            glyphs[i].advanceX = g->advance.x >> 6;
            glyphs[i].advanceY = g->advance.y >> 6;

            glyphs[i].bitmapWidth = g->bitmap.width;
            glyphs[i].bitmapHeight = g->bitmap.rows;

            glyphs[i].bitmapLeft = g->bitmap_left;
            glyphs[i].bitmapTop = g->bitmap_top;

            glyphs[i].textureX = (float)x / textureWidth;
            x += g->bitmap.width;
        }
        FT_Done_Face(fontFace);
        FT_Done_FreeType(fontLibrary);
        return true;
    }
}