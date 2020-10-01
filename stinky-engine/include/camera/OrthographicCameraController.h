//
// Created by christian on 23/08/2020.
//

#pragma once

#include <list>
#include <unordered_map>
#include <functional>

#include "event/KeyEvent.h"
#include "event/Timestep.h"
#include "OrthographicCamera.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OrthographicCameraController {
    public:
        explicit OrthographicCameraController(OrthographicCamera &camera, float aspectRatio);

        void OnUpdate(const Timestep &ts);
        void OnKeyboardEvent(const Event &keyPressedEvent);

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void RotateLeft();
        void RotateRight();

        void OnWindowResize(const Event &event);
        void WindowResize(float width, float height);

        void OnZoom(const Event &e);

    private:
        OrthographicCamera &m_Camera;

        glm::vec3 m_CameraPosition;
        float m_CameraSpeed;
        float m_CameraRotation, m_CameraRotationSpeed;
        float m_AspectRatio, m_ZoomLevel;

        std::unordered_map<KeyCode, std::function<void()>> m_CameraMoveFunctions;
    };
}