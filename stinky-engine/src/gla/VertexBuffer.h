//
// Created by christian on 1/19/20.
//
#pragma once

#include <vector>

#include "core/StinkyLogger.h"
#include "core/StinkyMacros.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    enum class ShaderDataType {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
            default: STINKY_LOG_ERROR_AND_BREAK("Unknown ShaderDataType!");
                return 0;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    struct BufferElement {
    public:
        /////////////////////////////////////////////////////////////////////////////////////////
        BufferElement() = default;

        /////////////////////////////////////////////////////////////////////////////////////////
        BufferElement(ShaderDataType type, const std::string &name, bool normalized = false,
                      size_t offset = 0)
                : m_Name(name), m_Type(type), m_Size(ShaderDataTypeSize(type)), m_Offset(offset),
                  m_Normalized(normalized) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        [[nodiscard]] uint32_t GetComponentCount() const {
            switch (m_Type) {
                case ShaderDataType::Float:
                    return 1;
                case ShaderDataType::Float2:
                    return 2;
                case ShaderDataType::Float3:
                    return 3;
                case ShaderDataType::Float4:
                    return 4;
                case ShaderDataType::Mat3:
                    return 3; // 3* float3
                case ShaderDataType::Mat4:
                    return 4; // 4* float4
                case ShaderDataType::Int:
                    return 1;
                case ShaderDataType::Int2:
                    return 2;
                case ShaderDataType::Int3:
                    return 3;
                case ShaderDataType::Int4:
                    return 4;
                case ShaderDataType::Bool:
                    return 1;
                default: STINKY_LOG_ERROR_AND_BREAK("Unknown ShaderDataType!");
                    return 0;
            }
        }

    public:
        std::string m_Name;
        ShaderDataType m_Type;
        uint32_t m_Size;
        size_t m_Offset;
        bool m_Normalized;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class BufferLayout {
    public:
        BufferLayout(const std::initializer_list<BufferElement> &elements)
                : m_Elements(elements) {
            CalculateOffsetsAndStride();
        }

        [[nodiscard]] uint32_t GetStride() const { return m_Stride; }

        [[nodiscard]] const std::vector<BufferElement> &GetElements() const { return m_Elements; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }

        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

        [[nodiscard]] std::vector<BufferElement>::const_iterator
        begin() const { return m_Elements.begin(); }

        [[nodiscard]] std::vector<BufferElement>::const_iterator
        end() const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride() {
            size_t offset = 0;
            m_Stride = 0;
            for (auto &element : m_Elements) {
                element.m_Offset = offset;
                offset += element.m_Size;
                m_Stride += element.m_Size;
            }
        }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class VertexBuffer {
    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;

        virtual void Unbind() const = 0;

        virtual void SetData(const void *data, unsigned int size) = 0;

        [[nodiscard]] virtual const BufferLayout &GetBufferLayout() const = 0;

        virtual void SetBufferLayout(BufferLayout &layout) = 0;
    };
}
