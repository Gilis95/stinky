#include <Tracy.hpp>
#include <core/Time.h>

#include "application/application.h"
#include "core/project.h"
#include "event/application_event.h"
#include "event/event.h"
#include "stinkypch.h"
#include "window/window.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
application::application(time_frame &&minTimestep)
    : m_IsRunning(false), m_EventController(),
      m_MinTimestep(std::forward<time_frame>(minTimestep)) {}

/////////////////////////////////////////////////////////////////////////////////////////
application::~application() = default;

/////////////////////////////////////////////////////////////////////////////////////////
void application::register_event_handlers() {
  m_EventController.register_event_handler<window_close_event>(
      [this](const event &event) { close(); });

  m_EventController.register_event_handler<app_update_event>(
      [window = get_window()](const event &event) { window->OnUpdate(event); });
}

/////////////////////////////////////////////////////////////////////////////////////////
void application::init() {
  Log::Init();
  get_window()->Init();

  std::string applicationRevision("Revision: 1234");
  std::string applicationName("Application Name: stinky");

  TracyAppInfo(applicationName.c_str(), applicationName.size())
      TracyAppInfo(applicationRevision.c_str(), applicationRevision.size())
}

/////////////////////////////////////////////////////////////////////////////////////////
void application::close() { m_IsRunning = false; }

/////////////////////////////////////////////////////////////////////////////////////////
void application::run() {
  m_IsRunning = true;
  app_update_event updateEvent;

  time_frame begin;
  time_frame timestep;
  time_frame leftFrameTime;
  while (m_IsRunning) {
    begin.AssignCurrentTime();

    std::for_each(m_LayerStack.begin(), m_LayerStack.end(),
                  [&](layer *layer) -> void {
                    layer->on_update(std::max(m_MinTimestep, timestep));
                  });

    m_EventController.on_event(updateEvent);
    {
      ZoneScopedN("LimitFrameRate")

          bool first = true;

      do {
        // Capture the end of frame
        timestep.AssignCurrentTime();
        // Subtract frame start from it. This will be the time, that frame has
        // taken until now.
        timestep -= begin;
        ContinueUnless(first)
            // Subtract timestep from min timestep. If this value is greater
            // than 0, we should wait this amount of time before next frame.
            leftFrameTime = m_MinTimestep;
        leftFrameTime -= timestep;
        first = false;
      } while (stinky::this_thread::sleep(leftFrameTime, leftFrameTime));
    }
    FrameMark
  }

  cleanup();
}

/////////////////////////////////////////////////////////////////////////////////////////
void application::push_lLayer(layer *layer) { m_LayerStack.push_layer(layer); }

/////////////////////////////////////////////////////////////////////////////////////////
void application::push_overlay(layer *layer) {
  m_LayerStack.push_overlay(layer);
}

/////////////////////////////////////////////////////////////////////////////////////////
void application::cleanup() { project_manager::destroy(); }
} // namespace stinky
