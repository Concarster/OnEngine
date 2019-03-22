#pragma once
#include "OnEngine\Util\Defs.h"
#include "IImput.h"
#include "OnEngine\Rendering\GLRender.h"
#include "OnEngine\ImageMgr.h"
#include "OnEngine\Rendering\Render.h"

namespace on
{

    class ON_API MainCtrl
    {
    private:
        GLRender m_GLRrender;
        ImageMgr m_ImageMgr;
        Render m_Render;

    protected:
        GLuint m_SProgram;
        GLuint m_TextureID;
        unsigned int VAO, VBO, EBO;

    public:
        MainCtrl();
        ~MainCtrl();

        void Init();

        void Setup();

        void Run();

        void Draw();

        void Use();

        void Activate();

        void Update();

        void Clean();

        void Terminate();

    private:


    protected:

        
    };

}