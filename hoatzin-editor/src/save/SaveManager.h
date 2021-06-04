//
// Created by christian on 05/11/2020.
//

#pragma once

#include <string>

namespace stinky {
    class Scene;

    class GraphicLayerAbstractionFactory;
}

namespace stinky::hoatzin {

    class SaveManager {
    public:
        SaveManager(GraphicLayerAbstractionFactory* glaFactory, Scene &scene);

        void SaveSceneToFile(const std::string& path);

        void LoadSceneFromFile(std::string path);
    private:
        GraphicLayerAbstractionFactory *m_GLAFactory;
        Scene &m_Scene;
    };
}