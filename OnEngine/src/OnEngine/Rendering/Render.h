#pragma once
#include "OnEngine\Defs.h"
#include "OnEngine\Objs\Objects.h"

namespace on
{

    class ON_API Render : public Objects
    {
    private:
        /*Getting The Objts*/
        Objects m_Obj;

        ///*The LoadShaders Obj*/
        //LoadShaders m_Shader;

        ///*This will identify our GLSL Program Shaders*/
        //GLuint m_ProgramID;

        ///*This will identify our Vertex Array Object*/
        //GLuint m_VAO;

        ///*This will identify our Vertex Buffer Object*/
        //GLuint m_VBO;

        ///*This will identify our Element Buffer Object*/
        //GLuint m_EBO;

    public:
        Render();
        ~Render();

        void Init();

        void Setup();

        void Draw();

        void CleanUp();

    private:
        void Triangles();

        void TwoTriangles();

        void ThreeTriangles();

        void FourTriangles();

        void FiveTriangles();

        void BlackAndWhiteTriangles();

        void Rectangles();

        void Cube();

        void CubeFloat();
    };

}