#pragma once

#include <cstdint>
#include <entt/entity/registry.hpp>

#include "stinkypch.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Entity {
    public:
        explicit Entity(entt::registry &registry) : m_Registry(registry), m_EntityHandle(registry.create()) {}

        Entity(const Entity &other) = default;

        template<typename T, typename... Args>
        bool AddComponent(Args &&... args) {
            AssertReturnIf(HasComponent<T>(), false);
            m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            return true;
        }

        template<typename T>
        std::pair<bool, T> GetComponent() {
            static T s_Empty;
            AssertReturnUnless(HasComponent<T>(), std::make_pair(false, s_Empty));
            return std::make_pair(true, m_Registry.get<T>(m_EntityHandle));
        }

        template<typename T>
        bool HasComponent() {
            return m_Registry.has<T>(m_EntityHandle);
        }

        template<typename T>
        bool RemoveComponent() {
            AssertReturnUnless(HasComponent<T>(), false);
            m_Registry.remove<T>(m_EntityHandle);
            return true;
        }

        operator void *() { return m_EntityHandle == entt::null ? nullptr : this; }

        operator bool() const { return m_EntityHandle != entt::null; }

        explicit operator unsigned() const { return (unsigned) m_EntityHandle; }

        bool operator==(const Entity &other) const {
            return m_EntityHandle == other.m_EntityHandle;
        }

        bool operator!=(const Entity &other) const {
            return !(*this == other);
        }

    private:
        entt::entity m_EntityHandle{entt::null};
        entt::registry &m_Registry;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////