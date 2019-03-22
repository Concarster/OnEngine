#include "OnPCH.h"
#include "MainCtrl.h"

namespace on
{

    MainCtrl::MainCtrl()
    {
    }


    MainCtrl::~MainCtrl()
    {
    }

    void MainCtrl::Init()
    {
        m_Render.Init();
        m_Render.CompileShaders();
        m_Render.SetCamera();

        m_ImageMgr.GenTexture("Assets/Textures/Penguin.gif", m_TextureID);

        m_GLRrender.LoadShaders(m_SProgram); 
    }

    void MainCtrl::Setup()
    {
        m_GLRrender.RenderASquareWithOutDuplicate(m_SProgram, VAO, VBO, EBO);
        //render.RenderATriangle(m_SProgram, VAO, VBO, EBO);
        //render.RenderASquare(m_SProgram, VAO, VBO, EBO);
    }

    void MainCtrl::Run()
    {
        Init();
        Setup();
    }

    void MainCtrl::Draw()
    {
        m_Render.Draw();
    }

    void MainCtrl::Use()
    {
        // draw our first triangle
        glUseProgram(m_SProgram);
    }

    void MainCtrl::Activate()
    {
        /*Draw Activate Texture*/
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }

    void MainCtrl::Update()
    {
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

            //glDrawArrays(GL_TRIANGLES, 0, render.GetNumbOfVertices());
        glDrawElements(GL_TRIANGLES, m_GLRrender.GetNumbOfIndices(), GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
    }

    void MainCtrl::Clean()
    {
        m_GLRrender.GlRenderCleanUp(m_SProgram, VAO, VBO, EBO);
        m_Render.CleanUp();
    }

    void MainCtrl::Terminate()
    {
    }

}