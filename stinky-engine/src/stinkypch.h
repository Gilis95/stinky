#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include <array>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "core/stinky_logger.h"
#include "core/stinky_macros.h"
#include "core/stinky_memory.h"

#ifdef SK_PLATFORM_WINDOWS
#include <Windows.h>
#endif