#ifndef KTE_RESSOURCE_PACKAGE_H
#define KTE_RESSOURCE_PACKAGE_H

#include <vector>
#include "Font.h"
#include "TextureData.h"
#include "File.h"
#include <fstream>
#include "AudioData.h"

namespace kte 
{
    class ResourcePackage 
    {
    public:
	ResourcePackage(){ }
	ResourcePackage(std::string packageName): packageName(packageName) { }
	void addResource(Font font) { fonts.push_back(font); }
	void addResource(TextureData texture) { textures.push_back(texture); }
	void addResource(AudioData audio) { audios.push_back(audio); }
	void addResource(File file) { files.push_back(file); }
	
	void persist();
	bool read();
	
	std::vector<File> getFiles() { return files; }
	std::vector<Font> getFonts() { return fonts; }
	std::vector<AudioData> getAudios() { return audios; }
	std::vector<kte::TextureData> getTextures() { return textures; }
	
	std::string getPackageName() { return packageName; }
    private:
	std::string packageName;
	std::string persistFonts();
	std::string persistTextures();
	std::string persistAudios();
	std::string persistFiles();
	
	std::vector<Font> fonts; 
	std::vector<AudioData> audios; 
	std::vector<TextureData> textures; 
	std::vector<File> files; 
    };
}
#endif