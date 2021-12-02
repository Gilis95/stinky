//
// Created by christian on 12/10/2020.
//

#include "camera/camera.h"
#include "asset/asset_manager.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
camera::camera(glm::mat4 &projectionMatrix)
    : _M_projection_matrix(projectionMatrix), _M_view_matrix(1),
      _M_view_projection_matrix(_M_projection_matrix) {}

/////////////////////////////////////////////////////////////////////////////////////////
camera::camera(glm::mat4 &&projectionMatrix)
    : _M_projection_matrix(std::forward<glm::mat4>(projectionMatrix)),
      _M_view_matrix(1), _M_view_projection_matrix(_M_projection_matrix) {}

/////////////////////////////////////////////////////////////////////////////////////////
camera::camera(camera &&_camera) noexcept
    : camera(_camera._M_projection_matrix) {}
} // namespace stinky