#pragma once

#include "StinkyPrerequisites.h"

namespace stinky {
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Layer {
    public:
        explicit Layer(std::string name = "Layer");

        virtual ~Layer() = default;

        virtual void OnAttach() {}

        virtual void OnDetach() {}

        virtual void OnUpdate(const TimeFrame &ts) {}

        [[nodiscard]] const std::string &GetName() const { return m_DebugName; }

    protected:
        const std::string m_DebugName;
    };
}