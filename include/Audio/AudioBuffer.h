#ifndef KTE_AUDIO_BUFFER_H
#define KTE_AUDIO_BUFFER_H

#include <vector>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <fstream>
#include "AudioManager.h"

#include "Resources/AudioData.h"

namespace kte 
{
    class AudioBuffer 
    {
    public:
	bool initialize(AudioData audio)
	{
		alGenBuffers(1, &buffer);
	       
		AudioManager::checkALError("Audio Buffer generation");

		alBufferData(buffer, (audio.numberOfChannels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
			     &audio.data.front(), audio.data.size()* sizeof(short), audio.sampleRate);
		
		AudioManager::checkALError("Set Audio Buffer Data");
		
		
		return true;
	}

	ALuint getBuffer() { return buffer; }
	
    private:
	ALuint buffer;
    };
}

#endif