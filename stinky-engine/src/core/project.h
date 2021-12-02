//
// Created by christian on 7/13/21.
//

#ifndef STINKY_PROJECT_H
#define STINKY_PROJECT_H

#include <string>

namespace stinky {
struct project {
  std::string name{};
  std::string rootDir{};
  std::string assetDir{};
};

class project_manager {
private:
  project_manager() = default;
  ~project_manager() = default;

public:
  static project_manager &instance();
  static void destroy();

  bool open(const std::string &projectFile);
  void save(const std::string &projectFile) const;

public:
  project _M_project;

private:
  static project_manager *_S_Instance;
};
} // namespace stinky

#endif // STINKY_PROJECT_H
