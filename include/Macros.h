//
// Created by christian on 5/3/20.
//

#ifndef ENGINE_MACROS_H
#define ENGINE_MACROS_H

// Platform detection using predefined macros
#ifdef _WIN32
/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define HZ_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define HZ_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define HZ_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
#define HZ_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
#define PLATFORM_LINUX
#else
/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

#ifdef DEBUG
#if defined(PLATFORM_WINDOWS)
#define DEBUGBREAK() __debugbreak()
#elif defined(PLATFORM_LINUX)
#include <signal.h>
#include <memory>

#define DEBUGBREAK() raise(SIGTRAP)
#else
#error "Platform doesn't support debugbreak yet!"
#endif
#define ENABLE_ASSERTS
#else
#define DEBUGBREAK()
#endif



template<typename T>
using Ref = std::shared_ptr<T>;

#endif //ENGINE_MACROS_H
