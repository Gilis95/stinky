//
// Created by christian on 19.12.20 г..
//
#include "core/StinkyMacros.h"
#include "core/ThreadUtils.h"
#include "core/Time.h"

#ifdef SK_PLATFORM_LINUX
#include <time.h>
#endif


namespace stinky {
    namespace this_thread {
#ifdef SK_PLATFORM_LINUX

        int sleep(const TimeFrame &requestedTime, TimeFrame &outRemainingTime) {
            return nanosleep(&requestedTime.m_Data, &outRemainingTime.m_Data);
        }

#elif SK_PLATFORM_ANDROID
        int sleep(const TimeFrame &requestedTime, TimeFrame &outRemainingTime){

        }
#elif SK_PLATFORM_MACOS
        int sleep(const TimeFrame &requestedTime, TimeFrame &outRemainingTime){

        }
#elif TARGET_OS_IPHONE
        int sleep(const TimeFrame &requestedTime, TimeFrame &outRemainingTime){

        }
#elif SK_PLATFORM_WINDOWS
        int sleep(const TimeFrame &requestedTime, TimeFrame &outRemainingTime){

        }
#endif
    }
}
