//
// Created by christian on 29/08/2020.
//

#include "camera/fps_camera.h"
#include "core/Time.h"

#include "stinkypch.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
fps_camera::fps_camera(uint32_t screenWidth, uint32_t screenHeight, float fov,
                       float zNear, float zFar)
    : camera(glm::perspective(glm::radians(fov),
                              (float)screenWidth / (float)screenHeight, zNear,
                              zFar)),
      perspective_camera_controller(0.09f, 0.8f), m_Yaw(0.0f), m_Pitch(0.0f),
      m_FocalPoint(0.0f) {
  glm::vec3 position = {-5, 5, 5};
  m_Distance = glm::distance(position, m_FocalPoint);

  fps_camera::recalculate_view_projection_matrix();
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::set_projection_rh(float fov, float aspectRatio, float zNear,
                                   float zFar) {
  _M_projection_matrix =
      glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
  _M_view_projection_matrix = _M_projection_matrix * _M_view_matrix;
}

void fps_camera::recalculate_view_projection_matrix() {
  ReturnUnless(_M_view_dirty);
  glm::vec3 position(CalculatePosition());

  glm::quat orientation = GetOrientation();
  _M_view_matrix =
      glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
  _M_view_matrix = glm::inverse(_M_view_matrix);
  _M_view_projection_matrix = _M_projection_matrix * _M_view_matrix;

  _M_view_dirty = false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::recalculate_view_matrix() {
  ReturnUnless(_M_view_dirty);
  glm::vec3 position(CalculatePosition());

  glm::quat orientation = GetOrientation();
  _M_view_matrix =
      glm::translate(glm::mat4(1.0f), position) * glm::toMat4(orientation);
  _M_view_matrix = glm::inverse(_M_view_matrix);

  _M_view_dirty = false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::pan(const glm::vec3 &oldMousePosition,
                     const glm::vec3 &newMousePosition, const time_frame &ts) {
  glm::vec3 delta = (newMousePosition - oldMousePosition) * 0.03f;

  auto [xSpeed, ySpeed] = PanSpeed();
  m_FocalPoint += -get_right_direction() * delta.x * xSpeed * m_Distance;
  m_FocalPoint += get_up_direction() * delta.y * ySpeed * m_Distance;

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::rotate(const glm::vec3 &oldMousePosition,
                        const glm::vec3 &newMousePosition,
                        const time_frame &ts) {
  glm::vec3 delta = (newMousePosition - oldMousePosition) * 0.009f;

  float yawSign = get_up_direction().y < 0 ? -1.0f : 1.0f;
  m_Yaw += yawSign * delta.x * m_RotationSpeed;
  m_Pitch += delta.y * m_RotationSpeed;

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::translate(const glm::vec3 &delta) {
  auto [xSpeed, ySpeed] = PanSpeed();
  m_FocalPoint += -get_right_direction() * delta.x * 0.7f * xSpeed * m_Distance;
  m_FocalPoint += get_up_direction() * delta.y * 0.7f * ySpeed * m_Distance;
  zoom(-delta.z, 0.0f);

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::zoom(float yOffset, float xOffset) {
  m_Distance -= yOffset * zoom_speed() * 0.07f;
  if (m_Distance < 1.0f) {
    m_FocalPoint += get_forward_direction();
    m_Distance = 1.0f;
  }

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void fps_camera::on_window_resize(uint32_t width, uint32_t height) {
  m_ViewportWidth = width;
  m_ViewportHeight = height;
  float aspectRatio = static_cast<float>(m_ViewportWidth) /
                      static_cast<float>(m_ViewportHeight);
  set_projection_rh(45, aspectRatio, 1, -1);
  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 fps_camera::get_up_direction() const {
  return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 fps_camera::get_right_direction() const {
  return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 fps_camera::get_forward_direction() const {
  return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 fps_camera::CalculatePosition() const {
  return m_FocalPoint - get_forward_direction() * m_Distance;
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::quat fps_camera::GetOrientation() const {
  return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
std::pair<float, float> fps_camera::PanSpeed() const {
  float x = std::min(m_ViewportWidth / 1000.0f, 2.4f); // max = 2.4f
  float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

  float y = std::min(m_ViewportHeight / 1000.0f, 2.4f); // max = 2.4f
  float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

  return {xFactor, yFactor};
}

/////////////////////////////////////////////////////////////////////////////////////////
float fps_camera::zoom_speed() const {
  float distance = m_Distance * 0.2f;
  distance = std::max(distance, 0.0f);
  float speed = distance * distance;
  speed = std::min(speed, 100.0f); // max speed = 100
  return speed;
}
} // namespace stinky