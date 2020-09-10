#include "WindowWindow.h"
#include <glfw3.h>

namespace App
{
    App::Window *App::Window::s_Instance = nullptr;
    static uint8_t s_GLFWWindowCount = 0;

    WindowWindow::WindowWindow(const WindowProps &props)
    {
        Init(props);
    }

    WindowWindow::~WindowWindow() { Shutdown(); }

    Window *Window::Create(const WindowProps &props) { return new WindowWindow(props); }

    void WindowWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void WindowWindow::SetVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_Data.VSync = enabled;
    }

    bool WindowWindow::IsVSync() const { return m_Data.VSync; }

    void WindowWindow::Init(const WindowProps &props)
    {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if (s_GLFWWindowCount == 0)
        {
            int success = glfwInit();
            printf("%d Cannot init", success);
            s_GLFWWindowCount++;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

        if (!m_Window)
        {
            glfwTerminate();
            return;
        }
        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        //set glfw callback
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);

            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mod) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressEvent event(key);
                data.EventCallback(event);
                break;
            }
            default:
                break;
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int codepoint) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(codepoint);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mod) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            default:
                break;
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xoffset, double yoffset) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseScrollEvent event((float)xoffset, (float)yoffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xpos, double ypos) {
            WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xpos, (float)ypos);
            data.EventCallback(event);
        });

        glfwSetErrorCallback([](int errorCode, const char *desc) {
            printf("Error code: %d, %s", errorCode, desc);
        });

        Window::s_Instance = this;
    }

    void WindowWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }
} // namespace App