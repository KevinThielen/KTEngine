#ifndef KTE_FONT_MANAGER_H
#define KTE_FONT_MANAGER_H

#include <map>
#include "Font.h"

namespace kte
{
    class FontManager
    {
    public:
        ~FontManager();
        static FontManager* getInstance();
        Font* getFont(std::string name);
        bool initializeDefaultFonts();
        bool loadFont(std::string path, unsigned int size);

    private:
        FontManager(){}
        std::map<std::string, Font> fonts;
    };
}

#endif