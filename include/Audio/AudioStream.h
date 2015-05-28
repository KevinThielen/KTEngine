#ifndef KTE_AUDIOSTREAM_H
#define KTE_AUDIOSTREAM_H

#include <portaudio.h>
#include "AudioData.h"

namespace kte
{	
	class AudioStream
	{
	public:
		AudioStream();
		~AudioStream();
		bool setAudioData(AudioData* data);
		void play();
		void stop();
		void restart();
	private:
		PaStream* stream;
		PaError error;
		PaStreamParameters outputParameters;
		AudioData* data;
	};
}

#endif