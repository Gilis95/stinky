//
// Created by christian on 29/08/2020.
//

#include "camera/track_ball_camera.h"
#include "core/Time.h"
#include <Tracy.hpp>

#include "stinkypch.h"

namespace stinky {

/////////////////////////////////////////////////////////////////////////////////////////
track_ball_camera::track_ball_camera(uint32_t screen_width,
                                     uint32_t screen_height, float fov,
                                     float z_near, float z_far)
    : camera(glm::perspective(glm::radians(fov),
                              (float)screen_width / (float)screen_height,
                              z_near, z_far)),
      perspective_camera_controller(0.04f, 0.56f),
      _M_rotation(1.0, 0.0, 0.0, 0.0), _M_viewport_width(screen_width),
      _M_viewport_height(screen_height), _M_focal_point(0.0f) {
  glm::vec3 position = {-5, 5, 5};
  _M_distance = glm::distance(position, _M_focal_point);

  track_ball_camera::recalculate_view_projection_matrix();
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::set_projection_rh(float fov, float aspectRatio,
                                          float zNear, float zFar) {
  _M_projection_matrix =
      glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
  _M_view_projection_matrix = _M_projection_matrix * _M_view_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::set_rotation(const glm::quat &rot) {
  _M_rotation = rot;
  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::quat track_ball_camera::get_rotation() const { return _M_rotation; }

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::rotate(const glm::quat &rot) {
  _M_rotation *= rot;
  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::recalculate_view_projection_matrix() {
  ReturnUnless(_M_view_dirty) glm::mat4 translate =
      glm::translate(-_M_position);
  glm::mat4 rotate = glm::toMat4(_M_rotation);

  _M_view_matrix = translate * rotate;
  _M_view_projection_matrix = _M_projection_matrix * _M_view_matrix;
  _M_view_dirty = false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::recalculate_view_matrix() {
  ReturnUnless(_M_view_dirty) glm::vec3 position(CalculatePosition());

  _M_view_matrix =
      glm::translate(glm::mat4(1.0f), position) * glm::toMat4(_M_rotation);
  _M_view_matrix = glm::inverse(_M_view_matrix);

  _M_view_dirty = false;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::pan(const glm::vec3 &oldMousePosition,
                            const glm::vec3 &newMousePosition,
                            const time_frame &ts) {
  glm::vec3 delta = (newMousePosition - oldMousePosition) * 0.03f;

  auto [xSpeed, ySpeed] = PanSpeed();
  _M_focal_point += -GetRightDirection() * delta.x * xSpeed * _M_distance;
  _M_focal_point += GetUpDirection() * delta.y * ySpeed * _M_distance;

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::rotate(const glm::vec3 &oldMousePosition,
                               const glm::vec3 &newMousePosition,
                               const time_frame &ts) {
  glm::vec3 rotVector = glm::normalize(
      glm::cross(newMousePosition - oldMousePosition, glm::vec3(0, 0, -2)));

  float rotationAngle =
      glm::acos(std::clamp(glm::dot(glm::normalize(oldMousePosition),
                                    glm::normalize(newMousePosition)),
                           -1.0f, 1.0f)) *
      ts.MiliSeconds() * m_RotationSpeed;
  float rotationAngleCos = glm::cos(rotationAngle);
  float rotationAngleSin = glm::sin(rotationAngle);

  glm::quat rotQuat(rotationAngleCos, rotationAngleSin * rotVector);

  rotate(rotQuat);
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::translate(const glm::vec3 &delta) {
  auto [xSpeed, ySpeed] = PanSpeed();
  _M_focal_point +=
      -GetRightDirection() * delta.x * 0.3f * xSpeed * _M_distance;
  _M_focal_point += GetUpDirection() * delta.y * 0.3f * ySpeed * _M_distance;
  Zoom(-delta.z, 0.0f);

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::Zoom(float yOffset, float xOffset) {
  _M_distance -= yOffset * ZoomSpeed() * 0.08f;
  if (_M_distance < 1.0f) {
    _M_focal_point += GetForwardDirection();
    _M_distance = 1.0f;
  }

  _M_view_dirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void track_ball_camera::on_window_resize(uint32_t width, uint32_t height) {
  float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
  set_projection_rh(45, aspectRatio, 1, -1);
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 track_ball_camera::GetUpDirection() const {
  return glm::rotate(_M_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 track_ball_camera::GetRightDirection() const {
  return glm::rotate(_M_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 track_ball_camera::GetForwardDirection() const {
  return glm::rotate(_M_rotation, glm::vec3(0.0f, 0.0f, -1.0f));
}

/////////////////////////////////////////////////////////////////////////////////////////
glm::vec3 track_ball_camera::CalculatePosition() const {
  return _M_focal_point - GetForwardDirection() * _M_distance;
}

/////////////////////////////////////////////////////////////////////////////////////////
std::pair<float, float> track_ball_camera::PanSpeed() const {
  float x = std::min(_M_viewport_width / 1000.0f, 2.4f); // max = 2.4f
  float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

  float y = std::min(_M_viewport_height / 1000.0f, 2.4f); // max = 2.4f
  float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

  return {xFactor, yFactor};
}

/////////////////////////////////////////////////////////////////////////////////////////
float track_ball_camera::ZoomSpeed() const {
  float distance = _M_distance * 0.2f;
  distance = std::max(distance, 0.0f);
  float speed = distance * distance;
  speed = std::min(speed, 100.0f); // max speed = 100
  return speed;
}
} // namespace stinky