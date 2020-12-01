//
// Created by christian on 04/11/2020.
//

#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky{
    class Scene;
    class Entity;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky::hoatzin::SceneHierarchyPanel {
    /**
     * @param scene - scene entities will be loaded from
     * @param outSelectedEntity - selected entity will be written to this param
     */
    void Render(Scene& scene, Entity& outSelectedEntity);
}