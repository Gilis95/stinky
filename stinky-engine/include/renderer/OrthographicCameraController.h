//
// Created by christian on 23/08/2020.
//

#pragma once

#include <list>
#include <unordered_map>
#include <functional>

#include "event/KeyEvent.h"
#include "event/Timestep.h"
#include "renderer/OrthographicCamera.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class OrthographicCameraController {
    public:
        explicit OrthographicCameraController(OrthographicCamera &camera, float aspectRatio);

        void OnUpdate(const Timestep &ts);

        void OnKeyboardEvent(const Event &keyPressedEvent);

        void MoveLeft(const Timestep &ts);

        void MoveRight(const Timestep &ts);

        void MoveUp(const Timestep &ts);

        void MoveDown(const Timestep &ts);

        void RotateLeft(const Timestep &ts);

        void RotateRight(const Timestep &ts);

        void OnWindowResize(const Event &event);

        void WindowResize(float width, float height);

        void OnZoom(const Event &e);

    private:
        OrthographicCamera &m_Camera;

        glm::vec3 m_CameraPosition;
        float m_CameraSpeed;
        float m_CameraRotation, m_CameraRotationSpeed;
        float m_AspectRatio, m_ZoomLevel;

        std::list<KeyCode> m_Commands;
        std::unordered_map<KeyCode, std::function<void(const Timestep &)>> m_CameraMoveFunctions;
    };
}