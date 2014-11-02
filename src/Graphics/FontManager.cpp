#include "Graphics/FontManager.h"

namespace kte
{
    FontManager::~FontManager()
    {

    }

    FontManager* FontManager::getInstance()
    {
        static FontManager FontManager;
        return &FontManager;
    }

    Font* FontManager::getFont(std::string name)
    {
        return &fonts[name];
    }

    bool FontManager::initializeDefaultFonts()
    {
        Font defaultFont;
        if(!defaultFont.loadFromFile("Fonts/default.ttf", 32))
            return false;
        fonts["default.ttf"] = defaultFont;
        return true;
    }

    bool FontManager::loadFont(std::string name, unsigned int size = 16)
    {
     //   Font font;
      //  if(!font.loadFromFile("Fonts/"+name, size))
    //        return false;
  //      fonts[name] = font;
        return true;
    }

}