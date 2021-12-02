#pragma once

#include "core/Time.h"
#include "event/event.h"
#include "event/event_controller.h"
#include "event/layer_stack.h"
#include <chrono>

#include "stinky_prerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class application {
public:
  /**
   * @param minTimestep - minimum allowed amount of time between frames
   */
  explicit application(time_frame &&minTimestep);

  virtual ~application();

  /**
   * This is the first function called after class creation.
   * It's used for registering user application event handlers to event
   * controller here.
   *
   * NOTE: Base class should be called, if user extend this function.
   */
  virtual void register_event_handlers();

  /**
   * This is second function called after class creation.
   * It's used for initializing debugger, logger and window.
   *
   * NOTE: When this function is being extended, it either should be called by
   * extender, or its logic should be copied.
   */
  virtual void init();

  void close();

  /**
   * Main game loop.
   */
  void run();

  /**
   * Application main loop, loops through layers queue and calls on_update
   * function of each queue element. This function adds to the end of this
   * queue, provided layer.
   *
   * @param layer - layer to be pushed at the end of layers queue
   */
  void push_lLayer(layer *layer);

  void push_overlay(layer *layer);

  /**
   * User must choose platform specific window implementation. This function is
   * used by application class for initialization purposes.
   */
  virtual window *get_window() = 0;

  virtual void cleanup();

protected:
  event_controller m_EventController;

private:
  layer_stack m_LayerStack;

  bool m_IsRunning;
  const time_frame m_MinTimestep;
};

extern application *create_application();

} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////