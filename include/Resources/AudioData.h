#ifndef KTE_AUDIODATA_H
#define KTE_AUDIODATA_H

#include "IResource.h"
#include <vector>

namespace kte
{
    struct AudioData : IResource
    {
	int sampleRate;
	int numberOfChannels;
	int numberOfFrames;
	std::vector<short> data;
    };
}
    
#endif