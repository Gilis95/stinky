#pragma once

#include <cstdint>
#include <optional>
#include <entt/entity/registry.hpp>
#include "core/stinky_macros.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
    class entity {
    public:
        explicit entity() : _M_registry(nullptr) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        explicit entity(entt::registry *registry) : _M_registry(registry), _M_entity_handle(registry->create()) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        explicit entity(entt::registry *registry, const entt::entity &entt) : _M_registry(registry),
                                                                              _M_entity_handle(entt) {
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        entity(const entity &other) = default;

        /////////////////////////////////////////////////////////////////////////////////////////
        entity(entity &&other) = default;

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename... Args>
        [[nodiscard]] bool AddComponent(Args &&... args) {
            AssertReturnIf(has_component<T>(), false);
            _M_registry->emplace<T>(_M_entity_handle, std::forward<Args>(args)...);
            return true;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        [[nodiscard]] std::optional<std::reference_wrapper<T>> get_component() {
            ReturnUnless(has_component<T>(), std::nullopt);
            return {std::reference_wrapper<T>(_M_registry->get<T>(_M_entity_handle))};
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        [[nodiscard]] bool has_component() const {
            return _M_registry->any_of<T>(_M_entity_handle);
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        template<typename T>
        [[nodiscard]] bool remove_component() {
            AssertReturnUnless(has_component<T>(), false);
            _M_registry->remove<T>(_M_entity_handle);
            return true;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        operator void *() { return _M_entity_handle == entt::null ? nullptr : this; }

        /////////////////////////////////////////////////////////////////////////////////////////
        operator bool() const { return _M_entity_handle != entt::null; }

        /////////////////////////////////////////////////////////////////////////////////////////
        explicit operator unsigned() const { return (unsigned) _M_entity_handle; }

        /////////////////////////////////////////////////////////////////////////////////////////
        bool operator==(const entity &other) const {
            return _M_entity_handle == other._M_entity_handle;
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        bool operator!=(const entity &other) const {
            return !(*this == other);
        }

        /////////////////////////////////////////////////////////////////////////////////////////
        entity &operator=(const entity &copy) noexcept = default;

        /////////////////////////////////////////////////////////////////////////////////////////
        entity &operator=(entity &&copy) noexcept {
            _M_registry = copy._M_registry;
            _M_entity_handle = std::move(copy)._M_entity_handle;
            return *this;
        }

    private:
        entt::entity _M_entity_handle{entt::null};
        entt::registry *_M_registry;
    };
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////