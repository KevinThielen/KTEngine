#ifndef FTE_SHADER_MANAGER
#define FTE_SHADER_MANAGER

#include <string>
#include <map>
#include <vector>
#include <fstream>

#include <GL/glew.h>
#include <iostream>

namespace kte
{
    //Singleton
    class ShaderManager
    {
    public:
        ~ShaderManager();

        static ShaderManager* instance()
        {
            static ShaderManager* instance = new ShaderManager();
            return instance;
        }

        void reset()
	{
	    for (auto iterator = shaderPrograms.begin(); iterator != shaderPrograms.end(); iterator++)
	    {
		glDeleteProgram(iterator->second);
	    }
    
	    shaderPrograms.clear();
	}
	
        void initAttributeLocations();
        bool shaderProgramFromFile(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader = "");

        GLuint getShaderProgram(std::string programName) {  return shaderPrograms[programName]; }
        GLuint getAttribLocation(std::string attribName) { return vertexAttributeLocations[attribName]; }

    private:
        ShaderManager();
        std::string loadShaderFromFile(std::string shader);
        bool compileShader(GLuint shaderId, std::string shaderCode);

        std::map<std::string, GLuint> shaderPrograms;
        std::map<std::string, GLuint> vertexAttributeLocations;
    };
}

#endif