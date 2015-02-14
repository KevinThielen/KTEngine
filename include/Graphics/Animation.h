#ifndef KTE_ANIMATION_H
#define KTE_ANIMATION_H

#include <map>
#include <string>
#include <glm/glm.hpp>
namespace kte
{
    struct Animation
    {
        std::string name;
        std::string spriteSheet;
        std::map<unsigned int, glm::vec4> frames;
        bool repeat = true;
    };
}

#endif