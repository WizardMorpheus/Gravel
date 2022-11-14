#pragma once
#include "grvpch.h"


#ifdef GRAVEL_PLATFORM_WINDOWS
	#ifdef GRAVEL_BUILD_DLL
		#define GRAVEL_API __declspec(dllexport)
	#else
		#define GRAVEL_API __declspec(dllimport)
	#endif
#else
	#error GRAVEL only supprts windows!
#endif


#ifdef GRAVEL_ENABLE_ASSERTS
	#define GRAVEL_ASSERT(x, ...) {if (!(x)) {GRAVEL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbeak(); } }
	#define GRAVEL_CORE_ASSERT(x, ...) {if (!(x)) {GRAVEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbeak(); } }
#else
	#define GRAVEL_ASSERT(x, ...)
	#define GRAVEL_CORE_ASSERT(x, ...)
#endif // GRAVEL_ENABLE_ASSERTS


#define BIT(x) (1 << x)