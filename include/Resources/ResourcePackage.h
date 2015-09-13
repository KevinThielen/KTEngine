#ifndef KTE_RESSOURCE_PACKAGE_H
#define KTE_RESSOURCE_PACKAGE_H

#include <vector>
#include "Font.h"
#include "TextureData.h"
#include <fstream>

namespace kte 
{
    class ResourcePackage 
    {
    public:
	ResourcePackage(){ }
	ResourcePackage(std::string packageName): packageName(packageName) { }
	void addResource(Font font) { fonts.push_back(font); }
	void addResource(kte::TextureData texture) { textures.push_back(texture); }
	
	void persist();
	bool read();
	
	std::vector<Font> getFonts() { return fonts; }
	std::vector<kte::TextureData> getTextures() { return textures; }
	
	std::string getPackageName() { return packageName; }
    private:
	std::string packageName;
	std::string persistFonts(const char* file);
	std::string persistTextures();
	
	std::vector<Font> fonts; 
	std::vector<kte::TextureData> textures; 
    };
}
#endif