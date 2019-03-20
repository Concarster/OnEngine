#pragma once
#include "OnEngine/Util/Defs.h"
#include "OnEngine\Util\LoadShaders.h"

namespace on
{

    class ON_API Objects
    {
    private:
        //static Objects* s_InstObj;

    protected:
        /*The LoadShaders Obj*/
        LoadShaders m_Shader;

        /*This will identify our GLSL Program Shaders*/
        //GLuint m_ProgramID;
        unsigned int m_ProgramID;

        /*This will identify our Vertex Array Object*/
        //GLuint m_VAO;
        unsigned int m_VAO;

        /*This will identify our Vertex Buffer Object*/
        //GLuint m_VBO;
        unsigned int m_VBO;

        /*This will identify our Color Buffer Object*/
        //GLuint m_CBO;
        unsigned int m_CBO;

        /*This will identify our Element Buffer Object*/
        //GLuint m_EBO;
        unsigned int m_EBO;

        /*This will identify our MatrixID Object*/
        //GLuint MatrixID;
        unsigned int m_MatrixID;

        int m_Size = 100;
        int m_Width = 400;
        int m_Height = 400;
        float* m_Vertices = 0;
        int* m_Indices = 0;


    public:
        Objects();
        ~Objects();

        //inline static Objects& GetInstObj() { return *s_InstObj; }

        /*Getting the shader Program*/
        LoadShaders GetShader();

        /*Getting The Program ID*/
        //GLuint GetProgramId();
        unsigned int GetProgramId();

        /*Get Vertex Array Object*/
        //GLuint GetVAO();
        unsigned int GetVAO();

        /*Get Vertex Buffer Object*/
        //GLuint GetVBO();
        unsigned int GetVBO();

        /*Get Element Buffer Object*/
        //GLuint GetEBO();
        unsigned int GetEBO();
    };

}