//
// Created by christian on 7/13/21.
//

#include "stinkypch.h"
#include <filesystem>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "asset/asset_manager.h"
#include "core/project.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
project_manager *project_manager::_S_Instance = nullptr;

/////////////////////////////////////////////////////////////////////////////////////////
project_manager &project_manager::instance() {
  if (!_S_Instance)
    _S_Instance = new project_manager();

  return *_S_Instance;
}

/////////////////////////////////////////////////////////////////////////////////////////
void project_manager::destroy() { delete _S_Instance; }

/////////////////////////////////////////////////////////////////////////////////////////
bool project_manager::open(const std::string &projectFile) {
  std::ifstream projectFileStream(projectFile);
  ReturnUnless(projectFileStream, false);

  YAML::Node rootNode = YAML::Load(projectFileStream);

  YAML::Node projectNode(rootNode["project"]);
  ReturnUnless(projectNode, false);

  DESERIALIZE("name", projectNode, _M_project.name, std::string, false)
  DESERIALIZE("root_directory", projectNode, _M_project.rootDir, std::string,
              false)
  DESERIALIZE("asset_directory", projectNode, _M_project.assetDir, std::string,
              false)

  asset_manager::instance().register_directory(_M_project.assetDir);

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
void project_manager::save(const std::string &projectFile) const {
  std::ofstream projectFileStream(projectFile);
  YAML::Emitter out(projectFileStream);

  out << YAML::BeginMap;
  out << "project" << YAML::BeginMap;
  out << "name" << _M_project.name;
  out << "root_directory" << _M_project.rootDir;
  out << "asset_directory" << _M_project.assetDir;
  out << YAML::EndMap;
  out << YAML::EndMap;
}
} // namespace stinky