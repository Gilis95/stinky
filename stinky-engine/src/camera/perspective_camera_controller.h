//
// Created by christian on 29/08/2020.
//

#pragma once

#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "core/keyboard_codes.h"
#include "stinky_prerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class perspective_camera_controller {
public:
  perspective_camera_controller(float translationSpeed, float rotationSpeed);

  ~perspective_camera_controller();

public:
  virtual void pan(const glm::vec3 &oldMousePosition,
                   const glm::vec3 &newMousePosition, const time_frame &ts) = 0;

  // Camera Rotation
  virtual void rotate(const glm::vec3 &oldMousePosition,
                      const glm::vec3 &newMousePosition,
                      const time_frame &ts) = 0;
  virtual void translate(const glm::vec3 &delta) = 0;

  virtual void on_window_resize(uint32_t width, uint32_t height) = 0;

public:
  // Camera move trough XYZ
  void move_left();
  void move_right();
  void move_up();
  void move_down();
  void move_near();
  void move_far();

  void on_update(const time_frame &ts);

  void on_keyboard_event(const key_pressed_event &event);

  void on_mouse_scrolled(const mouse_scrolled_event &event);
  void on_mouse_pressed(const mouse_button_pressed_event &event);
  void on_mouse_released(const mouse_button_released_event &event);
  void on_mouse_moved(const mouse_moved_event &event);

  void on_window_resize(const window_resize_event &event);

protected:
  float m_TranslationSpeed;
  float m_RotationSpeed;

private:
  glm::vec3 _M_old_mouse_position, _M_new_mouse_position;
  bool _M_left_mouse_button_pressed, _M_middle_mouse_button_pressed, m_Rotate,
      m_Pan;

  glm::vec3 _M_translation_vec;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////