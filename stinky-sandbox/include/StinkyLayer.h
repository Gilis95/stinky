#pragma once

#include "event/Layer.h"

namespace stinky {
    class StinkyLayer : public Layer
    {
        StinkyLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Timestep ts) override;
    };

}