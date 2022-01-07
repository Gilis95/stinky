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

/////////////////////////////////////////////////////////////////////////////////////////
bool copy_buffer(const tinygltf::Model &_model, size_t _accessor,
                 int _src_structure, int _src_component_type,
                 void *_target_buffer, size_t _target_offset,
                 size_t _target_stride) {
  auto &_buffer_accessor = _model.accessors[_accessor];
  AssertReturnUnless(_buffer_accessor.type == _src_structure, false);
  AssertReturnUnless(_buffer_accessor.componentType == _src_component_type,
                     false);

  auto &_buffer_view = _model.bufferViews[_buffer_accessor.bufferView];
  /**NOTE:: Possibly not working*/
  auto _offset = _buffer_accessor.byteOffset + _buffer_view.byteOffset;
  auto &_buffer = _model.buffers[_buffer_view.buffer];

  auto _src_stride = _buffer_accessor.ByteStride(_buffer_view);

  char *_c_target_buffer = static_cast<char *>(_target_buffer);
  _c_target_buffer += _target_offset;

  for (auto *_data_it = &_buffer.data[_offset];
       _data_it <
       &_buffer.data[_offset] + (_src_stride * _buffer_accessor.count);
       _data_it += _src_stride) {
    memcpy(_c_target_buffer, _data_it, _src_stride);
    _c_target_buffer += _target_stride;
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////
gltf_mesh_asset::gltf_mesh_asset(const tinygltf::Model &_model,
                                 int _mesh_index) {
  deserialize(_model, _mesh_index);
}

/////////////////////////////////////////////////////////////////////////////////////////
gltf_mesh_asset::~gltf_mesh_asset() = default;

/////////////////////////////////////////////////////////////////////////////////////////
void gltf_mesh_asset::load() {}

/////////////////////////////////////////////////////////////////////////////////////////
void gltf_mesh_asset::deserialize(const tinygltf::Model &_model,
                                  int _mesh_index) {
  size_t _float_size = sizeof(float);
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

    auto &_vertices = _sub_mesh.vertices;

    //fill empty
    {
      auto &_buffer_accessor = _model.accessors[_position_it->second];
      for (size_t i = 0; i < _buffer_accessor.count; ++i) {
        vertex tmp;
        _vertices.emplace_back(tmp);
      }
    }

    // mesh indices
    copy_buffer(_model, _position_it->second, TINYGLTF_TYPE_VEC3,
                    TINYGLTF_COMPONENT_TYPE_FLOAT, &_vertices[0].position.x,
                    0 * _float_size, 12 * _float_size);

    // mesh texture coordinates
    copy_buffer(_model, _tex_coord_it->second, TINYGLTF_TYPE_VEC2,
                TINYGLTF_COMPONENT_TYPE_FLOAT, &_vertices[0].position.x,
                3 * _float_size, 12 * _float_size);

    // normals
    copy_buffer(_model, _normal_it->second, TINYGLTF_TYPE_VEC3,
                TINYGLTF_COMPONENT_TYPE_FLOAT, &_vertices[0].position.x,
                5 * _float_size, 12 * _float_size);

    // tangents
    copy_buffer(_model, _tangent_it->second, TINYGLTF_TYPE_VEC4,
                TINYGLTF_COMPONENT_TYPE_FLOAT, &_vertices[0].position.x,
                8 * _float_size, 12 * _float_size);

    sub_meshes.emplace_back(std::move(_sub_mesh));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////
void gltf_mesh_asset::serialize(const tinygltf::Model &_model,
                                int meshIndex) const {}
} // namespace stinky