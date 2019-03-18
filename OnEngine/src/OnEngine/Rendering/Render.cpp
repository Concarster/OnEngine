#include "OnPCH.h"
#include "Render.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

    }

    void Render::CompileShaders()
    {
        // Create and compile our GLSL program from the shaders
        m_ProgramID = m_Shader.Load("Assets/Shaders/VertexShader_GLM.vert", "Assets/Shaders/FragmentShader_GLM.frag");

        // Get a handle for our "MVP" uniform
        m_MatrixID = glGetUniformLocation(m_ProgramID, "MVP");
    }

    void Render::SetCamera()
    {
        // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(
                                                glm::radians(45.0f),   // 45° Field of View
                                                4.0f / 3.0f,           // 4:3 ratio
                                                0.1f,                  // display range from 0.1 unit to
                                                100.0f);               // 100 units
        
        // Or, for an ortho camera :
        //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

        // Camera matrix
        glm::mat4 View = glm::lookAt(
                                      glm::vec3(4, 3, 3),          // Camera is at (4,3,3), in World Space
                                      glm::vec3(0, 0, 0),          // and looks at the origin
                                      glm::vec3(0, 1, 0)           // Head is up (set to 0,-1,0 to look upside-down)
                                      );

        // Model matrix : an identity matrix (model will be at the origin)
        glm::mat4 Model = glm::mat4(1.0f);

        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

        // Use our shader
        glUseProgram(m_ProgramID);
        //glUseProgram(m_Obj.GetProgramId());

        // Send our transformation to the currently bound shader, 
        // in the "MVP" uniform
        glUniformMatrix4fv(m_MatrixID, 1, GL_FALSE, &MVP[0][0]);

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