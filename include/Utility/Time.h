#ifndef KTE_TIME_H
#define KTE_TIME_H

#include <chrono>
#include <iostream>

using namespace std::chrono;

namespace kte
{
    namespace Time 
    {
	unsigned int getTimeInMs();
    }
}
#endif