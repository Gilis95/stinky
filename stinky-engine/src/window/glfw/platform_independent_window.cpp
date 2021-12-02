#include <GLFW/glfw3.h>
#include <Tracy.hpp>
#include <event/mouse_event.h>
#include <event/platform/glfw/glfw_window_event.h>
#include <glad/glad.h>

#include "event/event_controller.h"
#include "event/key_event.h"
#include "event/windows_event.h"
#include "window/glfw/platform_independent_window.h"

#include "stinkypch.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
static void GLFWErrorCallback(int error, const char *description) {
  STINKY_ERROR("GLFW Error ({0}): {1}", error, description);
}

/////////////////////////////////////////////////////////////////////////////////////////
platform_independent_window::platform_independent_window(
    const WindowProperties &properties, event_controller &eventController)
    : window(eventController), m_Data(eventController, properties.m_Title,
                                      properties.m_Width, properties.m_Height) {
}

/////////////////////////////////////////////////////////////////////////////////////////
platform_independent_window::~platform_independent_window() {
  platform_independent_window::Shutdown();
};

/////////////////////////////////////////////////////////////////////////////////////////
void platform_independent_window::Init() {
  int status = glfwInit();

  AssertReturnUnless(status);
  glfwSetErrorCallback(GLFWErrorCallback);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(),
                              NULL, NULL);

  // create context for current window
  glfwMakeContextCurrent(m_Window);

  // VSync
  glfwSwapInterval(0);

  AssertReturnUnless(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

  glfwSetWindowUserPointer(m_Window, &m_Data);

  glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    data.eventController.on_event(window_close_event());
  });

  glfwSetWindowSizeCallback(
      m_Window, [](GLFWwindow *window, int width, int height) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        data.height = height;
        data.width = width;

        window_resize_event event(width, height);
        data.eventController.on_event(event);
      });

  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scanCode,
                                  int action, int mods) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    switch (action) {
    case GLFW_PRESS: {
      key_pressed_event event(static_cast<key_code>(key));
      data.eventController.on_event(event);
      break;
    }
    case GLFW_RELEASE: {
      key_released_event event(static_cast<key_code>(key));
      data.eventController.on_event(event);
      break;
    }
    case GLFW_REPEAT: {
      key_pressed_event event(static_cast<key_code>(key));
      data.eventController.on_event(event);
      break;
    }
    }
  });

  glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keyCode) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    key_typed_event event(static_cast<key_code>(keyCode));
    data.eventController.on_event(event);
  });

  glfwSetScrollCallback(
      m_Window, [](GLFWwindow *window, double xOffset, double yOffset) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

        data.eventController.on_event(
            mouse_scrolled_event((float)xOffset, (float)yOffset));
      });

  glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos,
                                        double yPos) {
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    data.eventController.on_event(mouse_moved_event((float)xPos, (float)yPos));
  });

  glfwSetMouseButtonCallback(
      m_Window, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
        switch (action) {
        case GLFW_PRESS: {
          data.eventController.on_event(
              mouse_button_pressed_event(static_cast<mouse_code>(button)));
          break;
        }
        case GLFW_RELEASE: {
          data.eventController.on_event(
              mouse_button_released_event(static_cast<mouse_code>(button)));
          break;
        }
        }
      });

  _M_event_controller.on_event(glfw_window_post_init_event(m_Window));
}

/////////////////////////////////////////////////////////////////////////////////////////
void platform_independent_window::OnUpdate(const event &onUpdateEvent) {
  ZoneScopedN("GLFWUpdate")
      // poll for process events
      glfwPollEvents();

  // swap front and back buffer
  glfwSwapBuffers(m_Window);
}

/////////////////////////////////////////////////////////////////////////////////////////
void platform_independent_window::Shutdown() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

} // namespace stinky
