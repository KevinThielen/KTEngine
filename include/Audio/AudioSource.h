#ifndef KTE_AUDIO_SOURCE_H
#define KTE_AUDIO_SOURCE_H

#include <AL/al.h>
#include <AL/alc.h>
#include "AudioManager.h"

#include "Resources/AudioData.h"
#include "AudioBuffer.h"

namespace kte
{
    class AudioSource
    {
    public:
	AudioSource()
	{
	}
	
	~AudioSource()
	{
	    alDeleteSources(1, &source);
	}
	bool initialize()
	{
	    alGenSources(1, &source);

	    alSourcef(source, AL_PITCH, 1);
	    alSourcef(source, AL_GAIN, 1);
	    alSource3f(source, AL_POSITION, 0, 0, 0);
	    alSource3f(source, AL_VELOCITY, 0, 0, 0);
	    alSourcei(source, AL_LOOPING, AL_FALSE);
	    
	    AudioManager::checkALError("Audio source generation");
	    looping = false;
	  
	    
	    return true;
	}
	
	void play(AudioBuffer* buffer, bool looping = false) { playSound(buffer, looping); } 
	void playSound(AudioBuffer* buffer, bool looping = false)
	{
	    alSourceStop(source);
	    if(looping)
		alSourcei(source, AL_LOOPING, AL_TRUE);
	    else 
		alSourcei(source, AL_LOOPING, AL_FALSE);
	
	    this-> looping = looping;
	    alSourcei(source, AL_BUFFER, buffer->getBuffer());
	    if(!Sound::muted)
		alSourcef(source, AL_GAIN, Sound::masterVolume);
	    else 
		alSourcef(source, AL_GAIN, 0.0f);
	    
	    alSourcePlay(source);
	    AudioManager::checkALError("Play Buffer");
	}

	
	void playMusic(AudioBuffer* buffer, bool looping = true)
	{
	    if(looping)
		alSourcei(source, AL_LOOPING, AL_TRUE);
	    else 
		alSourcei(source, AL_LOOPING, AL_FALSE);
	
	    this-> looping = looping;
	    
	    alSourceStop(source);
	    alSourcei(source, AL_BUFFER, buffer->getBuffer());
	    if(!Music::muted)
		alSourcef(source, AL_GAIN, Music::masterVolume);
	    else 
		alSourcef(source, AL_GAIN, 0.0f);
	    
	    alSourcePlay(source);
	    AudioManager::checkALError("Play Buffer");
	}
	

	
    private:
	bool looping;
	ALuint source;
    };
}

#endif