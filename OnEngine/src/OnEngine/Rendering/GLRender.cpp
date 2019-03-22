#include "OnPCH.h"
#include "GLRender.h"
#include "OnEngine\Drawing\Vertex.h"

namespace on
{

    GLRender::GLRender()
    {
    }


    GLRender::~GLRender()
    {
    }

    void GLRender::GLRenderDraw(GLuint & program)
    {
        LoadShaders(program);
    }

    bool GLRender::LoadShaders(GLuint & program)
    {
        bool loadSuccess = true;

        char infoLog[512];
        GLint success;

        std::string tmp = "";
        std::string src = "";

        std::ifstream in_file;

        /// * VERTEX * ///  
        //in_file.open("Assets/Shaders/VertexTriangleMod1.vert");
        //in_file.open("Assets/Shaders/Vertex.vert");
        in_file.open("Assets/Shaders/VertexGLSLTexture.vert");

        if (in_file.is_open())
        {
            while (std::getline(in_file, tmp))
            {
                src += tmp + "\n";
            }
               
        }
        else
        {
            std::cout << "ERROR::SHADER::COULD_NOT_OPEN_VERTEX_FILE: " << "\n";
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_OPEN_VERTEX_FILE: ");
            loadSuccess = false;
        }
            
        in_file.close();
    
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        
        const GLchar* vertSrc = src.c_str();

        glShaderSource(vertexShader, 1, &vertSrc, NULL);

        glCompileShader(vertexShader);

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_COMPILE_VERTEX_SHADER: ");
            std::cout << infoLog << "\n";
            loadSuccess = false;
        }

        tmp = "";
        src = "";
        /// * VERTEX END* ///

        ///* FRAGMENT *///
        //in_file.open("Assets/Shaders/FragmentTriangleMod1.frag");
        //in_file.open("Assets/Shaders/Fragment.frag");
        in_file.open("Assets/Shaders/FragmentGLSLTexture.frag");

        if (in_file.is_open())
        {
            while (std::getline(in_file, tmp))
            {
                src += tmp + "\n";
            }

        }
        else
        {
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_OPEN_FRAGMENT_FILE: ");
            loadSuccess = false;
        }

        in_file.close();

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar* fragSrc = src.c_str();

        glShaderSource(fragmentShader, 1, &fragSrc, NULL);

        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_COMPILE_FRAGMENT_SHADER: ");
            std::cout << infoLog << "\n";
            loadSuccess = false;
        }


        /* Program */
        program = glCreateProgram();

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(program, 512, NULL, infoLog);
            ON_ENGINE_ERROR("ERROR::SHADER::COULD_NOT_LINK_PROGRAM: ");
            std::cout << infoLog << "\n";
            loadSuccess = false;
        }

        /* End */
        glUseProgram(0);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return loadSuccess;
    }

    void GLRender::CreateProgram()
    {

    }

    void GLRender::CreateProgram(GLuint & program)
    {
    }

    void GLRender::ShaderInit(GLuint & core_program)
    {
        //GLuint core_program;
        if (!LoadShaders(core_program))
        {
            glfwTerminate();
        }
    }

    void GLRender::ShaderInit(GLuint core_program)
    {
        /*SHADER INIT*/

    }

    void GLRender::GlRenderCleanUp(GLuint & program, GLuint& vao, GLuint& vbo, GLuint& ebo)
    {
        glDeleteProgram(program);
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }


   

    void GLRender::RenderGlmTriangle(GLuint & program, GLuint& vao, GLuint& vbo, GLuint& ebo)
    {
        //MODEL
        Vertex vertices[] =
        {
            /* Position */                       /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3( 0.0f,  0.5f, 0.0f),     glm::vec3(1.0f, 0.5f, 0.0f),      glm::vec2(0.5f, 1.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f),     glm::vec3(0.0f, 1.0f, 0.0f),      glm::vec2(0.0f, 0.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
            glm::vec3( 0.0f, -0.5f, 0.0f),     glm::vec3(0.0f, 0.5f, 1.0f),      glm::vec2(1.0f, 0.0f)      //glm::vec3( 0.0f, 0.0f, 1.0f)
        };

        unsigned numbOfVertices = sizeof(vertices) / sizeof(Vertex3A);

        GLuint indices[] =
        {
            0, 1, 2
        };

        unsigned numbOfIndices = sizeof(indices) / sizeof(GLuint);

        //VAO, VBO, EBO
    //GEN VAO AND BIND
    
        glCreateVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //GEN VBO AND BIND AND SEND DATA
    
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //GEN EBO AND BIND AND SEND DATA
        
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        //SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
        //Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        glEnableVertexAttribArray(0);
        //Color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Color));
        glEnableVertexAttribArray(1);
        //Texcoord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_TexCoord));
        glEnableVertexAttribArray(2);
        //Normal
        /*glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(3);*/

        //BIND VAO 0
        glBindVertexArray(0);
    }

    void GLRender::RenderATriangle(GLuint & program, unsigned int& VAO, unsigned int& VBO)
    {
        /*MY VERSION*/
        // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left  
             0.5f, -0.5f, 0.0f, // right 
             0.0f,  0.5f, 0.0f  // top   
        };

        //unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);


        // uncomment this call to draw in wireframe polygons.
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        /*MY VERSION END*/
    }

    void GLRender::RenderATriangle(GLuint & program, unsigned int & VAO, unsigned int & VBO, unsigned int & EBO)
    {
        /*MY VERSION*/
        // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
        Vertex vertices[] = {

            /* Position */                    /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec3(1.0f, 0.0f, 0.0f),        glm::vec2(0.5f, 1.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //BOTTOM LEFT
            glm::vec3( 0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 1.0f, 0.0f),        glm::vec2(0.0f, 0.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //TOP CENTER
            glm::vec3( 0.0f,  0.5f, 0.0f),    glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(1.0f, 0.0f)         //glm::vec3( 0.0f, 0.0f, 1.0f)    //BOTTOM RIGTH

        };

        m_NumbOfVertices = sizeof(vertices) / sizeof(Vertex3A);

        GLuint indices[] =
        {
            0, 1, 2
        };

        m_NumbOfIndices = sizeof(indices) / sizeof(GLuint);

        /*Generate VAO and BIND*/
        glGenVertexArrays(1, &VAO);            //glCreateVertexArrays(1, &VAO);     // Create and Generatte DSA
        glBindVertexArray(VAO);

        /*Generate VBO and BIND*/
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        /*ARRAY Buffer DATA*/
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*Generate EBO and BIND*/
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        /*ELEMENT Buffer DATA*/
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        /*Getting the AttribLocation to or from the Shader*/
        GLuint attribLocation = glGetAttribLocation(program, "v_Position");
        //Then use Like glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        //glEnableVertexAttribArray(attribLocation);

        /*VERTEX AttribPointer and ENABLE*/
        /* POSITION */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        glEnableVertexAttribArray(0);

        /* COLOR */
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Color));
        glEnableVertexAttribArray(1);

        /* TEXT COORD */
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_TexCoord));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);


        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        /*MY VERSION END*/
    }

    void GLRender::RenderASquare(GLuint & program, unsigned int & VAO, unsigned int & VBO, unsigned int & EBO)
    {
        /*MY VERSION*/
        // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
        Vertex vertices[] = {

            /* Position */                    /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3(-0.5f,  0.5f, 0.0f),    glm::vec3(1.0f, 0.0f, 0.0f),        glm::vec2(0.5f, 1.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //BOTTOM LEFT
            glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 1.0f, 0.0f),        glm::vec2(0.0f, 0.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //TOP CENTER
            glm::vec3( 0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(1.0f, 0.0f),         //glm::vec3( 0.0f, 0.0f, 1.0f)    //BOTTOM RIGTH

            /*Second Triangle*/
            glm::vec3(-0.5f,  0.5f, 0.0f),    glm::vec3(1.0f, 0.0f, 0.0f),        glm::vec2(0.5f, 1.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //BOTTOM LEFT
            glm::vec3( 0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(0.0f, 0.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //TOP CENTER
            glm::vec3( 0.5f,  0.5f, 0.0f),    glm::vec3(1.0f, 1.0f, 0.0f),        glm::vec2(1.0f, 0.0f)         //glm::vec3( 0.0f, 0.0f, 1.0f)    //BOTTOM RIGTH


        };

        m_NumbOfVertices = sizeof(vertices) / sizeof(Vertex3A);

        GLuint indices[] =
        {
            0, 1, 2, //Triangle A
            3, 4, 5  //Triangle B
        };

        m_NumbOfIndices = sizeof(indices) / sizeof(GLuint);

        /*Generate VAO and BIND*/
        glGenVertexArrays(1, &VAO);            //glCreateVertexArrays(1, &VAO);     // Create and Generatte DSA
        glBindVertexArray(VAO);

        /*Generate VBO and BIND*/
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        /*ARRAY Buffer DATA*/
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*Generate EBO and BIND*/
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        /*ELEMENT Buffer DATA*/
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        /*Getting the AttribLocation to or from the Shader*/
        //GLuint attribLocation = glGetAttribLocation(program, "v_Position");
        //Then use Like glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        //glEnableVertexAttribArray(attribLocation);

        /*VERTEX AttribPointer and ENABLE*/
        /* POSITION */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        glEnableVertexAttribArray(0);

        /* COLOR */
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Color));
        glEnableVertexAttribArray(1);

        /* TEXT COORD */
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_TexCoord));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);


        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        /*MY VERSION END*/
    }

    void GLRender::RenderASquareWithOutDuplicate(GLuint & program, unsigned int & VAO, unsigned int & VBO, unsigned int & EBO)
    {
        Vertex vertices[] = {

            /* Position */                    /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3(-0.5f,  0.5f, 0.0f),    glm::vec3(1.0f, 0.0f, 0.0f),        glm::vec2(0.0f, 1.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //BOTTOM LEFT
            glm::vec3(-0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 1.0f, 0.0f),        glm::vec2(0.0f, 0.0f),        //glm::vec3( 0.0f, 0.0f, 1.0f),   //TOP CENTER
            glm::vec3( 0.5f, -0.5f, 0.0f),    glm::vec3(0.0f, 0.0f, 1.0f),        glm::vec2(1.0f, 0.0f),         //glm::vec3( 0.0f, 0.0f, 1.0f)    //BOTTOM RIGTH
            glm::vec3( 0.5f,  0.5f, 0.0f),    glm::vec3(1.0f, 1.0f, 0.0f),        glm::vec2(1.0f, 1.0f)         //glm::vec3( 0.0f, 0.0f, 1.0f)    //BOTTOM RIGTH
        };

        m_NumbOfVertices = sizeof(vertices) / sizeof(Vertex3A);

        GLuint indices[] =
        {
            0, 1, 2, //Triangle A
            0, 2, 3  //Triangle B
        };

        m_NumbOfIndices = sizeof(indices) / sizeof(GLuint);

        /*Generate VAO and BIND*/
        glGenVertexArrays(1, &VAO);            //glCreateVertexArrays(1, &VAO);     // Create and Generatte DSA
        glBindVertexArray(VAO);

        /*Generate VBO and BIND*/
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        /*ARRAY Buffer DATA*/
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*Generate EBO and BIND*/
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        /*ELEMENT Buffer DATA*/
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        /*Getting the AttribLocation to or from the Shader*/
        //GLuint attribLocation = glGetAttribLocation(program, "v_Position");
        //Then use Like glVertexAttribPointer(attribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        //glEnableVertexAttribArray(attribLocation);

        /*VERTEX AttribPointer and ENABLE*/
        /* POSITION */
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Position));
        glEnableVertexAttribArray(0);

        /* COLOR */
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_Color));
        glEnableVertexAttribArray(1);

        /* TEXT COORD */
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, v_TexCoord));
        glEnableVertexAttribArray(2);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);


        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void GLRender::RenderATriangleDNT(GLuint & program, unsigned int & VAO, unsigned int & VBO, unsigned int & EBO)
    {
        /*MY VERSION*/
        // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
        Vertex vertices[] = {

            /* Position */                    /* Color */                         /* Texcoords */               /* Normals */
            glm::vec3(-0.5f, -0.5f, 0.0f),    //glm::vec3(1.0f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),    //glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(0.0f,  0.5f, 0.0f),    //glm::vec3(0.0f, 0.5f, 1.0f)


        };

        ///* Position */                       /* Color */                         /* Texcoords */               /* Normals */
        //glm::vec3( 0.0f,  0.5f, 0.0f),       glm::vec3(1.0f, 0.5f, 0.0f), glm::vec2(0.5f, 1.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
        //glm::vec3(-0.5f, -0.5f, 0.0f),       glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f),      //glm::vec3( 0.0f, 0.0f, 1.0f),
        //glm::vec3( 0.0f, -0.5f, 0.0f),       glm::vec3(0.0f, 0.5f, 1.0f), glm::vec2(1.0f, 0.0f)      //glm::vec3( 0.0f, 0.0f, 1.0f)


        //unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);


        // uncomment this call to draw in wireframe polygons.
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        /*MY VERSION END*/
    }

}