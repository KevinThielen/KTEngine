#ifndef KTE_AUDIODATA_H
#define KTE_AUDIODATA_H

#include <sndfile.h>
#include <iostream>

namespace kte
{
    class AudioData
	{
	public:
		bool loadFromFile(std::string path, bool isRepeating = false)
		{
			/* initialize our data structure */
			position = 0;
			sfInfo.format = SF_FORMAT_PCM_32;
			/* try to open the file */
			sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);

			if (!sndFile)
			{
				std::cout << "Error loading AudioFile "<<path<<"\n";
				return false;
			}
			repeating = isRepeating;

			return true;
		}

		void isRepeating(bool repeating) { this->repeating = repeating; }
		bool isRepeating() { return repeating; }

		SNDFILE* getFile() { return sndFile; }
		SF_INFO getInfo() { return sfInfo; }
		int getPosition() { return position; }
		void setPosition(int pos) { position = pos; }
		void movePosition(int delta) { position += delta; }
	private:
		SNDFILE* sndFile;
		SF_INFO sfInfo;
		int position;
		bool repeating;
	};
    
}
    


#endif