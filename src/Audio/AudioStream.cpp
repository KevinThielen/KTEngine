#include "Audio/AudioStream.h"


namespace kte
{


	int audioCallback(const void *input,
		void *output,
		unsigned long frameCount,
		const PaStreamCallbackTimeInfo* paTimeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData)
	{
		AudioData *data = (AudioData *)userData; /* we passed a data structure into the callback so we have something to work with */
		int *cursor; /* current pointer into the output  */
		int *out = (int *)output;
		int thisSize = frameCount;
		int thisRead;

		cursor = out; /* set the output cursor to the beginning */

	
		while (thisSize > 0)
		{
			/* seek to our current file position */
			sf_seek(data->getFile(), data->getPosition(), SEEK_SET);

			/* are we going to read past the end of the file?*/
			if (thisSize > (data->getInfo().frames - data->getPosition()))
			{
				/*if we are, only read to the end of the file*/
				thisRead = data->getInfo().frames - data->getPosition();
				/* and then loop to the beginning of the file */
				//data->setPosition(0);
				

				if (!data->isRepeating())
					return paAbort;
				else
				{
					data->setPosition(0);
				//	*out = 0;
					return paContinue;
				}
			}
			else
			{
				/* otherwise, we'll just fill up the rest of the output buffer */
				thisRead = thisSize;
				/* and increment the file position */
				data->movePosition(thisRead);
			}

		
			
			/* since our output format and channel interleaving is the same as
			sf_readf_int's requirements */
			/* we'll just read straight into the output buffer */
			sf_readf_int(data->getFile(), cursor, thisRead);
			/* increment the output cursor*/
			cursor += thisRead;
			/* decrement the number of samples left to process */
			thisSize -= thisRead;

		}

		return paContinue;
	}





	AudioStream::AudioStream()
	{
		Pa_Initialize();
	}

	AudioStream::~AudioStream()
	{
		Pa_Terminate();
	}


	bool AudioStream::setAudioData(AudioData* data)
	{
		this->data = data;
		restart();
		/* set the output parameters */
		outputParameters.device = Pa_GetDefaultOutputDevice(); /* use the
															   default device */
		outputParameters.channelCount = data->getInfo().channels; /* use the
															   same number of channels as our sound file */
		outputParameters.sampleFormat = paInt32; /* 32bit int format */
		outputParameters.suggestedLatency = 0.1; /* 200 ms ought to satisfy
												 even the worst sound card */
		outputParameters.hostApiSpecificStreamInfo = 0; /* no api specific data */

		/* try to open the output */


		error = Pa_OpenStream(&stream,  /* stream is a 'token' that we need to save for future portaudio calls */
							  0,  /* no input */
							  &outputParameters,
							  data->getInfo().samplerate,  /* use the same sample rate as the sound file */
							  paFramesPerBufferUnspecified,  /* let portaudio choose the buffersize */
							  paNoFlag,  /* no special modes (clip off, dither off) */
							  audioCallback,  /* callback function*/
							  data); /* pass in our data structure so the callback knows what's up */


		/* if we can't open it, then bail out */
		if (error)
		{
			std::cout<<"error opening output, error code = "<<error<<std::endl;
			return false;
		}

		return true;
	}

	void AudioStream::play()
	{
		/* when we start the stream, the callback starts getting called */
		Pa_StartStream(stream);
	}

	void AudioStream::stop()
	{
		Pa_StopStream(stream); // stop the stream
	}

	void AudioStream::restart()
	{
		data->setPosition(0);

	}

	
}