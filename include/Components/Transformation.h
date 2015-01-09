/***********************
* Contains a point, the scale and the rotation in the world space.
* It uses the glm Libary to represent each of those.
************************/

#ifndef KTE_TRANSFORMATION_H
#define KTE_TRANSFORMATION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "IComponent.h"

namespace kte
{
    class Transformation : public IComponent
    {
    public:
        /*********************
    * Default constructor, does nothing.
    *********************/
        Transformation() : IComponent(0)
        {
            position = glm::vec3(0,0,0);
            rotation = glm::vec3(0,0,0);
            scale = glm::vec3(1,1, 1);
            isDirty = true;
        }

        Transformation(int gameObjectId) : IComponent(gameObjectId)
        {
            position = glm::vec3(0,0,0);
            rotation = glm::vec3(0,0,0);
            scale = glm::vec3(1,1, 1);
            isDirty = true;

        }

        Transformation(unsigned int gameObjectId, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) : position(
                position), scale(scale), rotation(rotation), IComponent(gameObjectId)
        {
            isDirty = true;
        }

        bool contains2DPoint(float x, float y)
        {

            if(scale.x < 0.0f)
            {
                if (x < position.x + scale.x || x > position.x)
                    return false;
            }
            else
            {
                if (x < position.x || x > position.x + scale.x )
                    return false;
            }

            if(y < position.y || y > position.y+scale.y)
                return false;
            return true;
        }
        /**********************
        * GETTERS
        **********************/
        glm::vec3 getPosition()
        {
            return position;
        }

        glm::vec3 getScale()
        {
            return scale;
        }

        glm::vec3 getRotation()
        {
            return rotation;
        }

        glm::mat4 getMatrix()
        {
            if (isDirty)
            {
                matrix = glm::mat4();
                // transformation = translation x rotation x scale

                matrix = glm::translate(matrix, position + scale/2.0f);
                matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
                matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
                matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
                matrix = glm::translate(matrix, -scale/2.0f);


                matrix = glm::scale(matrix, scale);
                isDirty = false;
            }
            return matrix;
        }

        /**********************
        * SETTERS
        **********************/
        void setPosition(glm::vec3 position)
        {
            isDirty = true;
            this->position = position;
        }

        void setScale(glm::vec3 scale)
        {
            isDirty = true;
            this->scale = scale;
        }

        void setRotation(glm::vec3 rotation)
        {
            isDirty = true;
            this->rotation = rotation;
        }

        void move(glm::vec3 deltaPosition)
        {
            isDirty = true;
            this->position += deltaPosition;
        }

  private:

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
        glm::mat4 matrix;

        bool isDirty = true;
  };
}

#endif

