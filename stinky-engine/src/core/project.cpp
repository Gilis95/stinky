//
// Created by christian on 7/13/21.
//

#include "stinkypch.h"
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include "core/project.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    project_manager *project_manager::s_Instance = nullptr;

    /////////////////////////////////////////////////////////////////////////////////////////
    project_manager &project_manager::instance() {
        if (!s_Instance)
            s_Instance = new project_manager();

        return *s_Instance;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void project_manager::destroy() {
        delete s_Instance;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    bool project_manager::deserialize(const std::string &projectFile) {
        std::ifstream projectFileStream(projectFile);
        ReturnUnless(projectFileStream, false);

        YAML::Node rootNode = YAML::Load(projectFileStream);

        YAML::Node projectNode(rootNode["project"]);
        ReturnUnless(projectNode, false);

        SERIALIZE("name", projectNode, project.name, std::string, false)
        SERIALIZE("root_directory", projectNode, project.rootDir, std::string, false)
        SERIALIZE("asset_directory", projectNode, project.assetDir, std::string, false)

        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    void project_manager::serialize(const std::string &projectFile) const {
        std::ofstream projectFileStream(projectFile);
        YAML::Emitter out(projectFileStream);

        out << YAML::BeginMap;
        out << "project" << YAML::BeginMap;
        out << "name" << project.name;
        out << "root_directory" << project.rootDir;
        out << "asset_directory" << project.assetDir;
        out<<YAML::EndMap;
        out<<YAML::EndMap;
    }
}