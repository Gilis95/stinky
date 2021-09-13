//
// Created by christian on 23/08/2020.
//

#pragma once

#include <unordered_map>
#include <functional>

#include "StinkyPrerequisites.h"
#include "core/keyboard_codes.h"


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class orthographic_camera_controller {
    public:
        explicit orthographic_camera_controller(orthographic_camera &camera, float aspectRatio);

        void on_update(const time_frame &ts);
        void on_keyboard_event(const key_pressed_event &keyPressedEvent);

        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void RotateLeft();
        void RotateRight();

        void OnWindowResize(const window_resize_event &event);
        void WindowResize(float width, float height);

        void OnZoom(const mouse_scrolled_event &e);

    private:
        orthographic_camera &m_Camera;

        glm::vec3 m_CameraPosition;
        float m_CameraSpeed;
        float m_CameraRotation, m_CameraRotationSpeed;
        float m_AspectRatio, m_ZoomLevel;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////