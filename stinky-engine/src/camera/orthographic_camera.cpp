//
// Created by christian on 23/08/2020.
//
#include "camera/orthographic_camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/stinky_macros.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
orthographic_camera::orthographic_camera(float left, float right, float bottom,
                                         float top)
    : camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      m_ViewDirty(false), m_Rotation(0.0f) {}

/////////////////////////////////////////////////////////////////////////////////////////
void orthographic_camera::translate(const glm::vec3 &delta) {
  if (true) {
    _M_position += m_Rotation * delta;
  } else {
    _M_position += delta;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void orthographic_camera::rotate(float deltaRotation) {
  m_Rotation += deltaRotation;

  if (m_Rotation == 360.0f || m_Rotation == -360.0f) {
    m_Rotation = 0;
  }

  m_ViewDirty = true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void orthographic_camera::set_projection(float left, float right, float bottom,
                                         float top) {
  _M_projection_matrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
  _M_view_projection_matrix = _M_projection_matrix * _M_view_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////
void orthographic_camera::recalculate_view_projection_matrix() {
  ReturnUnless(m_ViewDirty) glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), _M_position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation),
                  glm::vec3(0, 0, 1));

  _M_view_matrix = glm::inverse(transform);
}

/////////////////////////////////////////////////////////////////////////////////////////
void orthographic_camera::recalculate_view_matrix() {
  ReturnUnless(m_ViewDirty) glm::mat4 transform =
      glm::translate(glm::mat4(1.0f), _M_position) *
      glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation),
                  glm::vec3(0, 0, 1));

  _M_view_matrix = glm::inverse(transform);
  _M_view_projection_matrix = _M_projection_matrix * _M_view_matrix;

  m_ViewDirty = false;
}

} // namespace stinky