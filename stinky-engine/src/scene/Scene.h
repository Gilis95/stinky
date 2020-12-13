//
// Created by christian on 07/10/2020.
//

#pragma once

#include <entt/entity/registry.hpp>

#include "ecs/Entity.h"
#include "renderer/Renderer.h"
#include "StinkyPrerequisites.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Entity;

    class Scene {
    public:
        explicit Scene(const GraphicLayerAbstractionFactory *rendererFactory);
        ~Scene() = default;

        void Render();

        void OnClose();

        /** NOTE:: maybe in separate class */
        Entity CreateEntity();

        void each(std::function<void (Entity& entt)> func);
    private:
        entt::registry m_Registry;
        Scope<Renderer> m_Renderer;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
