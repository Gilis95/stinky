#include <glm/ext.hpp>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include "HoatzinEditorLayer.h"

#include "camera/PerspectiveCamera.h"
#include "ecs/CameraComponent.h"
#include "ecs/Entity.h"
#include "ecs/MaterialComponent.h"
#include "ecs/MeshComponents.h"
#include "ecs/ProgramComponent.h"
#include "ecs/TransformationComponents.h"
#include "event/ApplicationEvent.h"
#include "gla/GraphicLayerAbstractionFactory.h"
#include "gla/VertexBuffer.h"
#include "ImGuiLayer.h"

namespace stinky::hoatzin {
    namespace {
        constexpr unsigned CUBE_VERTICES_COUNT = 32;
        glm::vec4 cubeVertices[8] = {
                //Front Quad
                {-1.0f, -1.0f, -1.0, 1.0f}, //0
                {1.0f,  -1.0f, -1.0, 1.0f}, //1
                {1.0f,  1.0f,  -1.0, 1.0f}, //2
                {-1.0f, 1.0f,  -1.0, 1.0f}, //3

                // Back Quad
                {1.0f,  -1.0f, 1.0,  1.0f}, //4
                {-1.0f, -1.0f, 1.0,  1.0f}, //5
                {-1.0f, 1.0f,  1.0,  1.0f}, //6
                {1.0f,  1.0f,  1.0,  1.0f} //7
        };

        constexpr unsigned int CUBE_INDICES_COUNT = 36;

        uint32_t cubeIndices[CUBE_INDICES_COUNT] = {
                // front side
                0, 1, 3, 1, 2, 3,

                // right side
                1, 4, 2, 4, 6, 2,

                // back side
                4, 5, 7, 5, 6, 7,

                // left side
                0, 5, 3, 5, 6, 3,

                // down side
                3, 2, 6, 2, 7, 6,

                // upper side
                0, 1, 2, 2, 3, 0
        };

        glm::vec4 quadVertices[4] = {
                {-1.0f, -1.0f, 1.0, 1.0f}, //0
                {1.0f,  -1.0f, 1.0, 1.0f}, //1
                {1.0f,  1.0f,  1.0, 1.0f}, //2
                {-1.0f, 1.0f,  1.0, 1.0f}, //3
        };

        uint32_t quadIndices[6] = {
                // front side
                0, 1, 3, 1, 2, 3
        };
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    HoatzinEditorLayer::HoatzinEditorLayer(EventController &eventController)
            : Layer("Hoatzin HoatzinEditorEditor Layer"),
              m_RendererFactory(GraphicLayerAbstractionFactory::create(GraphicLayerAbstractionFactory::API::OpenGL)),
              m_Camera(CreateScope<PerspectiveCamera>()),
              m_CameraController(CreateScope<PerspectiveCameraController>(m_Camera.get())),
              m_Scene(m_RendererFactory.get()) {
        Entity entity(m_Scene.CreateEntity());
        entity.AddComponent<CameraComponent>(m_Camera.get(), true);

        eventController.RegisterEventHandler(
                {
                        EventType::MouseButtonPressed,
                        [cameraController = m_CameraController.get()](const Event &event) {
                            cameraController->OnMousePressed(event);
                        }
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseMoved,
                        [capture0 = m_CameraController.get()](const Event &event) {
                            capture0->OnMouseMoved(event);
                        }
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::MouseButtonReleased,
                        [cameraController = m_CameraController.get()](const Event &event) {
                            cameraController->OnMouseReleased(event);
                        }
                }
        );

        eventController.RegisterEventHandler(
                {
                        EventType::KeyPressed,
                        [cameraController = m_CameraController.get()](const Event &event) {
                            cameraController->OnKeyboardEvent(event);
                        }
                }
        );
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnAttach() {
        m_FrameBuffer = m_RendererFactory->CreateFrameBuffer({1280, 720});
        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        auto entity = m_Scene.CreateEntity();
        entity.AddComponent<MeshComponent>(16, quadVertices, 6, quadIndices);
        entity.AddComponent<TranslateComponent>(glm::vec3(0.0f, 0.0f, -10.0f));
        entity.AddComponent<ScaleComponent>(glm::vec3(2.0f, 2.0f, 2.0f));
        entity.AddComponent<ProgramComponent>(m_RendererFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/skybox.glsl"));
        entity.AddComponent<MaterialComponent>(m_RendererFactory->CreateCubeTexture(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/skybox.png"));

        auto entity1 = m_Scene.CreateEntity();
        entity1.AddComponent<MeshComponent>(CUBE_VERTICES_COUNT, cubeVertices, CUBE_INDICES_COUNT, cubeIndices);
        entity1.AddComponent<TranslateComponent>(glm::vec3(0.8f, 0.0f, -2.0f));
        entity1.AddComponent<ScaleComponent>(glm::vec3(0.5f, 0.5f, 0.5f));
        entity1.AddComponent<ProgramComponent>(m_RendererFactory->CreateShader(
                "/home/christian/workspace/stinky/stinky-sandbox/resources/shaders/basic.shader"));
        entity1.AddComponent<MaterialComponent>(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnUpdate(const Timestep &ts) {
        m_FrameBuffer->Unbind();

        m_Scene.OnUpdate();
        m_CameraController->OnUpdate(ts);

        m_FrameBuffer->Bind();

        ImGuiBegin();
        ImGuiRender();
        ImGuiEnd();
    }

    void HoatzinEditorLayer::ImGuiBegin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void HoatzinEditorLayer::ImGuiRender() {
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    void HoatzinEditorLayer::ImGuiEnd() {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(1024, 720);

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}
