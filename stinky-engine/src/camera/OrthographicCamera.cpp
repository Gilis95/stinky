//
// Created by christian on 23/08/2020.
//
#include "camera/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "core/StinkyMacros.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
            : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f),
              m_ViewDirty(false), m_Position(0.0f), m_Rotation(0.0f) {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCamera::Translate(const glm::vec3 &delta) {
        m_Position += delta;
        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCamera::Rotate(float deltaRotation) {
        m_Rotation += deltaRotation;

        if (m_Rotation == 360.0f || m_Rotation == -360.0f) {
            m_Rotation = 0;
        }

        m_ViewDirty = true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void OrthographicCamera::RecalculateViewMatrix() {
        ReturnUnless(m_ViewDirty)
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
                              glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation),
                                          glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

        m_ViewDirty = false;
    }

}