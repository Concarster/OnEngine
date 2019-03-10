#include "OnPCH.h"
#include "WinWindow.h"



namespace on
{
    static bool s_GLFWInitialized = false;

    /*static void GLFWErrorCallBack(int error, const char* description)
    {
        ON_ENGINE_ERROR("GLFW Error ({0}): {1}", error, description);
    }*/

    Window* Window::Create(const WindowProps & props)
    {
        return new WinWindow(props);
    }

    WinWindow::WinWindow(const WindowProps & props)
    {
        Init(props);
    }

    WinWindow::~WinWindow()
    {
    }

    void WinWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WinWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_Data.VSync = enabled;
    }

    bool WinWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

    void WinWindow::Init(const WindowProps & props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        ON_ENGINE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            
            ON_ENGINE_ASSERT(success, "Could not intialize GLFW!");
            
            //glfwSetErrorCallback(GLFWErrorCallBack);
            
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        
        glfwMakeContextCurrent(m_Window);
        
        /*int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        HZ_ENGINE_ASSERT(status, "Failed to initialize Glad!");*/
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        
        SetVSync(true);
    }

    void WinWindow::ShutDown()
    {
        glfwDestroyWindow(m_Window);
    }

}