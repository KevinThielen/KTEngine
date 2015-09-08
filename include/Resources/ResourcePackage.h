#ifndef KTE_RESSOURCE_PACKAGE_H
#define KTE_RESSOURCE_PACKAGE_H

#include <vector>
#include "Font.h"
#include <fstream>

namespace kte 
{
    class ResourcePackage 
    {
    public:
	void addResource(Font font) { fonts.push_back(font); }
	
	void persist();
	bool read(const char* file);
	
	std::vector<Font> getFonts() { return fonts; }
	
    private:
	std::string persistFonts();
	
	std::vector<Font> fonts; 
    };
}
#endif