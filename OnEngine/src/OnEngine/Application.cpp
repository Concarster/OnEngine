#include "OnPCH.h"
#include "Application.h"

#include <glad\glad.h>

#include "OnEngine\IImput.h"
#include "OnEngine\Rendering\GLRender.h"

namespace on
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ON_ENGINE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        /*Cause is an explicit Constructor*/
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
    }


    Application::~Application()
    {
    }

    void Application::Run()
    {
        GLRender render;

        GLuint m_SProgram;
        unsigned int VAO, VBO, EBO;
        
        render.LoadShaders(m_SProgram);
        
        m_Render.Init();
        m_Render.CompileShaders();
        m_Render.SetCamera();
       
        render.RenderATriangle(m_SProgram, VAO, VBO, EBO);

        while (m_Running)
        {
            m_Render.Draw();

            //render.RenderATriangle(m_SProgram, VAO, VBO, EBO);
            //render.RenderGlmTriangle(m_SProgram, VAO, VBO, EBO);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            /*MY VERSION*/

            // draw our first triangle
            glUseProgram(m_SProgram);
            
            glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            
            glDrawArrays(GL_TRIANGLES, 0, render.GetNumbOfIndices());
            //glDrawElements(GL_TRIANGLES, render.GetNumbOfIndices(), GL_UNSIGNED_INT, 0);
            // glBindVertexArray(0); // no need to unbind it every time 


            /*MY VERSION END*/

            /*auto[x, y] = IImput::GetMousePosition();
            ON_ENGINE_TRACE("X :{0}, Y: {1}", x, y);*/
            
            m_Window->OnUpdate();
            
        }

        render.GlRenderCleanUp(m_SProgram, VAO, VBO, EBO);
        m_Render.CleanUp();
    }

    void Application::OnEvent(Event & event)
    {
        EventDispatcher distpacher(event);
        distpacher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

        ON_ENGINE_TRACE("{0}", event);

        for (auto iterate = m_LayerStack.end(); iterate != m_LayerStack.begin(); )
        {
            (*--iterate)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    void Application::PushLayer(Layer * layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
        
    }

    void Application::PushOverlay(Layer * overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    bool Application::OnWindowClosed(WindowCloseEvent & event)
    {
        m_Running = false;
        return true;
    }


}