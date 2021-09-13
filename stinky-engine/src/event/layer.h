#pragma once

#include "StinkyPrerequisites.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class layer {
    public:
        explicit layer(std::string name = "Layer");

        virtual ~layer() = default;

        virtual void OnAttach() {}

        virtual void OnDetach() {}

        virtual void OnUpdate(const time_frame &ts) {}

        [[nodiscard]] const std::string &GetName() const { return m_DebugName; }

    protected:
        const std::string m_DebugName;
    };
}