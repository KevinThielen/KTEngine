
#include "Graphics/Geometries.h"

kte::Quad kte::Geometry::quad;

bool kte::Geometries::initialze()
{
    static bool initalized = false;
    bool result = false;

    if(!initalized)
    {
	result = Geometry::quad.init();
	initalized = true;
    }

    return result;
}