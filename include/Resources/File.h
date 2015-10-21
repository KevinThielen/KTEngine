#ifndef KTE_FILE_H
#define KTE_FILE_H

#include "IResource.h"

namespace kte  
{
    struct File : public IResource
    {
	std::string content;
    };
}
#endif