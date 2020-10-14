//
// Created by christian on 07/10/2020.
//

#pragma once

#include <entt/entity/registry.hpp>
#include <renderer/Renderer.h>
#include "stinkypch.h"
#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Entity;

    class Scene {
    public:
        explicit Scene(const GraphicLayerAbstractionFactory *rendererFactory);
        ~Scene() = default;
        Entity CreateCubeEntity();

        Entity CreateCameraEntity();

        void OnUpdate();
    private:
        entt::registry m_Registry;
        Scope<Renderer> m_Renderer;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
