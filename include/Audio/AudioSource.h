#ifndef KTE_AUDIO_SOURCE_H
#define KTE_AUDIO_SOURCE_H

#include <AL/al.h>
#include <AL/alc.h>
#include "AudioManager.h"

#include "AudioData.h"
#include "AudioBuffer.h"

namespace kte
{
    class AudioSource
    {
    public:
	AudioSource()
	{
	}
	
	bool initialize()
	{
	    alGenSources((ALuint)1, &source);

	    alSourcef(source, AL_PITCH, 1);
	    alSourcef(source, AL_GAIN, 1);
	    alSource3f(source, AL_POSITION, 0, 0, 0);
	    alSource3f(source, AL_VELOCITY, 0, 0, 0);
	    alSourcei(source, AL_LOOPING, AL_FALSE);
	    
	    AudioManager::checkALError("Audio source generation");
	    
	  
	    
	    return true;
	}
	
	void play(AudioBuffer* buffer)
	{
	    alSourcei(source, AL_BUFFER, buffer->getBuffer());
	    alSourcePlay(source);
	    AudioManager::checkALError("Play Buffer");
	}
	
    private:
	
	ALuint source;
    };
}

#endif