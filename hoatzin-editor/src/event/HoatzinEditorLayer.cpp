#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <camera/PerspectiveCamera.h>
#include <camera/PerspectiveCameraController.h>
#include <ecs/CameraComponent.h>

#include <gla/GraphicLayerAbstractionFactory.h>
#include <gla/VertexBuffer.h>
#include <scene/Scene.h>
#include <panels/Workspace.h>
#include <panels/SceneHierarchyPanel.h>
#include <panels/EntityInspectorPanel.h>
#include <panels/ScenePanel.h>
#include <GLFW/glfw3.h>

#include "HoatzinEditorLayer.h"


namespace stinky::hoatzin {

    /////////////////////////////////////////////////////////////////////////////////////////
    HoatzinEditorLayer::HoatzinEditorLayer(GraphicLayerAbstractionFactory *glaFactory,
                                           PerspectiveCameraController *cameraController,
                                           uint32_t width, uint32_t height)
            : Layer("Hoatzin HoatzinEditorEditor Layer"), m_GLAFactory(glaFactory),
              m_Scene(glaFactory),
              m_SceneManager(glaFactory, m_Scene),
              m_CameraController(cameraController), m_Camera(CreateScope<PerspectiveCamera>(width, height)),
              m_FrameBuffer(glaFactory->CreateFrameBuffer({width, height})) {
        Entity entity(m_Scene.CreateEntity());
        entity.AddComponent<CameraComponent>(m_Camera.get(), true);

        m_CameraController->SetCamera(m_Camera.get());
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnAttach() {
        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        m_SceneManager.LoadSceneFromFile("default");
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::OnUpdate(const Timestep &ts) {
        const auto &frameBufferSpecification = m_FrameBuffer->GetSpecification();
        if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0 &&
            !(m_ViewportSize.x == frameBufferSpecification.Height &&
              m_ViewportSize.y == frameBufferSpecification.Width)) {
            m_FrameBuffer->WindowResize(m_ViewportSize.x, m_ViewportSize.y);
            m_CameraController->OnWindowResize(m_ViewportSize.x, m_ViewportSize.y);
        }
        /** Render current scene */
        m_FrameBuffer->Bind();

        m_CameraController->OnUpdate(ts);
        m_Scene.OnUpdate();

        m_FrameBuffer->Unbind();
        /** Render current scene */

        /** Render editor */
        ImGuiBegin();
        ImGuiRender();
        ImGuiEnd();
        /** Render editor */
    }

    void HoatzinEditorLayer::OnDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::ImGuiBegin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void HoatzinEditorLayer::ImGuiRender() {
        ImGui::ShowDemoWindow();
        Workspace::Begin();

        SceneHierarchyPanel::Render(m_Scene, m_SelectedEntt);

        EntityInspectorPanel::Render(m_SelectedEntt);

        uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
        ScenePanel::Render(textureID, m_ViewportSize);

        Workspace::End();
    }

    /////////////////////////////////////////////////////////////////////////////////////////
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
