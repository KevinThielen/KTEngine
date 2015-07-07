#ifndef KTE_MATH_H
#define KTE_MATH_H

namespace kte
{
    glm::vec3 ColorToFloat(float r, float g, float b)
    {
	glm::vec4 rgb;
	rgb.x = r / 256.0f;
	rgb.y = g / 256.0f;
	rgb.z = b / 256.0f;
	
	return rgb;
    }
}

#endif