#include "OnPCH.h"
#include "Render.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace on
{

    Render::Render()
    {
    }


    Render::~Render()
    {
    }

    void Render::Init()
    {
        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

        ///* Dark blue background */
        //glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        //
        ///* Ligth blue background */
        ////glClearColor(0.5F, 0.8F, 1.0F, 1.0F);

        //glClear(GL_COLOR_BUFFER_BIT);

    }

    void Render::Setup()
    {
        // Create and compile our GLSL program from the shaders
        m_ProgramID = m_Shader.Load("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
        /*GLuint m_ProgramID = m_Obj.GetProgramId();
        m_ProgramID = m_Obj.GetShader().Load("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");*/

        // Use our shader
        glUseProgram(m_ProgramID);
        //glUseProgram(m_Obj.GetProgramId());
    }

    void Render::Draw()
    {
        /* Dark blue background */
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

        /* Ligth blue background */
        //glClearColor(0.5F, 0.8F, 1.0F, 1.0F);

        glClear(GL_COLOR_BUFFER_BIT);

        Triangles();
    }

    void Render::CleanUp()
    {
        // Cleanup VBO
        glDeleteBuffers(1, &m_VAO);
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteProgram(m_ProgramID);
    }

    void Render::Triangles()
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // An array of 3 vectors which represents 3 vertices
        static const GLfloat g_vertex_buffer_data[] = {
           -0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
        };

        

        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &m_VBO);

        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
    }

    void Render::TwoTriangles()
    {
        
    }

    void Render::ThreeTriangles()
    {
    }

    void Render::FourTriangles()
    {
    }

    void Render::FiveTriangles()
    {
    }

    void Render::BlackAndWhiteTriangles()
    {
    }

    void Render::Rectangles()
    {
    }

    void Render::Cube()
    {
    }

    void Render::CubeFloat()
    {
    }

}