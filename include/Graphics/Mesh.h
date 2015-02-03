#ifndef KTE_MESH_H
#define KTE_MESH_H

#include <GL/glew.h>

namespace kte
{
    class Mesh
    {
    public:
        virtual ~Mesh(){}
        virtual void bindVAO() { glBindVertexArray(vao); }
        virtual bool init() { }
        virtual GLuint getMVP() { return mvp; }
        virtual GLuint getCOLOR() { return color; }
        virtual unsigned int getNumberOfIndices() { return numberOfIndices; }
    protected:
        unsigned int numberOfIndices;
        static GLuint mvp;
        static GLuint color;

        GLuint vao;     //vertex array object
        GLuint vbo;     //vertex buffer object
        GLuint ibo;     //index buffer object
    };
}

#endif