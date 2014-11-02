#ifndef KTE_GAMEOBJECT_H
#define KTE_GAMEOBJECT_H



/***********************
* A single game object in the scene.
* The game object contains only a transformation.
* Additional components can be added.
************************/
#include <map>
#include <memory>
#include <typeinfo>
#include <typeindex>

#include "Components/Transformation.h"

class IComponent;
namespace kte
{
    class GameObject
    {
    public:
        GameObject() : transformation(Transformation(availableId))
        {
            ID = availableId;
            availableId++;

        }

        GameObject(glm::vec3 position, glm::vec3 scale = glm::vec3(1,1,1), glm::vec3 rotation = glm::vec3(0,0,0)) : transformation(Transformation(availableId))
        {
            ID=availableId;
            transformation.setPosition(position);
            transformation.setScale(scale);
            transformation.setRotation(rotation);
            availableId++;

        }

        GameObject(const GameObject &other) : ID(availableId)
        {
            ID = other.ID;
            transformation = other.transformation;
            components = other.components;
        }

        GameObject& operator= (const GameObject &other)
        {
            ID = other.ID;

            transformation = other.transformation;
            components = other.components;

            return *this;
        }

        ~GameObject()
        {

        }

        Transformation* getTransformation() { return &transformation; }

        template<typename T>
        T *addComponent()
        {
            std::shared_ptr<T> component(new T(ID));
            components[std::type_index(typeid(*component))] = component;
            return component.get();
        }

        template<typename T>
        T *getComponent()
        {
            std::type_index index(typeid(T));
            unsigned long count = components.count(std::type_index(typeid(T)));
            if (count != 0)
            {
                return dynamic_cast< T * >(components[index].get());
            }
            else
            {
                return NULL;
            }
        }

        int getId() { return ID; }

    private:
        int ID = 0;          //ID of this gameObject, needed for hashing and other performance optimaizations
        static int availableId; //contains the next available ID. After instancing a new gameObject, this will increase by one

        std::map<const std::type_index, std::shared_ptr<IComponent>> components;

        Transformation transformation;    //Transformation: positions, rotation and scale in world space
    };


}
#endif