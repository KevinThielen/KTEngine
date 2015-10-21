#ifndef RESOURCES_H
#define RESOURCES_H

#include <Graphics/Texture.h>
#include <Graphics/Animation.h>
#include <Graphics/FontTexture.h>
#include <Resources/ResourcePackage.h>
#include <Audio/AudioBuffer.h>

#include <initializer_list>
#include <iostream>

namespace kte
{
    class Resources
    {
    public:
	~Resources()
	{
	    for(auto& texture : textures)
	    {
		texture.second.unload();
	    }
	}

        bool loadPackage(std::string name)
	{
	   ResourcePackage resourcePackage(name);
	   
	   if(!resourcePackages.count(name))
	   {
		if(!resourcePackage.read())
		    return false;
		
		std::vector<Font> packedFonts = resourcePackage.getFonts();
		
		for(auto& font : packedFonts)
		{
		    FontTexture fontTexture;
		    if(!fonts.count(font.name))
		    {
			if(!fontTexture.loadFromFont(font))
			    return false;
			    
			fonts[font.name] = fontTexture;
		    }
		    else 
		    {
			std::cout<<"WARNING: Font "<<font.name<<" already loaded."<<std::endl;
		    }
		}
		
		std::vector<AudioData> packedAudios = resourcePackage.getAudios();
		
		for(auto& audio : packedAudios)
		{
		    AudioBuffer audioBuffer;
		    if(!audios.count(audio.name))
		    {
			if(!audioBuffer.initialize(audio))
			    return false;
			    
			audios[audio.name] = audioBuffer;
		    }
		    else 
		    {
			std::cout<<"WARNING: Audio "<<audio.name<<" already loaded."<<std::endl;
		    }
		}
		
		std::vector<TextureData> packedTextures = resourcePackage.getTextures();
		
		for(auto& textureData : packedTextures)
		{
		    
		    Texture texture;
		    if(!textures.count(textureData.name))
		    {
			if(!texture.create(textureData))
			    return false;
			textures[textureData.name] = texture;
		    }
		    else 
		    {
			std::cout<<"WARNING: Texture "<<textureData.name<<" already loaded."<<std::endl;
		    }
		}
		
		std::vector<File> packedFiles = resourcePackage.getFiles();
		
		for(auto& fileData : packedFiles)
		{
		    
		    if(!files.count(fileData.name))
		    {
			
			files[fileData.name] = fileData;
		    }
		    else 
		    {
			std::cout<<"WARNING: File "<<fileData.name<<" already loaded."<<std::endl;
		    }
		}
		
		resourcePackages[name]  = resourcePackage;
	   }
	   else 
	   {
	       	std::cout<<"WARNING: Package "<<name<<" already loaded."<<std::endl;
	   }
	   return true;
	}
	

//         TODO: load animation from file
//         bool loadAnimation(std::string name, std::string spriteSheet, std::initializer_list<glm::vec4> frames)
//         {
//             animations[name].name = name;
//             animations[name].spriteSheet = spriteSheet;
// 
//             if(!textures.count(spriteSheet) && !loadTextureFromFile(spriteSheet))
//                 return false;
//             unsigned int frameCounter = 0;
//             for(auto frame : frames)
//             {
//                 animations[name].frames[frameCounter++] = frame;
//             }
//             return true;
//         }


        //AudioDatas
        AudioBuffer* getAudio(std::string name) 
	{ 
	     if(!audios.count(name)) 
		std::cout<<"Audio "<<name<<" not loaded!"<<std::endl; 
		
	    return &audios[name];
	}
        
        Texture* getTexture(std::string name) 
	{ 
	    if(!textures.count(name)) 
	    {
		std::cout<<"Texture "<<name<<" not loaded!"<<std::endl; 
		return nullptr;
	    }
	    return &textures[name];
	    
	}
        Animation* getAnimation(std::string name) { return &animations[name]; }
        
        FontTexture* getFont(std::string name) 
	{
	     if(!fonts.count(name)) 
		std::cout<<"Font "<<name<<" not loaded!"<<std::endl; 
	    
	    return &fonts[name]; 

	}

	File* getFile(std::string name) 
	{
	    if(!files.count(name)) 
		std::cout<<"File "<<name<<" not loaded!"<<std::endl; 
	    
	    return &files[name]; 
	}
	
	void reload() 
	{
	    for(auto& texture : textures)
	    {
		texture.second.reload();
	    }
	}
	
	void unload() 
	{
	    for(auto& texture : textures)
	    {
		texture.second.unload();
	    }
	}
    private:
        std::map<std::string, Texture> textures;
        std::map<std::string, Animation> animations;
        std::map<std::string, FontTexture> fonts;
	std::map<std::string, AudioBuffer> audios;
	std::map<std::string, File> files;
	
	std::map<std::string, kte::ResourcePackage> resourcePackages;
    };
}

#endif