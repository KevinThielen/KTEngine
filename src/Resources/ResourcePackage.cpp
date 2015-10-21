#include "Resources/ResourcePackage.h"

#include <iostream>

void kte::ResourcePackage::persist()
{
//    std::string header = "KTE";
    
    
    std::string fontData = persistFonts();
    std::string textureData = persistTextures();
    std::string audioData = persistAudios();
    std::string fileData = persistFiles();
    
    std::fstream file(packageName, std::ios::binary | std::ios::out );
    
    file.write(fontData.c_str(), fontData.size());
    file.write(textureData.c_str(), textureData.size());
    file.write(audioData.c_str(), audioData.size());
    file.write(fileData.c_str(), fileData.size());
    
    file.close();
}

std::string kte::ResourcePackage::persistFiles()
{
    std::string fileData;
    
    int numberOfFiles = files.size();
    
    fileData += (char) numberOfFiles;
    
    for(auto& file : files)
    {
	std::cout<<"Packing file "<<file.name<<".."<<std::endl;
	
	
	//1 byte name Length
	uint8_t nameLength = file.name.size();
	fileData += (char)nameLength;
	
	fileData += file.name;
	
	//4 byte texture data length
	uint8_t dataLength[4];
	uint32_t dataLengthRaw = file.content.size();
	dataLength[0] = dataLengthRaw >> 24;
	dataLength[1] = dataLengthRaw >> 16;
	dataLength[2] = dataLengthRaw >> 8;
	dataLength[3] = dataLengthRaw;

	fileData += (char) dataLength[0];
        fileData+= (char) dataLength[1];
	fileData += (char) dataLength[2];
	fileData += (char) dataLength[3];
	
	
	fileData += file.content;
	std::cout<<"Done."<<std::endl;
    }
    return fileData;
}

std::string kte::ResourcePackage::persistAudios()
{
    std::string audioData;
    int numberOfAudios = audios.size();
    audioData += (char)numberOfAudios;
    
    for(auto audio : audios)
    {
	std::cout<<"\nPacking audio "<<audio.name<<".."<<std::endl;
	//1 byte name Length
	uint8_t nameLength = audio.name.size();
	audioData += (char)nameLength;
	
	
	
	const char* audioName = audio.name.c_str();
	audioData += audio.name;
	
	//1 byte channels TODO: can be shortened to a single bit 
	uint8_t channels = audio.numberOfChannels;
	audioData += (char) channels;
	
	//4 byte samplerate
	uint8_t sampleRate[4];
	uint32_t sampleRateRaw = audio.sampleRate;
	sampleRate[0] = sampleRateRaw >> 24;
	sampleRate[1] = sampleRateRaw >> 16;
	sampleRate[2] = sampleRateRaw >> 8;
	sampleRate[3] = sampleRateRaw;
	
	audioData += (char) sampleRate[0];
        audioData += (char) sampleRate[1];
	audioData += (char) sampleRate[2];
        audioData += (char) sampleRate[3];
	
	//4 byte number of frames //TODO: can be optional, depending on the number of frames
	uint8_t numberOfFrames[4];
	uint32_t numberOfFramesRaw = audio.numberOfFrames;
	numberOfFrames[0] = numberOfFramesRaw >> 24;
	numberOfFrames[1] = numberOfFramesRaw >> 16;
	numberOfFrames[2] = numberOfFramesRaw >> 8;
	numberOfFrames[3] = numberOfFramesRaw;
	
	audioData += (char) numberOfFrames[0];
        audioData += (char) numberOfFrames[1];
	audioData += (char) numberOfFrames[2];
        audioData += (char) numberOfFrames[3];
	
	//4 byte number of frames
	uint8_t dataLength[4];
	uint32_t dataLengthRaw = audio.data.size();
	dataLength[0] = dataLengthRaw >> 24;
	dataLength[1] = dataLengthRaw >> 16;
	dataLength[2] = dataLengthRaw >> 8;
	dataLength[3] = dataLengthRaw;
	
	audioData += (char) dataLength[0];
        audioData += (char) dataLength[1];
	audioData += (char) dataLength[2];
        audioData += (char) dataLength[3];
	
	//copy audio data byte by byte
	std::vector<unsigned char> data;
	data.resize(dataLengthRaw);
	
	for(int i = 0; i<dataLengthRaw; i++)
	{
	    char dataByte[2];
	    int32_t dataRaw = audio.data[i];
	    dataByte[0] = dataRaw >> 8;
	    dataByte[1] = dataRaw;
	    
	    data[i] = audio.data[i];
	    audioData += (char) dataByte[0];
	    audioData += (char) dataByte[1];
	}
	std::cout<<"Done."<<std::endl;
    }
    return audioData;
}

std::string kte::ResourcePackage::persistTextures()
{
    std::string textureData;

    
    
    int numberOfTextures = textures.size();
    textureData += (char)numberOfTextures;
    
    for(auto& texture : textures)
    {
	std::cout<<"\nPacking texture "<<texture.name<<".."<<std::endl;
	
	//1 byte name Length
	uint8_t nameLength = texture.name.size();
	textureData += (char)nameLength;
	
	
	
	const char* textureName = texture.name.c_str();

	textureData += texture.name;
	
	char hasAlpha = 'F';
	//1 byte has alpha component
	if(texture.hasAlpha)
	    hasAlpha = 'T';

	textureData += hasAlpha;
	
	//2 byte texture width/height    
	uint32_t textureHeightRaw = texture.height;
	uint8_t textureHeight[2];
	textureHeight[0] = textureHeightRaw >> 8;
	textureHeight[1] = textureHeightRaw >> 0;

	textureData += (char) textureHeight[0];
        textureData += (char) textureHeight[1];
	
	uint32_t textureWidthRaw = texture.width;
	uint8_t textureWidth[2];
	textureWidth[0] = textureWidthRaw >> 8;
	textureWidth[1] = textureWidthRaw >> 0;

	textureData += (char) textureWidth[0];
        textureData += (char) textureWidth[1]; 
	
	
	//4 byte texture data length
	uint8_t dataLength[4];
	uint32_t dataLengthRaw = texture.data.size();
	dataLength[0] = dataLengthRaw >> 24;
	dataLength[1] = dataLengthRaw >> 16;
	dataLength[2] = dataLengthRaw >> 8;
	dataLength[3] = dataLengthRaw;

	textureData += (char) dataLength[0];
        textureData += (char) dataLength[1];
	textureData += (char) dataLength[2];
        textureData += (char) dataLength[3];
	
	std::vector<unsigned char> data;
	data.resize(dataLengthRaw);

	//copy texture data byte by byte
	for(int i = 0; i<dataLengthRaw; i++)
	{
	    data[i] = texture.data[i];
	    textureData += texture.data[i];
	}

	std::cout<<"Done."<<std::endl;
	
    }
    	
    return textureData;
}


std::string kte::ResourcePackage::persistFonts()
{
    std::string fontData;

    
    //write the information into a file
//     std::fstream file(filename, std::ios::binary | std::ios::out );
    
    
    int numberOfFonts = fonts.size();
//     file.write((char*) &numberOfFonts, 1);
    
    fontData += (char) numberOfFonts;
    for(auto& font : fonts)
    {
	std::cout<<"\nPacking font "<<font.name<<".."<<std::endl;
	
	//1 byte name Length
	uint8_t nameLength = font.name.size();
// 	file.write((char*) &nameLength, 1);
	fontData += (char) nameLength;
	
// 	const char* fontName = font.name.c_str();
// 	file.write(fontName,  font.name.size());
	fontData += font.name;
	
	uint8_t fontSize = font.fontSize;
// 	file.write((char*) &fontSize, 1);
	fontData += (char) fontSize;
	
	//2 byte texture width/height    
	uint32_t textureHeightRaw = font.textureHeight;
	uint8_t textureHeight[2];
	textureHeight[0] = textureHeightRaw >> 8;
	textureHeight[1] = textureHeightRaw >> 0;
// 	file.write((char*) &textureHeight, 2);
	fontData += (char)textureHeight[0];
	fontData += (char)textureHeight[1];

	uint32_t textureWidthRaw = font.textureWidth;
	uint8_t textureWidth[2];
	textureWidth[0] = textureWidthRaw >> 8;
	textureWidth[1] = textureWidthRaw >> 0;
// 	file.write((char*) &textureWidth, 2);
	fontData += (char)textureWidth[0];
	fontData += (char)textureWidth[1];
	 
	//4 byte texture data length
	uint8_t dataLength[4];
	uint32_t dataLengthRaw = font.data.size();
	dataLength[0] = dataLengthRaw >> 24;
	dataLength[1] = dataLengthRaw >> 16;
	dataLength[2] = dataLengthRaw >> 8;
	dataLength[3] = dataLengthRaw;
// 	file.write((char*) &dataLength, 4);
	 fontData += (char) dataLength[0];
	 fontData += (char) dataLength[1];
	 fontData += (char) dataLength[2];
	 fontData += (char) dataLength[3];
	 
	std::vector<unsigned char> data;
	data.resize(dataLengthRaw);

	//copy texture data byte by byte
	for(int i = 0; i<dataLengthRaw; i++)
	{
	    data[i] = font.data[i];
	    fontData += font.data[i];
	    
	}

// 	file.write((char*) &data[0], dataLengthRaw);
	
	
	
	//copy the glyph informations
	uint32_t glyphSizeRaw = font.glyphs.size();
	uint8_t glyphSize[2];
	glyphSize[0] = glyphSizeRaw >> 8;
	glyphSize[1] = glyphSizeRaw >> 0;
	
// 	file.write((char*) &glyphSize, 2);
	fontData += (char) glyphSize[0];
	fontData += (char) glyphSize[1];
		
	
		
	std::map<char, std::vector<uint8_t>> glyphs;
	for(auto& glyph : font.glyphs)
	{
	    uint8_t glyphBytes[7][4];
	    
	    
	    char glyphCharacter = glyph.first;
// 	    file.write((char*) &glyphCharacter, 1);
	    fontData += glyphCharacter;
	    
	    std::vector<unsigned int> glyphInformation;
	    glyphInformation.push_back(glyph.second.advanceX);
	    glyphInformation.push_back(glyph.second.advanceY);
	    glyphInformation.push_back(glyph.second.bitmapWidth);
	    glyphInformation.push_back(glyph.second.bitmapHeight);
	    glyphInformation.push_back(glyph.second.bitmapLeft);
	    glyphInformation.push_back(glyph.second.bitmapTop);
	    glyphInformation.push_back(glyph.second.textureX);
	    
	    for(int i = 0; i<7; i++)
	    {
		glyphBytes[i][0] =  glyphInformation[i] >>24;
		glyphBytes[i][1] =  glyphInformation[i] >>16;
		glyphBytes[i][2] =  glyphInformation[i] >>8;
		glyphBytes[i][3] =  glyphInformation[i];

		fontData += (char) glyphBytes[i][0];
		fontData += (char) glyphBytes[i][1];
		fontData += (char) glyphBytes[i][2];
		fontData += (char) glyphBytes[i][3];

// 		file.write((char*) &glyphBytes[i], 4);
	    }

	}

	
	 std::cout<<"Done."<<std::endl;
	
    } 
    
   return fontData;
}

bool kte::ResourcePackage::read()
{
    std::ifstream file(packageName, std::ios::in | std::ios::binary );
    if(file.good())
    {
	unsigned char id[256];
	
	
	//first byte number of fonts
	file.read((char*)id, 1);
	uint32_t numberOfFonts = (uint32_t)id[0];
	
	for(unsigned i = 0; i<numberOfFonts; ++i)
	{
	    Font font;
	    
	    //length of the font name
	    file.read((char*)id, 1);
	    uint32_t fontNameLength = (uint32_t)id[0];
	    
	    //read font name
	    file.read((char*)id, fontNameLength);
	    std::string fontname((char*)id, fontNameLength);
	    font.name = fontname;
	    
	    //1 byte fontsize 
	    file.read((char*)id, 1);
	    uint32_t fontSize = (uint32_t) id[0];
	    font.fontSize = fontSize;
	    
	    //2 byte fonttexture height 
	    file.read((char*)id, 2);
	    uint32_t textureHeight = (uint32_t) id[0] << 8 | ((uint32_t) id[1]);
	    font.textureHeight = textureHeight;
	    
	    //2 byte fonttexture width 
	    file.read((char*)id, 2);
	    uint32_t textureWidth = ((uint32_t) id[0]) << 8  | ((uint8_t)id[1]); 
	    font.textureWidth = textureWidth;
	    
	    
	    
	    //4 byte fonttexture data count 
	    file.read((char*)id, 4);
	    uint32_t textureDataCount = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    
	    
	    std::vector<char> textureData(textureDataCount);
	    file.read((char*) &textureData[0], textureDataCount);
	    
	    font.data = textureData;
	    
	    
	    //2 byte for the number of glyphes 
	    file.read((char*)id, 2);
	    uint32_t glyphCount = ((uint32_t)id[0]<<8) | ((uint32_t)id[1]); 
	    


	    for(int i = 0; i<glyphCount; ++i)
	    {
		char glyphCharacter;
		//read 1 byte glyph character 
		file.read((char*) &glyphCharacter, 1);
		
		std::vector<unsigned int> glyphInformation(7);
		
		//7 * 4 bytes for the glyph informations 
		for(int j = 0; j<7; ++j)
		{
 		    file.read((char*) id, 4);

		    uint32_t glyphValue = ((uint32_t) id[0] << 24)  
				 | ((uint32_t)id[1] << 16) 
				 | ((uint32_t)id[2]<<8) 
				 | ((uint32_t)id[3]);
				 
		    glyphInformation[j] = glyphValue;	
		}
		
		font.glyphs[glyphCharacter].advanceX = glyphInformation[0];
		font.glyphs[glyphCharacter].advanceY = glyphInformation[1];
		font.glyphs[glyphCharacter].bitmapWidth = glyphInformation[2];
		font.glyphs[glyphCharacter].bitmapHeight = glyphInformation[3];
		font.glyphs[glyphCharacter].bitmapLeft = glyphInformation[4];
		font.glyphs[glyphCharacter].bitmapTop = glyphInformation[5];
		font.glyphs[glyphCharacter].textureX= glyphInformation[6];
		 
	
	    }
	    fonts.push_back(font);
	}
    
	//read textures 
	//first byte number of textures
	file.read((char*)id, 1);
	uint32_t numberOfTextures = (uint32_t)id[0];
	
	for(unsigned i = 0; i<numberOfTextures; ++i)
	{
	    TextureData textureData;
	    
	    //length of the texture name
	    file.read((char*)id, 1);
	    uint32_t textureNameLength = (uint32_t)id[0];
	    
	    //read texture name
	    file.read((char*)id, textureNameLength);
	    std::string textureName((char*)id, textureNameLength);
	    textureData.name = textureName;
	    
	    //1 byte hasAlpha 
	    file.read((char*)id, 1);
	    if(id[0] == 'F')
		textureData.hasAlpha = false;
	    else 
		textureData.hasAlpha  =true;
	    
	    //2 byte texture height 
	    file.read((char*)id, 2);
	    uint32_t textureHeight = (uint32_t) id[0] << 8 | ((uint32_t) id[1]);
	    textureData.height = textureHeight;
	    
	    //2 byte texture width 
	    file.read((char*)id, 2);
	    uint32_t textureWidth = ((uint32_t) id[0]) << 8  | ((uint8_t)id[1]); 
	    textureData.width = textureWidth;
	    
	    
	    
	    //4 byte texture data count 
	    file.read((char*)id, 4);
	    uint32_t textureDataCount = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    
	    
	    std::vector<char> data(textureDataCount);
	    file.read((char*) &data[0], textureDataCount);
	    
	    textureData.data = data;
	    textures.push_back(textureData);
	}
	
	//read audios 
	//first byte number of audios
	file.read((char*)id, 1);
	uint32_t numberOfAudios = (uint32_t)id[0];
	
	for(unsigned i = 0; i<numberOfAudios; ++i)
	{
	    AudioData audioData;
	    
	    //length of the audio name
	    file.read((char*)id, 1);
	    uint32_t audioNameLength = (uint32_t)id[0];
	    
	    //read audio name
	    file.read((char*)id, audioNameLength );
	    std::string textureName((char*)id, audioNameLength );
	    audioData.name = textureName;
	    
	    //1 byte channels 
	    file.read((char*)id, 1);
	    uint32_t channels  = (uint32_t)id[0];
	    audioData.numberOfChannels = channels;    
	    
	     //4 byte sampleRate
	    file.read((char*)id, 4);
	    uint32_t sampleRate = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    audioData.sampleRate = sampleRate;
	    
	    //4 byte framecount
	    file.read((char*)id, 4);
	    uint32_t numberOfFrames = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    audioData.numberOfFrames = numberOfFrames;
	    
	    //4 byte audio data count 
	    file.read((char*)id, 4);
	    uint32_t audioDataCount = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    
	    
	    std::vector<char> dataBytes(audioDataCount*2);
	    std::vector<short> data(audioDataCount);
	    file.read((char*) &dataBytes[0], audioDataCount*2);
	    
	    for(int i =0 ; i<audioDataCount; i++)
	    {
		  
		data[i] = ((int32_t) dataBytes[2*i+0] << 8) |
		          ((int32_t) dataBytes[2*i+1] & 0x00FF);
	    }
	    
	    audioData.data = data;
	    audios.push_back(audioData);
	}
	
	
    //read files 
	//first byte number of files
	file.read((char*)id, 1);
	uint32_t numberOfFiles = (uint32_t)id[0];
	
	for(int i = 0; i<numberOfFiles; i++)
	{
	    File fileData;
	    
	    //length of the texture name
	    file.read((char*)id, 1);
	    uint32_t fileNameLength = (uint32_t)id[0];
	    
	    //read texture name
	    file.read((char*)id, fileNameLength);
	    std::string fileName((char*)id, fileNameLength);
	    fileData.name = fileName;
	    
	    //4 byte texture data count 
	    file.read((char*)id, 4);
	    uint32_t fileDataCount = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    
	       
	    std::vector<char> data(fileDataCount);
	    file.read((char*) &data[0], fileDataCount);
	    
	    fileData.content = "";
	    for(int i = 0; i<fileDataCount; i++)
		fileData.content += data[i];
	    
	    
	    files.push_back(fileData);
	}
	
    }
    else 
    {
	std::cout<<"Package "<<packageName<<" not found!"<<std::endl;
	return false;
    }
    file.close();
    
    return true;
}

