#ifndef KTE_QUAD_H
#define KTE_QUAD_H

#include <Graphics/Mesh.h>
#include <Graphics/ShaderManager.h>
/****************
* Contains information about generating
* a Quad. It uses the x and y axis for it's area.
****************/
namespace kte
{
    class Quad : public Mesh
    {
    public:
        /************
        * vao, vbo and ibo are initialized once for all following Quads.
        *************/
        Quad();
        virtual void bindVAO();

        GLuint getMVP() { return mvp; }
        GLuint getCOLOR() { return color; }
    private:
        static bool s_initialzed;  // are the class attributes already initialized?
        static GLuint s_vao;     //vertex array object
        static GLuint s_vbo;     //vertex buffer object
        static GLuint s_ibo;     //index buffer object

    };
}
#endif