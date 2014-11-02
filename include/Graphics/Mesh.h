#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>


/****************
* Contains information about a specific mesh..
* This is based on OpenGL and uses the vbo, ibo, vao
****************/
namespace kte
{
    class Mesh
    {
    public:
        /*********
        * Binds the VAO to render the Mesh
        *********/

        virtual ~Mesh(){}
        virtual void bindVAO() = 0;

        unsigned int getNumberOfIndices() { return numberOfIndices; }
        virtual GLuint getMVP() { return mvp; }

        virtual GLuint getCOLOR() { return color; }
    protected:
        unsigned int numberOfIndices;
        static GLuint mvp;
        static GLuint color;
    };
}
#endif