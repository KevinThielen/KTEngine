#ifndef RESOURCES_H
#define RESOURCES_H

#include <Graphics/Texture.h>
#include <Graphics/Animation.h>
#include <Resources/Font.h>
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

        bool loadFontFromFile(std::string name, unsigned int size = 16)
        {
            Font font;
            static std::string ressourcePath = RESOURCE_PATH;

            if(!font.loadFromFile(ressourcePath+"Fonts/"+name, size))
            {
                std::cout<<"Error loading "<<ressourcePath+"Fonts/"+name<<std::endl;

                return false;
            }

            fonts[name] = font;
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
        
        Font* getFont(std::string name) 
	{
	     if(!fonts.count(name)) 
		std::cout<<"Font "<<name<<" not loaded!"<<std::endl; 
	      
	    return &fonts[name]; 

	}

    private:
        std::map<std::string, Texture> textures;
        std::map<std::string, Animation> animations;
        std::map<std::string, Font> fonts;
	std::map<std::string, AudioBuffer> sounds;
    };
}

#endif