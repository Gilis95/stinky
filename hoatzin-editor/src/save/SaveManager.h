//
// Created by christian on 05/11/2020.
//

#pragma once

#include <string>

namespace stinky {
    class scene;

    class graphic_layer_abstraction_factory;
}

namespace stinky::hoatzin {

    class SaveManager {
    public:
        SaveManager(graphic_layer_abstraction_factory* glaFactory, scene &scene);

        void SaveSceneToFile(const std::string& path);

        void LoadSceneFromFile(std::string path);
    private:
        graphic_layer_abstraction_factory *m_GLAFactory;
        scene &m_Scene;
    };
}