//
// Created by christian on 10/20/21.
//
#include "asset/entity/gltf/gltf_mesh_asset.h"
#include "core/stinky_macros.h"
#include "core/uuid.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <tiny_gltf.h>
#include <vector>

#include <iostream>

namespace stinky {

gltf_mesh_asset::gltf_mesh_asset(const tinygltf::Model &_model, int _mesh_index) {
    deserialize(_model, _mesh_index);
}

gltf_mesh_asset::~gltf_mesh_asset() = default;

void gltf_mesh_asset::load() {}

void gltf_mesh_asset::deserialize(const tinygltf::Model &_model, int _mesh_index) {
  auto &_mesh = _model.meshes[_mesh_index];

  auto &_primitives = _mesh.primitives;
  sub_meshes.reserve(_primitives.size());

  for (auto &_primitive : _primitives) {
    sub_mesh _sub_mesh;
    auto &_index_buffer_accessor = _model.accessors[_primitive.indices];
    auto &attributes = _primitive.attributes;

    auto _position_it = attributes.find("POSITION");
    auto _tex_coord_it = attributes.find("TEXCOORD_0");
    auto _normal_it = attributes.find("NORMAL");
    auto _tangent_it = attributes.find("TANGENT");

    BreakIf(_position_it == attributes.end() ||
            _tex_coord_it == attributes.end() ||
            _normal_it == attributes.end() || _tangent_it == attributes.end());

    {
      auto &_buffer_accessor = _model.accessors[_position_it->second];
      auto &_buffer_view = _model.bufferViews[_buffer_accessor.bufferView];
      auto _offset = _buffer_accessor.byteOffset + _buffer_view.byteOffset;
      auto &_buffer = _model.buffers[_buffer_view.buffer];

      AssertBreakUnless(_buffer_accessor.type == TINYGLTF_TYPE_VEC3)

          if (_buffer_accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
        auto _type_size =
            tinygltf::GetComponentSizeInBytes(TINYGLTF_COMPONENT_TYPE_FLOAT);
        auto &_vertices = _sub_mesh.vertices;
        _vertices.reserve(_buffer_accessor.count);
        for (auto *_data_it = &_buffer.data[_offset];
             _data_it < &_buffer.data[_offset] +
                            (_buffer_accessor.ByteStride(_buffer_view) *
                             _buffer_accessor.count);
             _data_it += (_type_size * 3)) {
          vertex tmp;

          memcpy(&tmp.position.x, _data_it, _type_size * 3);

          _vertices.emplace_back(tmp);
        }
      }
    }

    sub_meshes.emplace_back(std::move(_sub_mesh));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void gltf_mesh_asset::serialize(const tinygltf::Model &_model, int meshIndex) const {

}
} // namespace stinky