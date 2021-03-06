#include "OnPCH.h"
#include "Render.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "OnEngine\Drawing\Primitive.h"
#include "OnEngine\Drawing\Triangle.h"
#include "OnEngine\\Drawing\Quad.h"

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

        /*OpenGL Options*/
        /*If GL_BLEND is enabled; check the rendering order of your objects*/
        glEnable(GL_BLEND);

        /*If GL_DEPTH_TEST is enabled; then check the planes to your frustum against your model view projection matrix along with the camera's position & view direction.*/
        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);

        /*If you have GL_CULL_FACE enabled check the winding order of your model's vertices. (LH) vs (RH).*/
        glEnable(GL_CULL_FACE);

        glCullFace(GL_BACK);         ///<<<--Back of the triangle obj
        glFrontFace(GL_CCW);         ///<<<--Counter Clock Wide

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
    }

    void Render::InitPrimitiveVAO(Primitive * primitive)
    {
    }

    void Render::InitVAO(Primitive * primitive)
    {
       

        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

       

        // Generate 1 buffer, put the resulting identifier in vertexbuffer
        glGenBuffers(1, &m_VBO);

        // The following commands will talk about our 'vertexbuffer' buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, primitive->GetNumOfVertices() * sizeof Vertex, primitive->GetVertices(), GL_STATIC_DRAW);

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            (GLint)primitive->GetNumOfVertices() * sizeof Vertex,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)primitive->GetNumOfVertices() * sizeof Vertex); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
    }

    void Render::CompileShaders()
    {
        //SHADER INIT
        //core_program.Init("Assets/Shaders/VertexShaderColored.vert", "Assets/Shaders/FragmentShaderColored.frag");
        // Create and compile our GLSL program from the shaders
        //m_ProgramID = m_Shader.Load("Assets/Shaders/VertexShader.vert", "Assets/Shaders/FragmentShader.frag");
        //m_ProgramID = m_Shader.Load("Assets/Shaders/Vertex.vert", "Assets/Shaders/Fragment.frag");
        //m_ProgramID = m_Shader.Load("Assets/Shaders/VertexShaderColored.vert", "Assets/Shaders/FragmentShaderColored.frag");

        // Get a handle for our "MVP" uniform
        m_MatrixID = glGetUniformLocation(m_ProgramID, "MVP");

        // Get a handle for our "MVP" uniform
        //m_MatrixID = glGetUniformLocation(m_ProgramID, "MVP");
    }

    void Render::SetCamera()
    {
        // Enable depth test
        glEnable(GL_DEPTH_TEST);

        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        glm::mat4 Projection = glm::perspective(
                                                glm::radians(45.0f),   // 45� Field of View
                                                4.0f / 3.0f,           // 4:3 ratio
                                                0.1f,                  // display range from 0.1 unit to
                                                100.0f);               // 100 units
        
        // Or, for an ortho camera :
        //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

        // Camera matrix
        glm::mat4 View;
                  View = glm::lookAt(
                                      glm::vec3(4, 3, 3),          // Camera is at (4,3,3), in World Space (0, 4, 2)
                                      glm::vec3(0, 0, 0),          // and looks at the origin (0.0.0) 3D Center of the screen
                                      glm::vec3(0, 1, 0)           // Head is up (set to 0,-1,0 to look upside-down)
                                      );


        
                 /* View = glm::lookAt(glm::vec3(0, 4, 2),
                                     glm::vec3(0, 0, 0),
                                     glm::vec3(0, 1, 0));*/

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

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        
        Triangles();
      
    }

    void Render::CleanUp()
    {
        // Cleanup VBO
        glDeleteBuffers(1, &m_VAO);
        glDeleteBuffers(1, &m_CBO);
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteProgram(m_ProgramID);
    }

    int Render::GetVerticesCount(int width, int height)
    {
        return m_Width * m_Height * 3;
    }

    int Render::GetIndicesCount(int sWidth, int sHeight)
    {
        return (m_Width * m_Height) + (m_Width - 1) * (m_Height - 2);
    }

    float * Render::GetVertices(int sWidth, int sHeight)
    {
        if (m_Vertices) return m_Vertices;

        m_Vertices = new float[GetVerticesCount(m_Width, m_Height)];
        int i = 0;

        for (int row = 0; row < m_Height; row++) {
            for (int col = 0; col < m_Width; col++) {
                m_Vertices[i++] = (float)col;
                m_Vertices[i++] = 0.0f;
                m_Vertices[i++] = (float)row;
            }
        }

       return m_Vertices;
    }

    int * Render::GetIndices(int sWidth, int sHeight)
    {
        if (m_Indices) return m_Indices;

        m_Indices = new int[m_Size];
        int i = 0;

        for (int row = 0; row < m_Height - 1; row++) {
            if ((row & 1) == 0) { // even rows
                for (int col = 0; col < m_Width; col++) {
                    m_Indices[i++] = col + row * m_Width;
                    m_Indices[i++] = col + (row + 1) * m_Width;
                }
            }
            else { // odd rows
                for (int col = m_Width - 1; col > 0; col--) {
                    m_Indices[i++] = col + (row + 1) * m_Width;
                    m_Indices[i++] = col - 1 + +row * m_Width;
                }
            }
        }
        if ((m_Height & 1) && m_Height > 2) {
            m_Indices[i++] = (m_Height - 1) * m_Width;
        }

        return m_Indices;
    }

    void Render::Test()
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

    void Render::Test2()
    {
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(0.2f, 0.2f, 0.0f);
        glVertex3f(0.8f, 0.2f, 0.0f);
        glVertex3f(0.2f, 0.5f, 0.0f);
        glVertex3f(0.8f, 0.5f, 0.0f);
        glVertex3f(0.2f, 0.8f, 0.0f);
        glVertex3f(0.8f, 0.8f, 0.0f);
        glEnd();
    }

    void Render::DQuad()
    {
        Quad quad;
        std::cout << quad.GetVertices() << std::endl;
        std::cout << quad.GetNumOfVertices() << std::endl;
        std::cout << quad.GetIndices() << std::endl;
        std::cout << quad.GetNumOfIndices() << std::endl;
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

    void Render::TriangleOne()
    {
        //VertexPosition verticesPos[] =
        //{
        //    /* Position */                       /* Color */                         /* Texcoords */               /* Normals */
        //    glm::vec3(0.0f,  0.5f, 0.0f),     glm::vec3(1.0f, 0.5f, 0.0f),      //glm::vec2(0.5f, 1.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
        //    glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 1.0f, 0.0f),      //glm::vec2(0.0f, 0.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
        //    glm::vec3(0.0f, -0.5f, 0.0f),     glm::vec3(0.0f, 0.5f, 1.0f),      //glm::vec2(1.0f, 0.0f)      //glm::vec3( 0.0f, 0.0f, 1.0f)
        //};



        Vertex3A vertices[] =
        {
            /* Position */                       /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3(  0.0f,  0.5f, 0.0f ),     glm::vec3( 1.0f, 0.5f, 0.0f ),      glm::vec2( 0.5f, 1.0f ),      //glm::vec3( 0.0f, 0.0f, 1.0f),
            glm::vec3( -0.5f, -0.5f, 0.0f ),     glm::vec3( 0.0f, 1.0f, 0.0f ),      glm::vec2( 0.0f, 0.0f ),      //glm::vec3( 0.0f, 0.0f, 1.0f),
            glm::vec3(  0.0f, -0.5f, 0.0f ),     glm::vec3( 0.0f, 0.5f, 1.0f ),      glm::vec2( 1.0f, 0.0f )      //glm::vec3( 0.0f, 0.0f, 1.0f)
        };

        unsigned numbOfVertices = sizeof(vertices) / sizeof(Vertex3A);

        GLuint indices[] =
        {
            0, 1, 2
        };

        unsigned numbOfIndices = sizeof(indices) / sizeof(GLuint);

        //Meshes Objs 3ds, max, c4d, maya, blend, fbx
        /*MODEL*/




        //Load a vertex buffer into OpenGL for later rendering.
        //Vertex Array Obj, Vertex Buffer Obj, Element Buffer Obj
        /*VAO VBO EBO*/ 
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        //Create vertex array object names, Bind a vertex array object
        /*CREATE  VAO AND BIND*/
        glCreateVertexArrays(1, &VAO);            //http://docs.gl/gl4/glCreateVertexArrays.
        glBindVertexArray(VAO);                   //http://docs.gl/gl4/glBindVertexArray



        //Generate buffer object names
        /*GENERATE  BVO, BIND AND SEND DATA*/
        glGenBuffers(1, &VBO);                                                           //http://docs.gl/gl4/glGenBuffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);                                              //http://docs.gl/gl4/glBindBuffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);       //http://docs.gl/gl4/glBufferData



        //Generate element buffer object names
        /*GENERATE  EVO, BIND AND SEND DATA*/
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



        //
        
        /*SET VERTEX ATTRIB POINTERS AND ENABLE*/
        //GLuint v_AtrribLocation = glGetAttribLocation(m_ProgramID, "v_Position");
        
        //glVertexAttribPointer();                                      //http://docs.gl/gl4/glVertexAttribPointer
        /*POSITION*/
        glVertexAttribPointer( 0 ,                                      /*Index where is start*/ 
                               3 ,                                      /*Size of the vertex components*/
                               GL_FLOAT,                                /*What type of obj*/
                               GL_FALSE,                                /*Normalized Yes or No*/
                               sizeof(Vertex3A),                          /*How many bytes betwen each vertex attrib*/
                               (GLvoid*)offsetof(Vertex3A, v_Position));  /*Specifies a offset of the first component*/
        
                //glEnableVertexAttribArray(v_AtrribLocation);
        glEnableVertexAttribArray(0);

        /*COLOR*/
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3A), (GLvoid*)offsetof(Vertex3A, v_Color));
        glEnableVertexAttribArray(1);

        /*TEXT COORD*/
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3A), (GLvoid*)offsetof(Vertex3A, v_TexCoord));
        glEnableVertexAttribArray(2);

        /*BIND VAO 0*/
        glBindVertexArray(0);

        /*USE SHADER PROGRAM*/
        glUseProgram(m_ProgramID);

        /*BIND the already created obj VAO*/
        glBindVertexArray(m_VAO);

        /*DRAW THE OBJ*/
        glDrawArrays(GL_TRIANGLES, 0, numbOfVertices);

        //glDrawElements(GL_TRIANGLES, numbOfIndices, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
    }

    void Render::TriangleTwo()
    {
        //MODEL
        Vertex vertices[] =
        {
            /* Position */                       /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3(0.0f,  0.5f, 0.0f),     glm::vec3(1.0f, 0.5f, 0.0f),      glm::vec2(0.5f, 1.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),      glm::vec2(0.0f, 0.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
            glm::vec3(0.0f, -0.5f, 0.0f),     glm::vec3(0.0f, 0.5f, 1.0f),      glm::vec2(1.0f, 0.0f)      //glm::vec3( 0.0f, 0.0f, 1.0f)
        };

        unsigned numbOfVertices = sizeof(vertices) / sizeof(Vertex3A);

        GLuint indices[] =
        {
            0, 1, 2
        };

        numbOfIndices = sizeof(indices) / sizeof(GLuint);


    //VAO, VBO, EBO
    //GEN VAO AND BIND
        //GLuint VAO;
        //glCreateVertexArrays(1, &VAO);
        //glBindVertexArray(VAO);
  
        ////GEN VBO AND BIND AND SEND DATA
        //GLuint VBO;
        //glGenBuffers(1, &VBO);
        //glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        ////GEN EBO AND BIND AND SEND DATA
        //GLuint EBO;
        //glGenBuffers(1, &EBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ////SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
        ////Position
        //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        //glEnableVertexAttribArray(0);
        ////Color
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Color));
        //glEnableVertexAttribArray(1);
        ////Texcoord
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_TexCoord));
        //glEnableVertexAttribArray(2);
        ////Normal
        ///*glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
        //glEnableVertexAttribArray(3);*/

        ////BIND VAO 0
        //glBindVertexArray(0);
    }

    void Render::PrimitiveTriangles()
    {
        //Triangle primitive;

        //glGenVertexArrays(1, &m_VAO);
        //glBindVertexArray(m_VAO);



        //// Generate 1 buffer, put the resulting identifier in vertexbuffer
        //glGenBuffers(1, &m_VBO);

        //// The following commands will talk about our 'vertexbuffer' buffer
        //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        //// Give our vertices to OpenGL.
        //glBufferData(GL_ARRAY_BUFFER, primitive.GetNumOfVertices() * sizeof Vertex, primitive.GetVertices(), GL_STATIC_DRAW);

        //// 1st attribute buffer : vertices
        //glEnableVertexAttribArray(0);

        //glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        //glVertexAttribPointer(
        //    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        //    primitive.GetNumOfVertices() * sizeof Vertex,                  // size
        //    GL_FLOAT,           // type
        //    GL_FALSE,           // normalized?
        //    0,                  // stride
        //    (void*)0            // array buffer offset
        //);

        // Draw the triangle !
        //glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        //glDisableVertexAttribArray(0);
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
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // Our vertices. Three consecutive floats give a 3D vertex. 
        //Three consecutive vertices give a triangle.
        // A cube has 6 faces with 2 triangles each, so this makes 6 * 2 = 12 triangles, and 12 * 3 vertices

        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f,    // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,    // triangle 1 : end

             1.0f, 1.0f,-1.0f,     // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,    // triangle 2 : end

             1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
             1.0f,-1.0f,-1.0f,

             1.0f, 1.0f,-1.0f,
             1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,

             1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
             1.0f,-1.0f, 1.0f,

             1.0f, 1.0f, 1.0f,
             1.0f,-1.0f,-1.0f,
             1.0f, 1.0f,-1.0f,

             1.0f,-1.0f,-1.0f,
             1.0f, 1.0f, 1.0f,
             1.0f,-1.0f, 1.0f,

             1.0f, 1.0f, 1.0f,
             1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,

             1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,

             1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
             1.0f,-1.0f, 1.0f
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
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 * 3 indices starting at 0 -> 12 triangles -> 6 squares
        glDisableVertexAttribArray(0);
    }

    void Render::CubeColor()
    {
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        // Our vertices. Three consecutive floats give a 3D vertex. 
        //Three consecutive vertices give a triangle.
        // A cube has 6 faces with 2 triangles each, so this makes 6 * 2 = 12 triangles, and 12 * 3 vertices

        static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f,    // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,    // triangle 1 : end

             1.0f, 1.0f,-1.0f,     // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,    // triangle 2 : end

             1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
             1.0f,-1.0f,-1.0f,

             1.0f, 1.0f,-1.0f,
             1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,

             1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,

            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
             1.0f,-1.0f, 1.0f,

             1.0f, 1.0f, 1.0f,
             1.0f,-1.0f,-1.0f,
             1.0f, 1.0f,-1.0f,

             1.0f,-1.0f,-1.0f,
             1.0f, 1.0f, 1.0f,
             1.0f,-1.0f, 1.0f,

             1.0f, 1.0f, 1.0f,
             1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,

             1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,

             1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
             1.0f,-1.0f, 1.0f
        };

        // One color for each vertex. They were generated randomly.
        static const GLfloat g_color_buffer_data[] = {
            0.583f,  0.771f,  0.014f,
            0.609f,  0.115f,  0.436f,
            0.327f,  0.483f,  0.844f,
            0.822f,  0.569f,  0.201f,
            0.435f,  0.602f,  0.223f,
            0.310f,  0.747f,  0.185f,
            0.597f,  0.770f,  0.761f,
            0.559f,  0.436f,  0.730f,
            0.359f,  0.583f,  0.152f,
            0.483f,  0.596f,  0.789f,
            0.559f,  0.861f,  0.639f,
            0.195f,  0.548f,  0.859f,
            0.014f,  0.184f,  0.576f,
            0.771f,  0.328f,  0.970f,
            0.406f,  0.615f,  0.116f,
            0.676f,  0.977f,  0.133f,
            0.971f,  0.572f,  0.833f,
            0.140f,  0.616f,  0.489f,
            0.997f,  0.513f,  0.064f,
            0.945f,  0.719f,  0.592f,
            0.543f,  0.021f,  0.978f,
            0.279f,  0.317f,  0.505f,
            0.167f,  0.620f,  0.077f,
            0.347f,  0.857f,  0.137f,
            0.055f,  0.953f,  0.042f,
            0.714f,  0.505f,  0.345f,
            0.783f,  0.290f,  0.734f,
            0.722f,  0.645f,  0.174f,
            0.302f,  0.455f,  0.848f,
            0.225f,  0.587f,  0.040f,
            0.517f,  0.713f,  0.338f,
            0.053f,  0.959f,  0.120f,
            0.393f,  0.621f,  0.362f,
            0.673f,  0.211f,  0.457f,
            0.820f,  0.883f,  0.371f,
            0.982f,  0.099f,  0.879f
        };

        // Generate 1 buffer, put the resulting identifier in VBO
        glGenBuffers(1, &m_VBO);

        // The following commands will talk about our 'VBO' buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


        /*---->>>> Color Definition <<<<----*/

        // Generate 1 buffer, put the resulting identifier in CBO
        glGenBuffers(1, &m_CBO);

        // The following commands will talk about our 'CBO' buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_CBO);

        // Give our vertices to OpenGL.
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


        // 1st attribute VBO buffer : vertices
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


        // 2nd attribute CBO buffer : colors
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, m_CBO);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12 * 3 indices starting at 0 -> 12 triangles -> 6 squares

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }

    void Render::CubeFloat()
    {
    }

    void Render::Terrain()
    {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, GetVertices(m_Width, m_Height));
            glDrawElements(GL_TRIANGLE_STRIP, GetIndicesCount(m_Width, m_Height), GL_UNSIGNED_INT, GetIndices(m_Width, m_Height));
            glDisableClientState(GL_VERTEX_ARRAY);
       
    }

}