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
class fps_camera : public camera, public perspective_camera_controller {
public:
  explicit fps_camera(uint32_t screenWidth = 1280, uint32_t screenHeight = 720,
                      float fov = 45.0f, float zNear = 1.0f,
                      float zFar = -1.0f);
  ~fps_camera() override = default;

  void set_projection_rh(float fov, float aspectRatio, float zNear, float zFar);

public:
  void pan(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition,
           const time_frame &ts) override;
  // Controller extension
  void rotate(const glm::vec3 &oldMousePosition,
              const glm::vec3 &newMousePosition, const time_frame &ts) override;
  void translate(const glm::vec3 &delta) override;
  void zoom(float yOffset, float xOffset);
  void on_window_resize(uint32_t width, uint32_t height) override;
  // Controller extension
protected:
  void recalculate_view_projection_matrix() override;
  void recalculate_view_matrix() override;

private:
  [[nodiscard]] glm::vec3 get_up_direction() const;
  [[nodiscard]] glm::vec3 get_right_direction() const;
  [[nodiscard]] glm::vec3 get_forward_direction() const;
  [[nodiscard]] glm::vec3 CalculatePosition() const;
  [[nodiscard]] glm::quat GetOrientation() const;

  [[nodiscard]] float zoom_speed() const;
  [[nodiscard]] std::pair<float, float> PanSpeed() const;

private:
  float m_Distance, m_Yaw, m_Pitch;

  uint32_t m_ViewportWidth, m_ViewportHeight;

  glm::vec3 m_FocalPoint;
};
} // namespace stinky
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////