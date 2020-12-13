//
// Created by christian on 29/08/2020.
//

#pragma once

#include <glm/detail/type_quat.hpp>
#include "camera/Camera.h"
#include "PerspectiveCameraController.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class FPSCamera : public Camera, public PerspectiveCameraController {
    public:
        explicit FPSCamera(int screenWidth = 1280, int screenHeight = 720, float fov = 45.0f,
                                   float zNear = 1.0f, float zFar = -1.0f);
        ~FPSCamera() override = default;

        void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

        // Controller extension
        void Rotate(const glm::vec3 &oldMousePosition, const glm::vec3 &newMousePosition,  const Timestep& ts) override;
        void Translate(const glm::vec3 &delta, bool local) override;
        void OnWindowResize(uint32_t width, uint32_t height) override;
        // Controller extension
    protected:
        void RecalculateViewProjectionMatrix() override;
        void RecalculateViewMatrix() override;
    private:
        float m_Yaw;
        float m_Pitch;

        glm::quat m_QuatRotation;
        glm::mat4 m_Mat4Rotation;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////