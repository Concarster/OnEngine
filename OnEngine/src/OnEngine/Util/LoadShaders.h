#pragma once
#include <glad\glad.h>

#include "OnEngine\Defs.h"


namespace on
{

    class ON_API LoadShaders
    {
    public:
        LoadShaders();
        ~LoadShaders();

        GLuint Load(const char * vertex_file_path, const char * fragment_file_path);
    };

}