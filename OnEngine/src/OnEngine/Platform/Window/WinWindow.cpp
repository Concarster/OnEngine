#include "OnPCH.h"
#include "WinWindow.h"

#include "OnEngine\Events\ApplicationEvent.h"
#include "OnEngine\Events\Event.h"
#include "OnEngine\Events\KeyEvent.h"
#include "OnEngine\Events\MouseEvent.h"

namespace on
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallBack(int error, const char* description)
    {
        ON_ENGINE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

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
            
            glfwSetErrorCallback(GLFWErrorCallBack);
            
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
        
        glfwMakeContextCurrent(m_Window);
        
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ON_ENGINE_ASSERT(status, "Failed to initialize Glad!");
        
        glfwSetWindowUserPointer(m_Window, &m_Data);
        
        SetVSync(true);

        /*GLFW CallBacks*/
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallBack(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallBack(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallBack(event);
                    break;
                }
                            
                
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallBack(event);
                    break;
                }
                
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallBack(event);
                    break;
                }

            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keyCode);

            data.EventCallBack(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            switch (action)
            {
                 case GLFW_PRESS:
                 {
                     MouseButtonPressedEvent event(button);
                     data.EventCallBack(event);
                     break;
                 }
                 
                 
                 case GLFW_RELEASE:
                 {
                     MouseButtonReleasedEvent event(button);
                     data.EventCallBack(event);
                     break;
                 }

            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallBack(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallBack(event);
        });
    }

    void WinWindow::ShutDown()
    {
        glfwDestroyWindow(m_Window);
    }

}