#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "window/glfw/WindowsWindow.h"
#include "Logger.h"


namespace stinky {

    static void GLFWErrorCallback(int error, const char* description)
    {
        ERROR("GLFW Error ({0}): {1}", error, description);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& properties) {

    }

    void WindowsWindow::init(const WindowProperties& properties) {

        m_Data.height = properties.m_Height;
        m_Data.width = properties.m_Width;
        m_Data.titile = properties.m_Title;

        ASSERT(glfwInit(), "Maikata si eba eii!");
        glfwSetErrorCallback(GLFWErrorCallback);

        m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.titile.c_str(), NULL, NULL);

        // create context for current window
        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(5);

        ASSERT(gladLoadGL(), "Maikata si eba eii!");


        glfwSetWindowUserPointer(m_Window, &m_Data);


        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.closeCallback();
            }
        );
    }

    void WindowsWindow::setCloseCallback(const std::function<void()>& callback) {
        m_Data.closeCallback = callback;
    }

    void WindowsWindow::onUpdate()
    {

        // swap front and back buffer
        glfwSwapBuffers(m_Window);

        //poll for process events
        glfwPollEvents();
    }

    void shutdown()
    {
        glfwTerminate();
    }
}