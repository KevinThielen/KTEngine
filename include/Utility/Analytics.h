#ifndef KTE_ANALYSTICS_H
#define KTE_ANALYSTICS_H

#include <string.h>
#include <stdio.h>
#include "Serializer.h"

namespace kte
{
    class Analytics
    {
    public:
	Analytics(std::string host, unsigned int port);

	static void enable(bool enabled) { Analytics::enabled = enabled; }
	
	Json::Value& operator [](std::string name) 
	{ 
	    return data[name]; 
	}
	
	bool sendData();
	
	std::string dataToString();
	
	void resetData()
	{
	    std::string ID = data["ID"].asString(); 
	    data = Serializer();
	    data["ID"] = ID;
	}
    private:
	unsigned int userID;
	static bool enabled;
	kte::Serializer data;

	const std::string HOST;
	const unsigned int PORT;
    };
}


#endif