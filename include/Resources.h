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
	
        //Textures
        bool loadTextureFromFile(std::string name, std::string path)
        {
            Texture texture;
            if(!texture.loadFromFile(path+name))
            {
                std::cout<<"Error loading "<<path+name<<std::endl;
                return false;
            }
            textures[name]  = texture;
            return true;
        }

        bool loadTextureFromFile(std::string name)
        {
            Texture texture;
            static std::string ressourcePath = RESOURCE_PATH;

            if(!texture.loadFromFile(ressourcePath+"Textures/"+name))
            {
                std::cout<<"Error loading "<<ressourcePath+"Textures/"+name<<std::endl;
                return false;
            }
            textures[name]  = texture;
            return true;
        }

        bool loadPackage(std::string name)
	{
	   ResourcePackage resourcePackage;
	   if(!resourcePackage.read(name.c_str()))
	       return false;
	   
	   std::vector<Font> packedFonts = resourcePackage.getFonts();
	   
	   for(auto& font : packedFonts)
	   {
	       FontTexture fontTexture;
	       if(!fontTexture.loadFromFont(font))
		   return false;
	       fonts[font.name] = fontTexture;
	   }
	   
	   return true;
	}
	
        bool loadFontFromFile(std::string name, unsigned int size = 16)
        {
         
            return true;
        }
         
        bool loadAudioFromFile(std::string name)
        {
            AudioBuffer sound;
            static std::string ressourcePath = RESOURCE_PATH;

            if(!sound.loadWaveFromFile(ressourcePath+"Audio/"+name))
            {
                std::cout<<"Error loading "<<ressourcePath+"Audio/"+name<<std::endl;

                return false;
            }
            sounds[name] = sound;
            return true;
        }

        bool loadMusicFromFile()
	{
	    return true;
	}
        //TODO: load animation from file
        bool loadAnimation(std::string name, std::string spriteSheet, std::initializer_list<glm::vec4> frames)
        {
            animations[name].name = name;
            animations[name].spriteSheet = spriteSheet;

            if(!textures.count(spriteSheet) && !loadTextureFromFile(spriteSheet))
                return false;
            unsigned int frameCounter = 0;
            for(auto frame : frames)
            {
                animations[name].frames[frameCounter++] = frame;
            }
            return true;
        }


        //AudioDatas
        AudioBuffer* getAudio(std::string name) { return &sounds[name]; }
        
        Texture* getTexture(std::string name) 
	{ 
	    if(!textures.count(name)) 
		std::cout<<"Texture "<<name<<" not loaded!"<<std::endl; 
	    
	    return &textures[name];
	    
	}
        Animation* getAnimation(std::string name) { return &animations[name]; }
        
        FontTexture* getFont(std::string name) 
	{
	     if(!fonts.count(name)) 
		std::cout<<"Font "<<name<<" not loaded!"<<std::endl; 
	    
	    return &fonts[name]; 

	}

    private:
        std::map<std::string, Texture> textures;
        std::map<std::string, Animation> animations;
        std::map<std::string, FontTexture> fonts;
	std::map<std::string, AudioBuffer> sounds;
	
	std::vector<kte::ResourcePackage> resourcePackages;
    };
}

#endif