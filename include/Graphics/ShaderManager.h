#ifndef FTE_SHADER_MANAGER
#define FTE_SHADER_MANAGER

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <GL/glew.h>


namespace kte
{
    //Singleton
    class ShaderManager
    {
    public:
        ~ShaderManager();

        static ShaderManager* getInstance();

        void initAttributeLocations();
        bool shaderProgramFromFile(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader = "");

        GLuint getShaderProgram(std::string programName) { return shaderPrograms[programName]; }
      //  GLuint getUniformLocation(std::string programName, const char* uniform) { return glGetUniformLocation(shaderPrograms[programName], uniform); }
        GLuint getAttribLocation(std::string attribName) { return vertexAttributeLocations[attribName]; }

    private:
        ShaderManager();
        std::string loadShaderFromFile(std::string shader);
        bool compileShader(GLuint shaderId, std::string shaderCode);

        static ShaderManager* shaderManager;
        std::map<std::string, GLuint> shaderPrograms;
        std::map<std::string, GLuint> vertexAttributeLocations;
    };
}
#endif