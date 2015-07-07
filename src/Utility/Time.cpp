#include "Utility/Time.h"

int kte::Time::getTimeInMs()
{
    milliseconds currentMs = duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch());
    return currentMs.count();
}