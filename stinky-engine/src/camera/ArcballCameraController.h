//
// Created by christian on 29/08/2020.
//

#pragma once

#include <functional>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

#include "core/KeyboardCodes.h"
#include "StinkyPrerequisites.h"
#include "PerspectiveCameraController.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class ArcballCameraController : public PerspectiveCameraController {
    public:
        ArcballCameraController();

        explicit ArcballCameraController(ArcballCamera *camera);

        ~ArcballCameraController();

        inline void SetCamera(ArcballCamera *camera) {
            m_Camera = camera;
        }

        //Camera Rotation
        void Rotate(const Timestep &ts) override;
        void Translate(const Timestep &ts) override;

        void OnWindowResize(uint32_t width, uint32_t height) override;

    private:
        ArcballCamera *m_Camera = nullptr;

        float m_CameraSpeed = 400.0f;
        float m_RotationSpeed = 300.0f;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////