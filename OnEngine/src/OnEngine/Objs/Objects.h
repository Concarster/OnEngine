#pragma once
#include "OnEngine\Defs.h"
#include "OnEngine\Util\LoadShaders.h"

class ON_API Objects
{
protected:
    /*The LoadShaders Obj*/
    on::LoadShaders m_Shader;

    /*This will identify our GLSL Program Shaders*/
    //GLuint m_ProgramID;
    unsigned int m_ProgramID;

    /*This will identify our Vertex Array Object*/
    //GLuint m_VAO;
    unsigned int m_VAO;

    /*This will identify our Vertex Buffer Object*/
    //GLuint m_VBO;
    unsigned int m_VBO;
    
    /*This will identify our Element Buffer Object*/
    //GLuint m_EBO;
    unsigned int m_EBO;

public:
    Objects();
    ~Objects();

    /*Getting the shader Program*/
    on::LoadShaders GetShader();

    /*Getting The Program ID*/
    GLuint GetProgramId();

    /*Get Vertex Array Object*/
    GLuint GetVAO();

    /*Get Vertex Buffer Object*/
    GLuint GetVBO();

    /*Get Element Buffer Object*/
    GLuint GetEBO();
};

