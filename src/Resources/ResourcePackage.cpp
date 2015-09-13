#include "Resources/ResourcePackage.h"

#include <iostream>

void kte::ResourcePackage::persist()
{
//    std::string header = "KTE";
    
    
    std::string fontData = persistFonts("bla");
    std::string textureData = persistTextures();
    
    std::fstream file(packageName, std::ios::binary | std::ios::out );
    
    file.write(fontData.c_str(), fontData.size());
    file.write(textureData.c_str(), textureData.size());
    
    file.close();
}


std::string kte::ResourcePackage::persistTextures()
{
    std::string textureData;

    
    //write the information into a file
 //   std::fstream file(filename, std::ios::binary | std::ios::out );
    
    int numberOfTextures = textures.size();
//     file.write((char*) &numberOfTextures, 1);
    textureData += (char)numberOfTextures;
    
    for(auto& texture : textures)
    {
	std::cout<<"\nPacking texture "<<texture.name<<".."<<std::endl;
	
	//1 byte name Length
	uint8_t nameLength = texture.name.size();
// 	file.write((char*) &nameLength, 1);
	textureData += (char)nameLength;
	
	
	
	const char* textureName = texture.name.c_str();
	//file.write(textureName,  texture.name.size());
	textureData += texture.name;
	
	char hasAlpha = 'F';
	//1 byte has alpha component
	if(texture.hasAlpha)
	    hasAlpha = 'T';
// 	file.write((char*) &hasAlpha, 1);
	textureData += hasAlpha;
	
	//2 byte texture width/height    
	uint32_t textureHeightRaw = texture.height;
	uint8_t textureHeight[2];
	textureHeight[0] = textureHeightRaw >> 8;
	textureHeight[1] = textureHeightRaw >> 0;
// 	file.write((char*) &textureHeight, 2);
        textureData += (char) textureHeight[0];
        textureData += (char) textureHeight[1];
	
	uint32_t textureWidthRaw = texture.width;
	uint8_t textureWidth[2];
	textureWidth[0] = textureWidthRaw >> 8;
	textureWidth[1] = textureWidthRaw >> 0;
// 	file.write((char*) &textureWidth, 2);
	textureData += (char) textureWidth[0];
        textureData += (char) textureWidth[1]; 
	
	
	//4 byte texture data length
	uint8_t dataLength[4];
	uint32_t dataLengthRaw = texture.data.size();
	dataLength[0] = dataLengthRaw >> 24;
	dataLength[1] = dataLengthRaw >> 16;
	dataLength[2] = dataLengthRaw >> 8;
	dataLength[3] = dataLengthRaw;
// 	file.write((char*) &dataLength, 4);
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

// 	file.write((char*) &data[0], dataLengthRaw);
	std::cout<<"Done."<<std::endl;
	
    }
    	
    return textureData;
}


std::string kte::ResourcePackage::persistFonts(const char* filename)
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
    
    }
    else 
    {
	std::cout<<"Package "<<packageName<<" not found!"<<std::endl;
	return false;
    }
    file.close();
    
    return true;
}

