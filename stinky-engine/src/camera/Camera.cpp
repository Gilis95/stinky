//
// Created by christian on 12/10/2020.
//

#include "camera/Camera.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    Camera::Camera(glm::mat4 &projectionMatrix) : m_ProjectionMatrix(projectionMatrix), m_ViewMatrix(1),
                                                  m_ViewProjectionMatrix(m_ProjectionMatrix) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    Camera::Camera(glm::mat4 &&projectionMatrix) : m_ProjectionMatrix(std::forward<glm::mat4>(projectionMatrix)),
                                                   m_ViewMatrix(1),
                                                   m_ViewProjectionMatrix(m_ProjectionMatrix) {}

    /////////////////////////////////////////////////////////////////////////////////////////
    Camera::Camera(Camera &&camera) noexcept: Camera(camera.m_ProjectionMatrix) {}
}