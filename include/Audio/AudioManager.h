#ifndef AUDIO_DEVICE_MANAGER_H
#define AUDIO_DEVICE_MANAGER_H

#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>
#include <vector>
#include <cstring>
#include <map>

namespace kte
{
    class AudioSource;
    namespace Sound 
    {
	extern float masterVolume ;
	extern bool muted;
    }
    namespace Music 
    {
	extern float masterVolume ;
	extern bool muted;
    }


    class AudioManager
    {
    public:
	
	~AudioManager();
	
	bool initializeAudioDevice()
	{
	 
	    if(!alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT"))
		std::cout<<"Enumeration not available!"<<std::endl;
	
	    std::cout<<"\nAvailable audio devices:"<<std::endl;
	    
	    std::vector<std::string> devices = getAudioDevices();
	    
	    for(auto device : devices)
	    {
		std::cout<<"\t"<<device<<std::endl;
	    }
	    
	   const ALCchar* defaultDeviceName = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	    
	    //flush previous errors
	    checkALError();
	    
	    audioDevice = alcOpenDevice(defaultDeviceName);
	    if(!audioDevice)
	    {
		std::cout<<"Failed to open the audio device"<<std::endl;
		return false;
	    }

	    checkALError("Open audio device");   
		
	    
	    context = alcCreateContext(audioDevice, nullptr);
	    if(!alcMakeContextCurrent(context))
	    {
		std::cout<<"Failed to set audio context"<<std::endl;
		return false;
	    }
	    checkALError("Set audio context");
	    
	    return true;
	}
	
	std::vector<std::string> getAudioDevices()
	{
	    std::vector<std::string> availableDevices;
	    
	    const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
	    const ALCchar* next = devices+1;
	    size_t length = 0;
	    
	    
	    while (devices && *devices != '\0' && next && *next != '\0') 
	    {
		availableDevices.push_back(std::string(devices));
		length = std::strlen(devices);
		devices += (length + 1);
		next += (length + 2);
	    };
	    
	    //default listener
	    ALfloat listenerOrientation[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	    alListener3f(AL_POSITION, 0, 0, 1.0f);
	    alListener3f(AL_VELOCITY, 0, 0, 0);
	    alListenerfv(AL_ORIENTATION, listenerOrientation);
	    
	    return availableDevices;
	}
    
	void update();
	void release()
	{
	    alcMakeContextCurrent(NULL);
	    alcDestroyContext(context);
	    alcCloseDevice(audioDevice);
	}
	
	static bool checkALError(std::string message = "") 
	{
	    ALenum error = alGetError();
	    if(error == AL_NO_ERROR)
		return false;
	    else
	    {
		std::cout<<"AL_ERROR: "<<getErrorString(error)<<"\n"<<message<<std::endl;
		return true;
	    }
	}
	
	void addAudioSource(AudioSource* audioSource);
	void removeAudioSource(AudioSource* audioSource); 
	
	
	void setMusicVolume(float volume);
	void setSoundVolume(float volume);
	void muteMusic(bool mute);
	void muteSound(bool mute);
	
    private:
	
	static std::string getErrorString(ALenum error)
	{
	    switch (error)
	    {
		case AL_INVALID_NAME: return "Invalid name param"; break;
		case AL_INVALID_ENUM: return "Invalid param"; break;
		case AL_INVALID_VALUE: return "Invalid enum-Param"; break;
		case AL_INVALID_OPERATION: return "Invalid operation"; break;
		case AL_OUT_OF_MEMORY: return "Out of memory"; break;
		default: return "unknown error";
	    }
	}
	
	ALCdevice* audioDevice;
	ALCcontext* context;
	std::map<ALuint, AudioSource*> audioSources;
	bool musicMuted;
	bool soundMuted;
	
	float musicVolume;
	float soundVolume;
    };
}

#endif