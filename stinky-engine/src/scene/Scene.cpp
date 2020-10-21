//
// Created by christian on 05/10/2020.
//

#include "scene/Scene.h"

#include <entt/entt.hpp>

#include "camera/Camera.h"
#include "ecs/CameraComponent.h"
#include "ecs/Entity.h"
#include "ecs/MaterialComponent.h"
#include "ecs/MeshComponents.h"
#include "ecs/ProgramComponent.h"
#include "ecs/TransformationComponents.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {

    /////////////////////////////////////////////////////////////////////////////////////////
    Scene::Scene(const GraphicLayerAbstractionFactory *rendererFactory) : m_Renderer(
            CreateScope<Renderer>(rendererFactory)) {
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    Entity Scene::CreateEntity() {
        return Entity(m_Registry);
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void Scene::OnUpdate() {
        auto camerasView = m_Registry.view<CameraComponent>();

        Camera *camera;

        for (auto cameraView:  camerasView) {
            auto &tmpCameraRef = camerasView.get<CameraComponent>(cameraView);
            ContinueUnless(tmpCameraRef.m_IsPrimary)
            camera = tmpCameraRef.m_Camera;
        }

        m_Renderer->Clear();
        m_Renderer->BeginScene(camera->GetViewProjectionMatrix());

        auto meshesGroup = m_Registry.group<MeshComponent, TranslateComponent, ScaleComponent, ProgramComponent, MaterialComponent>();

        for (auto mesh : meshesGroup) {
            m_Renderer->Draw({
                                     meshesGroup.get<MeshComponent>(mesh),
                                     meshesGroup.get<TranslateComponent>(mesh),
                                     meshesGroup.get<ScaleComponent>(mesh),
                                     meshesGroup.get<ProgramComponent>(mesh),
                                     meshesGroup.get<MaterialComponent>(mesh)
                             });
        }

        m_Renderer->EndScene();
    }
}