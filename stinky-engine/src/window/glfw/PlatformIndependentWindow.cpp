#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <event/MouseEvent.h>
#include <event/platform/glfw/GLFWWindowEvent.h>

#include "event/WindowsEvent.h"
#include "event/EventController.h"
#include "event/KeyEvent.h"
#include "window/glfw/PlatformIndependentWindow.h"

#include "stinkypch.h"


namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    static void GLFWErrorCallback(int error, const char *description) {
        STINKY_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    PlatformIndependentWindow::PlatformIndependentWindow(const WindowProperties &properties,
                                                         EventController &eventController)
            : Window(eventController),
              m_Data(eventController, properties.m_Title, properties.m_Height, properties.m_Width) {
        PlatformIndependentWindow::Init();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    PlatformIndependentWindow::~PlatformIndependentWindow() {
        PlatformIndependentWindow::Shutdown();
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::Init() {
        Window::Init();
        m_EventController.RegisterEvent(EventType::GLFWWindowPostInitEvent);

        int status = glfwInit();

        AssertReturnUnless(status);
        glfwSetErrorCallback(GLFWErrorCallback);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), NULL, NULL);

        // create context for current window
        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(5);

        AssertReturnUnless(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

        glfwSetWindowUserPointer(m_Window, &m_Data);

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
                                       WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                                       data.eventController.OnEvent(WindowCloseEvent());
                                   }
        );

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.height = height;
            data.width = width;

            WindowResizeEvent event(width, height);
            data.eventController.OnEvent(event);
        });

        glfwSetKeyCallback(m_Window,
                           [](GLFWwindow *window, int key, int scanCode, int action, int mods) {
                               WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
                               switch (action) {
                                   case GLFW_PRESS: {
                                       KeyPressedEvent event(static_cast<KeyCode>(key));
                                       data.eventController.OnEvent(event);
                                       break;
                                   }
                                   case GLFW_RELEASE: {
                                       KeyReleasedEvent event(static_cast<KeyCode>(key));
                                       data.eventController.OnEvent(event);
                                       break;
                                   }
                                   case GLFW_REPEAT: {
                                       KeyPressedEvent event(static_cast<KeyCode>(key));
                                       data.eventController.OnEvent(event);
                                       break;
                                   }
                               }
                           });

        glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keyCode) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

            KeyTypedEvent event(static_cast<KeyCode>(keyCode));
            data.eventController.OnEvent(event);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

            data.eventController.OnEvent(MouseScrolledEvent((float) xOffset, (float) yOffset));
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

            data.eventController.OnEvent(MouseMovedEvent((float) xPos, (float) yPos));
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    data.eventController.OnEvent(MouseButtonPressedEvent(static_cast<MouseCode>(button)));
                    break;
                }
                case GLFW_RELEASE: {
                    data.eventController.OnEvent(MouseButtonReleasedEvent(static_cast<MouseCode>(button)));
                    break;
                }
            }
        });

        m_EventController.OnEvent(GLFWWindowPostInitEvent(m_Window));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::OnUpdate(const Event &onUpdateEvent) {

        // swap front and back buffer
        glfwSwapBuffers(m_Window);

        //poll for process events
        glfwPollEvents();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void PlatformIndependentWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

}
