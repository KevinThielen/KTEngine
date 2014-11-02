#include <Graphics/ShaderManager.h>
#include <iostream>


namespace kte
{
    ShaderManager* ShaderManager::shaderManager = NULL;

    ShaderManager::ShaderManager()
    {
        initAttributeLocations();
    }

    ShaderManager::~ShaderManager()
    {
        for (auto iterator = shaderPrograms.begin(); iterator != shaderPrograms.end(); iterator++)
        {
            glDeleteProgram(iterator->second);
        }
    }

    ShaderManager* ShaderManager::getInstance()
    {

        if (shaderManager == NULL)
            shaderManager = new ShaderManager();
        return shaderManager;
    }


    void ShaderManager::initAttributeLocations()
    {
        vertexAttributeLocations["vertex"] = 1;
        vertexAttributeLocations["uv"] = 2;
        vertexAttributeLocations["color"] = 3;
        vertexAttributeLocations["MVP"] = 4;

    }
    bool ShaderManager::shaderProgramFromFile(std::string programName, std::string vertexShader, std::string fragmentShader, std::string geometryShader)
    {
        std::string vertexFilePath = vertexShader;
        std::string fragmentFilePath = fragmentShader;
        std::string geometryFilePath = geometryShader;

        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        //GLuint geometryShaderId;
       // if(geometryShader != "")
       //     geometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);


        if(!compileShader(vertexShaderId, loadShaderFromFile(vertexFilePath)))
            return false;
        else if(!compileShader(fragmentShaderId, loadShaderFromFile(fragmentFilePath)))
            return false;
        else
        {
            // Link the program
            GLint result = GL_FALSE;
            int infolength;

            GLuint programID = glCreateProgram();
            glAttachShader(programID, vertexShaderId);
            glAttachShader(programID, fragmentShaderId);


            for(auto iterator = vertexAttributeLocations.begin(); iterator!=vertexAttributeLocations.end(); iterator++)
            {
                glBindAttribLocation(programID, iterator->second, iterator->first.c_str());
            }

            glLinkProgram(programID);

            // Check the program
            glGetProgramiv(programID, GL_LINK_STATUS, &result);
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infolength);
            if (infolength > 0){
                std::vector<char> ProgramErrorMessage(infolength + 1);
                glGetProgramInfoLog(programID, infolength, NULL, &ProgramErrorMessage[0]);
                std::cout << &ProgramErrorMessage[0]  << std::endl;;
            }

            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);

            shaderPrograms[programName] = programID;
            return true;
        }
    }

    std::string ShaderManager::loadShaderFromFile(std::string shaderPath)
    {
        // Read the Vertex Shader code from the file
        std::string shaderCode;

        std::ifstream shaderStream(shaderPath, std::ios::in);
        if (shaderStream.is_open()){
            std::string Line = "";
            while (getline(shaderStream, Line))
                shaderCode += "\n" + Line;
            shaderStream.close();
        }
        else{
            std::cout << "Failed to open " << shaderPath << "\n" << std::endl;
            return "";
        }
        return shaderCode;
    }


    bool  ShaderManager::compileShader(GLuint shaderId, std::string shaderCode)
    {
        char const * shaderSourcePointer = shaderCode.c_str();
        GLint result = GL_FALSE;
        int infolength;

        glShaderSource(shaderId, 1, &shaderSourcePointer, NULL);
        glCompileShader(shaderId);


        // Check Vertex Shader
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infolength);
        if (infolength > 0){
            std::vector<char> shaderErrorMessage(infolength + 1);
            glGetShaderInfoLog(shaderId, infolength, NULL, &shaderErrorMessage[0]);
            std::cout << &shaderErrorMessage[0] << std::endl;

        }

        return true;
    }


}