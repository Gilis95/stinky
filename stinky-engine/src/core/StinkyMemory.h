//
// Created by christian on 19.11.20 г..
//

#pragma once

#ifdef STINKY_MEMORY_DEBUG
#include <iostream>
#endif
#include <memory>

namespace stinky {
    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args &&... args) {
#ifdef STINKY_MEMORY_DEBUG
        std::cout<<"Unique pointer creation: "<<__builtin_FUNCTION()<<std::endl;
#endif
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args &&... args) {
#ifdef STINKY_MEMORY_DEBUG
        std::cout<<"Shared pointer creation: "<<__builtin_FUNCTION()<<std::endl;
#endif
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

