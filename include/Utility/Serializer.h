#ifndef KTE_SERIALIZER_H
#define KTE_SERIALIZER_H

#include <json/json.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace kte 
{
    class Serializer 
    {
    public:
	Serializer()
	{
	}
	
	template <typename T> bool write(std::string node, T value)
	{
	    root[node] = value;
	    
	    return true;   
	}
	
	Json::Value& operator [](std::string node) { return root[node]; }
	
	Json::Value& getRoot() { return root; }
	
	bool readFromString(std::string data)
	{
	    //fill read with value
	    Json::Reader reader;
	    bool result = reader.parse(data, root);
	    
	    if(!result)
	    {
		  std::cout<<"Failed to read from string "<<reader.getFormattedErrorMessages()<<std::endl;
	    }
	    	    
	    return result;
	}
	
	bool read(std::string path)
	{
	    //fill read with value
	    std::ifstream file(path);
	    file.open(path);
	    
	    if(!file.is_open())
	    {
		std::cout<<"Coudln't open file "<<path<<std::endl;
		return false;
	    }
	    std::string buffer;
	    
	    std::ostringstream stream;
	    stream << file.rdbuf();
	    buffer = stream.str();
	    
	    file.close();
	    
	    Json::Reader reader;
	    bool result = reader.parse(buffer, root);
	    
	    if(!result)
	    {
		  std::cout  << "Failed to parse "<<path<<reader.getFormattedErrorMessages()<<std::endl;
	    }
	    	    
	    return result;
	}
	
	bool persist(std::string path) 
	{
	    Json::StyledWriter styledWriter;
	    std::ofstream file;
	    file.open(path);
	    
	    file<<styledWriter.write(root);
	    std::cout<<"PErsist: "<<styledWriter.write(root)<<std::endl;
	    file.close();
	    
	    return true;
	}	
	
    private:
	Json::Value root;
    };
    
}

#endif