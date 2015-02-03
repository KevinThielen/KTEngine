#ifndef KTE_QUAD_H
#define KTE_QUAD_H

#include <Graphics/Mesh.h>

/****************
* Contains information for rendering
* a Quad. It uses the x and y axis for it's draw area.
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
        bool init();

        GLuint getMVP() { return mvp; }
        GLuint getCOLOR() { return color;}
        GLuint getUV() { return uvVbo; }

    private:
        GLuint uvVbo;
    };
}
#endif

