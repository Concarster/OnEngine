#include "OnPCH.h"
#include "Shader.h"

namespace on
{

    //Shader::Shader()
    //{
    //}
    //
    //
    //Shader::~Shader()
    //{
    //}

    void Shader::Init(char * vertexFile, char * fragmentFile, char * geometryFile)
    {
        GLuint vertexShader = 0;
        GLuint geometryShader = 0;
        GLuint fragmentShader = 0;

        vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);

        if (geometryFile != "")
            geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);

        fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

        this->linkProgram(vertexShader, geometryShader, fragmentShader);

        //End
        glDeleteShader(vertexShader);
        glDeleteShader(geometryShader);
        glDeleteShader(fragmentShader);
    }

}