//
// Created by christian on 29/08/2020.
//

#pragma once

#include "camera/camera.h"
#include "perspective_camera_controller.h"
#include <glm/detail/type_quat.hpp>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
class track_ball_camera : public camera, public perspective_camera_controller {
public:
  explicit track_ball_camera(uint32_t screen_width = 1280,
                             uint32_t screen_height = 720, float fov = 45.0f,
                             float z_near = 1.0f, float z_far = -1.0f);

  ~track_ball_camera() override = default;

  void set_projection_rh(float fov, float aspectRatio, float zNear, float zFar);

  void set_rotation(const glm::quat &rot);

  [[nodiscard]] glm::quat get_rotation() const;

  // Rotate the camera by some amount.
  void rotate(const glm::quat &rot);

public:
  // Controller functions
  void pan(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition,
           const time_frame &ts) override;
  void rotate(const glm::vec3 &oldMousePosition,
              const glm::vec3 &newMousePosition, const time_frame &ts) override;
  void translate(const glm::vec3 &delta) override;
  void Zoom(float yOffset, float xOffset);
  void on_window_resize(uint32_t width, uint32_t height) override;
  // Controller functions
protected:
  void recalculate_view_projection_matrix() override;
  void recalculate_view_matrix() override;

private:
  [[nodiscard]] glm::vec3 GetUpDirection() const;
  [[nodiscard]] glm::vec3 GetRightDirection() const;
  [[nodiscard]] glm::vec3 GetForwardDirection() const;
  [[nodiscard]] glm::vec3 CalculatePosition() const;

  [[nodiscard]] float ZoomSpeed() const;
  [[nodiscard]] std::pair<float, float> PanSpeed() const;

private:
  float _M_distance;
  glm::quat _M_rotation;

  uint32_t _M_viewport_width, _M_viewport_height;

  glm::vec3 _M_focal_point;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////