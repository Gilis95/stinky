//
// Created by christian on 23/08/2020.
//
#pragma once

#include <cstdint>

namespace stinky {
    typedef uint16_t key_code;
    namespace key {
        // From glfw3.h
        constexpr key_code space = 32;
        constexpr key_code apostrophe = 39; /* ' */
        constexpr key_code comma = 44; /* ; */
        constexpr key_code minus = 45; /* - */
        constexpr key_code period = 46; /* . */
        constexpr key_code slash = 47; /* / */

        constexpr key_code d0 = 48; /* 0 */
        constexpr key_code d1 = 49; /* 1 */
        constexpr key_code d2 = 50; /* 2 */
        constexpr key_code d3 = 51; /* 3 */
        constexpr key_code d4 = 52; /* 4 */
        constexpr key_code d5 = 53; /* 5 */
        constexpr key_code d6 = 54; /* 6 */
        constexpr key_code d7 = 55; /* 7 */
        constexpr key_code d8 = 56; /* 8 */
        constexpr key_code d9 = 57; /* 9 */

        constexpr key_code semicolon = 59; /* ; */
        constexpr key_code equal = 61; /* = */

        constexpr key_code a = 65;
        constexpr key_code b = 66;
        constexpr key_code c = 67;
        constexpr key_code d = 68;
        constexpr key_code e = 69;
        constexpr key_code f = 70;
        constexpr key_code g = 71;
        constexpr key_code h = 72;
        constexpr key_code i = 73;
        constexpr key_code j = 74;
        constexpr key_code k = 75;
        constexpr key_code l = 76;
        constexpr key_code m = 77;
        constexpr key_code n = 78;
        constexpr key_code o = 79;
        constexpr key_code p = 80;
        constexpr key_code q = 81;
        constexpr key_code r = 82;
        constexpr key_code s = 83;
        constexpr key_code t = 84;
        constexpr key_code u = 85;
        constexpr key_code v = 86;
        constexpr key_code w = 87;
        constexpr key_code x = 88;
        constexpr key_code y = 89;
        constexpr key_code z = 90;

        constexpr key_code left_bracket = 91;  /* [ */
        constexpr key_code backslash = 92;  /* \ */
        constexpr key_code right_bracket = 93;  /* ] */
        constexpr key_code grave_accent = 96;  /* ` */

        constexpr key_code world1 = 161; /* non-US #1 */
        constexpr key_code world2 = 162; /* non-US #2 */

        /* Function constexpr KeyCodes */
        constexpr key_code escape = 256;
        constexpr key_code enter = 257;
        constexpr key_code tab = 258;
        constexpr key_code backspace = 259;
        constexpr key_code insert = 260;
        constexpr key_code delete_key = 261;
        constexpr key_code right = 262;
        constexpr key_code left = 263;
        constexpr key_code down = 264;
        constexpr key_code up = 265;
        constexpr key_code page_up = 266;
        constexpr key_code page_down = 267;
        constexpr key_code home = 268;
        constexpr key_code end = 269;
        constexpr key_code caps_lock = 280;
        constexpr key_code scroll_lock = 281;
        constexpr key_code num_lock = 282;
        constexpr key_code print_screen = 283;
        constexpr key_code pause = 284;
        constexpr key_code f1 = 290;
        constexpr key_code f2 = 291;
        constexpr key_code f3 = 292;
        constexpr key_code f4 = 293;
        constexpr key_code f5 = 294;
        constexpr key_code f6 = 295;
        constexpr key_code f7 = 296;
        constexpr key_code f8 = 297;
        constexpr key_code f9 = 298;
        constexpr key_code f10 = 299;
        constexpr key_code f11 = 300;
        constexpr key_code f12 = 301;
        constexpr key_code f13 = 302;
        constexpr key_code f14 = 303;
        constexpr key_code f15 = 304;
        constexpr key_code f16 = 305;
        constexpr key_code f17 = 306;
        constexpr key_code f18 = 307;
        constexpr key_code f19 = 308;
        constexpr key_code f20 = 309;
        constexpr key_code f21 = 310;
        constexpr key_code f22 = 311;
        constexpr key_code f23 = 312;
        constexpr key_code f24 = 313;
        constexpr key_code f25 = 314;

        /* constexpr KeyCodepad */
        constexpr key_code kp0 = 320;
        constexpr key_code kp1 = 321;
        constexpr key_code kp2 = 322;
        constexpr key_code kp3 = 323;
        constexpr key_code kp4 = 324;
        constexpr key_code kp5 = 325;
        constexpr key_code kp6 = 326;
        constexpr key_code kp7 = 327;
        constexpr key_code kp8 = 328;
        constexpr key_code kp9 = 329;
        constexpr key_code kp_decimal = 330;
        constexpr key_code kp_divide = 331;
        constexpr key_code kp_multiply = 332;
        constexpr key_code kp_subtract = 333;
        constexpr key_code kp_add = 334;
        constexpr key_code kp_enter = 335;
        constexpr key_code kp_equal = 336;

        constexpr key_code left_shift = 340;
        constexpr key_code left_control = 341;
        constexpr key_code left_alt = 342;
        constexpr key_code left_super = 343;
        constexpr key_code right_shift = 344;
        constexpr key_code right_control = 345;
        constexpr key_code right_alt = 346;
        constexpr key_code right_super = 347;
        constexpr key_code menu = 348;
    }
}
