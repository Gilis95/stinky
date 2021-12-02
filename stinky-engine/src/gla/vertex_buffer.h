//
// Created by christian on 1/19/20.
//
#pragma once

#include <utility>
#include <vector>

#include "core/stinky_logger.h"
#include "core/stinky_macros.h"

namespace stinky {
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * from 1st to 16th byte
 */
enum class component_type : uint32_t {
  FLOAT = 1 << 0,
  DOUBLE = 1 << 1,
  INT32 = 1 << 2,
  INT64 = 1 << 3,
  BOOL = 1 << 4
};

/**
 * from 16th to 32nd byte
 */
enum class param_type : uint32_t {
  SCALAR = 1 << 16,
  VEC2 = 1 << 17,
  VEC3 = 1 << 18,
  VEC4 = 1 << 19,
  MAT3 = 1 << 20,
  MAT4 = 1 << 21,
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
struct BufferElement {
public:
  /////////////////////////////////////////////////////////////////////////////////////////
  BufferElement() = default;

  /////////////////////////////////////////////////////////////////////////////////////////
  BufferElement(component_type _component_type, param_type _param_type,
                std::string _name, bool _normalized = false, size_t _offset = 0)
      : name(std::move(_name)), type(static_cast<uint32_t>(_component_type) |
                                     static_cast<uint32_t>(_param_type)),
        size(ShaderDataTypeSize(type)), offset(_offset),
        normalized(_normalized) {}

public:
  /////////////////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] static uint32_t ShaderDataTypeSize(uint32_t _type) {
    size_t _type_size = 0;

    if (_type & static_cast<uint32_t>(component_type::FLOAT)) {
      _type_size = sizeof(float);
    } else if (_type & static_cast<uint32_t>(component_type::INT32)) {
      _type_size = sizeof(uint32_t);
    } else if (_type & static_cast<uint32_t>(component_type::INT64)) {
      _type_size = sizeof(int64_t);
    } else if (_type & static_cast<uint32_t>(component_type::BOOL)) {
      _type_size = sizeof(bool);
    } else {
      STINKY_ERROR("Unknown component type!");
      return 0;
    }

    uint32_t _elements_count = GetComponentCount(_type);

    return _type_size * _elements_count;
  }

  /////////////////////////////////////////////////////////////////////////////////////////
  [[nodiscard]] static uint32_t GetComponentCount(uint32_t _type) {
    if (_type & static_cast<uint32_t>(param_type::SCALAR)) {
      return 1;
    } else if (_type & static_cast<uint32_t>(param_type::VEC2)) {
      return 2;
    } else if (_type & static_cast<uint32_t>(param_type::VEC3)) {
      return 3;
    } else if (_type & static_cast<uint32_t>(param_type::VEC4)) {
      return 4;
    } else if (_type & static_cast<uint32_t>(param_type::MAT3)) {
      return 3 * 3;
    } else if (_type & static_cast<uint32_t>(param_type::MAT4)) {
      return 4 * 4;
    } else {
      STINKY_ERROR("Unknown param type!");
      return 0;
    }
  }

public:
  [[nodiscard]] uint32_t GetComponentCount() const {
    return GetComponentCount(type);
  }
public:
  static const uint32_t component_mask = 0xFFFF0000; // 15th to 30th bit
  static const uint32_t param_mask = 0x0000FFFF;     // 0 to 15th bit
public:
  std::string name;
  uint32_t type{};
  uint32_t size{};
  size_t offset{};
  bool normalized{};
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class BufferLayout {
public:
  BufferLayout(const std::initializer_list<BufferElement> &elements)
      : _M_elements(elements) {
    CalculateOffsetsAndStride();
  }

  [[nodiscard]] uint32_t GetStride() const { return _M_stride; }

  [[nodiscard]] const std::vector<BufferElement> &GetElements() const {
    return _M_elements;
  }

  std::vector<BufferElement>::iterator begin() { return _M_elements.begin(); }

  std::vector<BufferElement>::iterator end() { return _M_elements.end(); }

  [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const {
    return _M_elements.begin();
  }

  [[nodiscard]] std::vector<BufferElement>::const_iterator end() const {
    return _M_elements.end();
  }

private:
  void CalculateOffsetsAndStride() {
    size_t _offset = 0;
    _M_stride = 0;
    for (auto &_element : _M_elements) {
      _element.offset = _offset;
      _offset += _element.size;
      _M_stride += _element.size;
    }
  }

private:
  std::vector<BufferElement> _M_elements;
  uint32_t _M_stride = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
class vertex_buffer {
public:
  virtual ~vertex_buffer() = default;

  virtual void Bind() const = 0;

  virtual void Unbind() const = 0;

  virtual void SetData(const void *data, unsigned int size) = 0;

  [[nodiscard]] virtual const BufferLayout &GetBufferLayout() const = 0;

  virtual void SetBufferLayout(BufferLayout &layout) = 0;
};
} // namespace stinky
