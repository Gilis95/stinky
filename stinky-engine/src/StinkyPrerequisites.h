//
// Created by christian on 04/10/2020.
//

#pragma once

#include "core/stinky_logger.h"
#include "core/stinky_macros.h"
#include "core/stinky_memory.h"

namespace stinky {
    /** ################################ Graphic Layer Abstraction Classes ####################################### */
    class cube_texture;

    class frame_buffer;

    struct frame_buffer_specification;

    class graphic_layer_abstraction_factory;

    class index_buffer;

    class shader;

    class texture;

    class vertex_array;

    class vertex_buffer;

    class BufferLayout;

    class renderer_api;
    /** ################################ Graphic Layer Abstraction Classes ####################################### */

    /** ################################ Entity Component Classes ################################################ */
    class mesh_component;

    class transform_component;

    class material_component;

    class program_component;
    /** ################################ Entity Component Classes ################################################ */

    /** ################################ Cameras ################################################################# */
    class fps_camera;

    class orthographic_camera;

    class track_ball_camera;
    /** ################################ Cameras ################################################################# */

    /** ################################ Events ################################################################# */
    class app_tick_event;

    class app_update_event;

    class app_render_event;

    class key_pressed_event;

    class key_released_event;

    class key_typed_event;

    class mouse_moved_event;

    class mouse_scrolled_event;

    class mouse_button_pressed_event;

    class mouse_button_released_event;

    class time_frame;

    class window_resize_event;

    class window_close_event;
    /** ################################ Events ################################################################# */

    /** ################################ Window ################################################################# */
    class window;
    /** ################################ Window ################################################################# */

    namespace this_thread {
        extern int sleep(const time_frame &requestedTime, time_frame &outRemainingTime);
    }
}