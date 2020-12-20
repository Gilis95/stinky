//
// Created by christian on 19.12.20 г..
//

#pragma once
#include "StinkyPrerequisites.h"

namespace stinky{
    namespace this_thread{
        /**
         * @param requestedTime - time thread should be asleep
         * @param outRemainingTime - in case sleep is interrupted, remaining time will be written to this variable
         */
        [[nodiscard]] int sleep(const TimeFrame& requestedTime, TimeFrame& outRemainingTime);
    }

}
