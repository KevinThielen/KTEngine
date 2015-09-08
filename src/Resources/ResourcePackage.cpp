#include "Resources/ResourcePackage.h"

#include <iostream>

void kte::ResourcePackage::persist()
{
    std::string header = "KTE";
    
    std::string fontData = persistFonts();
}

std::string kte::ResourcePackage::persistFonts()
{
    std::cout<<"Persist fonts.."<<std::endl;
    std::string fontData;

    
    //write the information into a file
    std::fstream file("fonts.kte", std::ios::binary | std::ios::out );
    
    
    int numberOfFonts = fonts.size();
    file.write((char*) &numberOfFonts, 1);
    
    for(auto& font : fonts)
    {
	std::cout<<"\nPacking font "<<font.name<<std::endl;
	
	//1 byte name Length
	uint8_t nameLength = font.name.size();
	file.write((char*) &nameLength, 1);
	
	const char* fontName = font.name.c_str();
	file.write(fontName,  font.name.size());
	
	uint8_t fontSize = font.fontSize;
	file.write((char*) &fontSize, 1);

	//2 byte texture width/height    
	uint32_t textureHeightRaw = font.textureHeight;
	uint8_t textureHeight[2];
	textureHeight[0] = textureHeightRaw >> 8;
	textureHeight[1] = textureHeightRaw >> 0;
	file.write((char*) &textureHeight, 2);

	uint32_t textureWidthRaw = font.textureWidth;
	uint8_t textureWidth[2];
	textureWidth[0] = textureWidthRaw >> 8;
	textureWidth[1] = textureWidthRaw >> 0;
	file.write((char*) &textureWidth, 2);
	
	 
	//4 byte texture data length
	uint8_t dataLength[4];
	uint32_t dataLengthRaw = font.data.size();
	dataLength[0] = dataLengthRaw >> 24;
	dataLength[1] = dataLengthRaw >> 16;
	dataLength[2] = dataLengthRaw >> 8;
	dataLength[3] = dataLengthRaw;
	file.write((char*) &dataLength, 4);
	 
	 
	std::vector<unsigned char> data;
	data.resize(dataLengthRaw);

	//copy texture data byte by byte
	for(int i = 0; i<dataLengthRaw; i++)
	{
	    data[i] = font.data[i];
	}

	file.write((char*) &data[0], dataLengthRaw);
	
	
	
	//copy the glyph informations
	uint32_t glyphSizeRaw = font.glyphs.size();
	uint8_t glyphSize[2];
	glyphSize[0] = glyphSizeRaw >> 8;
	glyphSize[1] = glyphSizeRaw >> 0;
	
	std::cout<<"Number of Glyphs "<<glyphSizeRaw<<std::endl;
	file.write((char*) &glyphSize, 2);

		
	
		
	std::map<char, std::vector<uint8_t>> glyphs;
	for(auto& glyph : font.glyphs)
	{
	    uint8_t glyphBytes[7][4];
	    
	    
	    char glyphCharacter = glyph.first;
	    file.write((char*) &glyphCharacter, 1);
	    
	    
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

		file.write((char*) &glyphBytes[i], 4);
	    }

	}

	
	 std::cout<<"Done."<<std::endl;
	
    }
    file.close();

}

bool kte::ResourcePackage::read(const char* package)
{
    std::cout<<"Reading package "<<package<<".."<<std::endl;
    std::ifstream file(package, std::ios::in | std::ios::binary );
    if(file.good())
    {
	unsigned char id[256];
	
	std::cout<<"\nHeader: "<<std::endl;
	
	//first byte number of fonts
	file.read((char*)id, 1);
	uint32_t numberOfFonts = (uint32_t)id[0];
	std::cout<<numberOfFonts<<" fonts found"<<std::endl;
	
	for(unsigned i = 0; i<numberOfFonts; ++i)
	{
	    std::cout<<"\nReading font "<< i <<".."<<std::endl;
	    Font font;
	    
	    //length of the font name
	    file.read((char*)id, 1);
	    uint32_t fontNameLength = (uint32_t)id[0];
	    
	    //read font name
	    file.read((char*)id, fontNameLength);
	    std::string fontname((char*)id, fontNameLength);
	    std::cout<<"Name: "<<fontname<<std::endl;
	    font.name = fontname;
	    
	    //1 byte fontsize 
	    file.read((char*)id, 1);
	    uint32_t fontSize = (uint32_t) id[0];
	    std::cout<<"Size: "<<fontSize<<std::endl;
	    font.fontSize = fontSize;
	    
	    //2 byte fonttexture height 
	    file.read((char*)id, 2);
	    uint32_t textureHeight = (uint32_t) id[0] << 8 | ((uint32_t) id[1]);
	    std::cout<<"Textureheight: "<<textureHeight<<std::endl;
	    font.textureHeight = textureHeight;
	    
	    //2 byte fonttexture width 
	    file.read((char*)id, 2);
	    uint32_t textureWidth = ((uint32_t) id[0]) << 8  | ((uint8_t)id[1]); 
	    font.textureWidth = textureWidth;
	    
	    std::cout<<"Texturewidth: "<<textureWidth<<std::endl;
	    
	    
	    //4 byte fonttexture data count 
	    file.read((char*)id, 4);
	    uint32_t textureDataCount = ((uint32_t) id[0] << 24)  | ((uint32_t)id[1] << 16) | ((uint32_t)id[2]<<8) | ((uint32_t)id[3]); 
	    
	    std::cout<<"Datacount: "<<textureDataCount<<std::endl;
	    
	    std::vector<char> textureData(textureDataCount);
	    file.read((char*) &textureData[0], textureDataCount);
	    
	    font.data = textureData;
	    
	    
	    //2 byte for the number of glyphes 
	    file.read((char*)id, 2);
	    uint32_t glyphCount = ((uint32_t)id[0]<<8) | ((uint32_t)id[1]); 
	    std::cout<<glyphCount<< " glyphs found."<<std::endl;
	    


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
    
    }
    else 
    {
	std::cout<<"Package not found!"<<std::endl;
	return false;
    }
    file.close();
    
    return true;
}

