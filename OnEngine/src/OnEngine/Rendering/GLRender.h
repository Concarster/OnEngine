#pragma once
#include "OnEngine\Util\Defs.h"
#include "OnEngine\Objs\Objects.h"

namespace on
{

    class ON_API GLRender
    {
    private:
        unsigned int m_NumbOfVertices;
        unsigned int m_NumbOfIndices;

    public:
        GLRender();
        ~GLRender();

        void GLRenderDraw(GLuint & program);

        bool LoadShaders(GLuint& program);

        void CreateProgram();
        void CreateProgram(GLuint& program);

        void ShaderInit(GLuint & core_program);
        void ShaderInit(GLuint core_program);

        void GlRenderCleanUp(GLuint & program, GLuint& vao, GLuint& vbo, GLuint& ebo);

        unsigned int GetNumbOfVertices() { return m_NumbOfVertices; }
        unsigned int GetNumbOfIndices() { return m_NumbOfIndices; }

        void RenderGlmTriangle(GLuint & program, GLuint& vao, GLuint& vbo, GLuint& ebo);
        void RenderATriangle(GLuint & program, unsigned int& VAO, unsigned int& VBO);
        void RenderATriangle(GLuint & program, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
        void RenderATriangleDNT(GLuint & program, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
    };

}