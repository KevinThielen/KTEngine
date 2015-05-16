#ifndef KTE_FONT_H
#define KTE_FONT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

#include <freetype/ft2build.h>
#include FT_FREETYPE_H

namespace kte
{
    struct GlyphInformation
    {
        float advanceX, advanceY;
        float bitmapWidth, bitmapHeight;
        float bitmapLeft, bitmapTop;
        float textureX;
    };

    class Font
    {
    public:
        bool loadFromFile(std::string path, unsigned fontSize = 16);
        unsigned int getTextureHeight() { return textureHeight; }
        unsigned int getTextureWidth() { return textureWidth; }

        GlyphInformation getGlyph(char c) { return glyphs[(int)c]; }

        GLuint getTexture() { return textureAtlas; }
    private:
        GlyphInformation glyphs[128];

        FT_Face fontFace;
        FT_Library fontLibrary;
        GLuint textureAtlas;

        unsigned int textureWidth;
        unsigned int textureHeight;
        unsigned int fontSize;
    };
}

#endif