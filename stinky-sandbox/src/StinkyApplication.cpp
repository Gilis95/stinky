#include "StinkyApplication.h"

namespace stinky {
    StinkyApplication::StinkyApplication() : Application() {
        PushLayer(new StinkyLayer());
    }

}