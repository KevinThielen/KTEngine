#ifndef KTE_AUDIO_BUFFER_H
#define KTE_AUDIO_BUFFER_H

#include <vector>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>
#include <fstream>
#include "AudioManager.h"

#include "AudioData.h"
namespace kte 
{
    class AudioBuffer 
    {
    public:
	


	bool loadWaveFromFile(std::string path)
	{
	   
	    
	       if(!audioData.loadWavFromFile(path))
		   return false;

	    
	
		alGenBuffers(1, &buffer);
	       
		AudioManager::checkALError("Audio Buffer generation");

		alBufferData(buffer, (audioData.getChannels() == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16,
			     &audioData.getData().front(), audioData.getData().size()* sizeof(short), audioData.getSampleRate());
		
		AudioManager::checkALError("Set Audio Buffer Data");
		
		
		
		

		return true;
	}

	ALuint getBuffer() { return buffer; }
	
    private:
	ALuint buffer;
	AudioData audioData;
    };
}

#endif