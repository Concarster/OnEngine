#include "OnPCH.h"
#include "LoadShaders.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include <string.h>

namespace on
{

    LoadShaders::LoadShaders()
    {
    }


    LoadShaders::~LoadShaders()
    {
    }

    GLuint LoadShaders::Load(const char * vertex_file_path, const char * fragment_file_path)
    {
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        
        if (VertexShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode = sstr.str();
            VertexShaderStream.close();
        }
        else 
        {
            ON_ENGINE_ERROR("Impossible to open {0}. Are you in the right directory ?", vertex_file_path);
            std::cin.get(); /*getchar();*/
            return 0;
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        
        if (FragmentShaderStream.is_open()) 
        {
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;


        // Compile Vertex Shader
        ON_ENGINE_TRACE("Compiling shader : {0}", vertex_file_path);

        char const * VertexSourcePointer = VertexShaderCode.c_str();

        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);

        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);

        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

        if (InfoLogLength > 1) 
        {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);

            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);

            ON_ENGINE_ERROR("{0}", &VertexShaderErrorMessage[0]);
        }



        // Compile Fragment Shader
        ON_ENGINE_TRACE("Compiling shader : {0}", fragment_file_path);

        char const * FragmentSourcePointer = FragmentShaderCode.c_str();

        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);

        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);

        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

        if (InfoLogLength > 1) 
        {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);

            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

            ON_ENGINE_ERROR("{0}", &FragmentShaderErrorMessage[0]);
        }



        // Link the program
        ON_ENGINE_TRACE("Linking Program!");

        GLuint ProgramID = glCreateProgram();

        glAttachShader(ProgramID, VertexShaderID);

        glAttachShader(ProgramID, FragmentShaderID);

        glLinkProgram(ProgramID);

        // Check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);

        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

        if (InfoLogLength > 1) 
        {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);

            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);

            ON_ENGINE_ERROR("{0}", &ProgramErrorMessage[0]);
        }


        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;

    }

}