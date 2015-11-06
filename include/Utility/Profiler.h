#ifndef KTE_PROFILER_H
#define KTE_PROFILER_H

#include <map>
#include <vector>
#include "Utility/Time.h"
#include <iostream>
#include <fstream>

namespace kte  
{
    class Profiler 
    {
    public:
	static Profiler* instance() 
	{
	    static Profiler profiler;
	    return &profiler;
	}
	
	void setMaxSampleSize(int n) { maxSampleSize = n; }
	
	
	
	static void track(std::string sectionName)
	{
	    instance()->instanceTrack(sectionName);
	}
	
	static void stop(std::string sectionName)
	{
	    instance()->instanceStop(sectionName);
	}
	
	static std::map<std::string, std::vector<unsigned int>> getResults() { return instance()->sectionResults; } 
	

	void saveAs(std::string fileName)
	{
	    std::string buffer = "";
	    for(auto sectionResult : sectionResults)
	    {
		buffer += "\n";
		buffer += sectionResult.first + ": \n";
		for(auto results : sectionResult.second)
		{
		    buffer += "    "+ std::to_string(results/1000.0f)+"s\n";
		}
	    }
	    
	    std::fstream file(fileName, std::ios::out);
	    file << buffer;
	    file.close();
	}
    private:
	Profiler(){ maxSampleSize = 100; };
	
	void instanceTrack(std::string sectionName)
	{
	    if(sectionResults[sectionName].size() < maxSampleSize)
	    {
		trackedSections[sectionName] = Time::getTimeInMs();
	    }
	}
	
	void instanceStop(std::string sectionName)
	{
	     if( trackedSections[sectionName] != 0 && sectionResults[sectionName].size() < maxSampleSize)
	     {
		 sectionResults[sectionName].push_back(Time::getTimeInMs() - trackedSections[sectionName]);
	     }
	     trackedSections[sectionName] = 0;
	}
	
	
	std::map<std::string, unsigned int> trackedSections;
	std::map<std::string, std::vector<unsigned int>> sectionResults;
	
	int maxSampleSize;
    };
}

#endif