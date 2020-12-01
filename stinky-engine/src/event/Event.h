#pragma once

#include <utility>

#include <ostream>

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
namespace stinky {
#define EVENT_CONSTRUCTOR(type) Event(#type)
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    class Event {
    public:
        Event(std::string name) :
                m_Name(std::move(name)) {}

        virtual ~Event() = default;

        [[nodiscard]] virtual std::string ToString() const { return m_Name; }

        std::string m_Name;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.m_Name;
    }
}

