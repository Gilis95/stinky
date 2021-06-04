#pragma once

#include <cstdint>
#include <optional>
#include <entt/entity/registry.hpp>
#include "core/StinkyMacros.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class Entity {
    public:
        explicit Entity() : m_Registry(nullptr) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        explicit Entity(entt::registry *registry) : m_Registry(registry), m_EntityHandle(registry->create()) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        explicit Entity(entt::registry *registry, const entt::entity &entt) : m_Registry(registry),
                                                                              m_EntityHandle(entt) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        Entity(const Entity &other) : m_Registry(other.m_Registry), m_EntityHandle(other.m_EntityHandle) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        Entity(Entity &&other) noexcept: m_Registry(other.m_Registry),
                                         m_EntityHandle(std::move(other).m_EntityHandle) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename... Args>
        [[nodiscard]] bool AddComponent(Args &&... args) {
            AssertReturnIf(HasComponent<T>(), false);
            m_Registry->emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
            return true;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        [[nodiscard]] std::optional<std::reference_wrapper<T>> GetComponent() {
            ReturnUnless(HasComponent<T>(), {});
            return {std::reference_wrapper<T>(m_Registry->get<T>(m_EntityHandle))};
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        [[nodiscard]] bool HasComponent() const {
            return m_Registry->has<T>(m_EntityHandle);
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        [[nodiscard]] bool RemoveComponent() {
            AssertReturnUnless(HasComponent<T>(), false);
            m_Registry->remove<T>(m_EntityHandle);
            return true;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        operator void *() { return m_EntityHandle == entt::null ? nullptr : this; }

        /////////////////////////////////////////////////////////////////////////////////////////
        operator bool() const { return m_EntityHandle != entt::null; }

        /////////////////////////////////////////////////////////////////////////////////////////
        explicit operator unsigned() const { return (unsigned) m_EntityHandle; }

        /////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(const Entity &other) const {
            return m_EntityHandle == other.m_EntityHandle;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        bool operator!=(const Entity &other) const {
            return !(*this == other);
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        Entity &operator=(const Entity &copy) noexcept = default;

        /////////////////////////////////////////////////////////////////////////////////////////
        Entity &operator=(Entity &&copy) noexcept {
            m_Registry = copy.m_Registry;
            m_EntityHandle = std::move(copy).m_EntityHandle;
            return *this;
        }

    private:
        entt::entity m_EntityHandle{entt::null};
        entt::registry *m_Registry;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////