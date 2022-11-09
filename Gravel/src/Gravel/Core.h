#pragma once


#ifdef GRAVEL_PLATFORM_WINDOWS
	#ifdef GRAVEL_BUILD_DLL
		#define GRAVEL_API __declspec(dllexport)
	#else
		#define GRAVEL_API __declspec(dllimport)
	#endif
#else
	#error GRAVEL only supprts windows!
#endif

#define BIT(x) (1 << x)