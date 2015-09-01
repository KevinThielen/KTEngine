#ifndef KTE_AUDIODATA_H
#define KTE_AUDIODATA_H


#include <iostream>
#include <vector>
#include <fstream>
#include "AudioManager.h"

namespace kte
{
    class AudioData
	{
	public:
		//TODO: external bit shifting, dependend on endian
		bool loadWavFromFile(std::string path, bool isRepeating = false)
		{
		    std::ifstream file(path, std::ios::binary);
	    
		    if(!file.is_open())
		    {
			std::cout<<"Unable to open "<<path<<std::endl;
			return false;
		    }
		    
		    char  id[4];
		    
		    bool result = false;
		    
		    //check header
		    file.read(id, 4);

		    if(!std::strncmp(id, "RIFF", 4))
		    {
			std::cout<<"RIFF test passed"<<std::endl;
			file.read(id, 4);
			
			
			file.read(id, 4);

			uint32_t combined;
	
			if(!strncmp(id, "WAVE", 4))
			{
			    //confirmed wave file
			    file.read(id, 4);   //"fmt " chunk begin
			    //Format length
			    file.read(id, 4);	
			    //Format Type
			    file.read(id, 2);	

			
			    //number of channels
			    file.read(id, 2);	
			    combined = (((int8_t) id[1])<< 8);
			    combined = combined | (((int8_t) id[0]));		
			    numberOfChannels = combined;

			    //sample rate
			    file.read(id, 4);   //sample rate
			    combined = ((( uint8_t) id[3])<< 24);
			    combined = combined | ((( uint8_t) id[2])<< 16);
			    combined = combined | ((( uint8_t) id[1])<< 8);
			    combined = combined | ((( uint8_t) id[0]));

			    sampleRate = combined;
			    
			    file.read(id, 4);	// (Sample rate * bits per sample * channels ) / 8
			    file.read(id, 2);	//block align
			    
			    //bits per sample
			    file.read(id, 2);	//bits per sample
			    combined = 0;
			    combined = ((uint8_t) id[1]<<8);
			    combined = ((uint8_t) id[0]);
			    bitsPerSample = combined;
			    
			    
			    //"data"
			    
			    do 
			    {
				file.read(id, 4);
				 std::cout<<"Received: "<<id<<std::endl;
				if(!file)
				{
				    std::cout<<"Wrong file format!(DATA check failed). Received: "<<id<<" instead !"<<std::endl;
				    return false;
				}
			    }
			    
			    while(strncmp(id, "data", 4));
			    
				//number of Frames
				file.read(id, 4);	
				combined = ((( uint8_t) id[3])<< 24);
				combined = combined | ((( uint8_t) id[2])<< 16);
				combined = combined | ((( uint8_t) id[1])<< 8);
				combined = combined | ((( uint8_t) id[0]));
				numberOfFrames = combined;
				
				const int blockSize = bitsPerSample / 8;
				
				for(int i = 0; i<numberOfFrames; i++)
				{
				    file.read(id, blockSize);	//data
				    
				    
				    combined = 0;
				    if(blockSize == 4)
				    {
					combined = combined | ((( uint8_t) id[3])<< 24);    
					combined = combined | ((( uint8_t) id[2])<< 16);   
				    }
				   
				    combined = combined | ((( uint8_t) id[1])<< 8);    
				    combined = combined | ((( uint8_t) id[0]));
				    data.push_back(combined);
				}
				result = true;
			}
			else 
			    std::cout<<"Wrong file format!(WAVE check failed)"<<std::endl;
		    }
		    else
			std::cout<<"Wrong file format!(RIFF check failed)"<<std::endl;

		    file.close();
		    
		    
		    return result;
		}

		int getChannels() { return numberOfChannels; }
		int getSampleRate() { return sampleRate; }
		
		std::vector<short> getData() { return data; }
	private:
	    int sampleRate;
	    int numberOfChannels;
	    int numberOfFrames;
	    short bitsPerSample;
	    std::vector<short> data;
	};
}
    


#endif