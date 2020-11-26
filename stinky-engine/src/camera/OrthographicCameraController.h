//
// Created by christian on 23/08/2020.
//

#pragma once

#include <unordered_map>
#include <functional>

#include "StinkyPrerequisites.h"
#include "core/KeyboardCodes.h"


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class OrthographicCameraController {
    public:
        explicit OrthographicCameraController(OrthographicCamera &camera, float aspectRatio);

        void OnUpdate(const Timestep &ts);
        void OnKeyboardEvent(const KeyPressedEvent &keyPressedEvent);

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void RotateLeft();
        void RotateRight();

        void OnWindowResize(const WindowResizeEvent &event);
        void WindowResize(float width, float height);

        void OnZoom(const MouseScrolledEvent &e);

    private:
        OrthographicCamera &m_Camera;

        glm::vec3 m_CameraPosition;
        float m_CameraSpeed;
        float m_CameraRotation, m_CameraRotationSpeed;
        float m_AspectRatio, m_ZoomLevel;

        std::unordered_map<KeyCode, std::function<void()>> m_CameraMoveFunctions;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////