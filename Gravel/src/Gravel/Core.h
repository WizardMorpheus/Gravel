#pragma once
#include "grvpch.h"

/*
*	this file contains the precompiled headers and creates some important defines that allow the system to be cross platform.
*/


//	checks if the operating system is Windows. this define is generated by the premake file. 
#ifdef GRAVEL_PLATFORM_WINDOWS
	/*
	*	this ifdef checks if the core.h file is being accessed by the .dll or during runtime.
	*	this allows the files withing the Gravel project to be both compiled into a .dll 
	*	and then accessed by applications in .cpp form.
	*/
	#ifdef GRAVEL_BUILD_DLL
		#define GRAVEL_API __declspec(dllexport)
	#else
		#define GRAVEL_API __declspec(dllimport)
	#endif
#else
	#error GRAVEL only supprts windows!
#endif


//	enables asserts if needed for debugging etc.
#ifdef GRAVEL_ENABLE_ASSERTS
	#define GRAVEL_ASSERT(x, ...) {if (!(x)) {GRAVEL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbeak(); } }
	#define GRAVEL_CORE_ASSERT(x, ...) {if (!(x)) {GRAVEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbeak(); } }
#else
	#define GRAVEL_ASSERT(x, ...)
	#define GRAVEL_CORE_ASSERT(x, ...)
#endif 


//	definition of BIT() function. creates an integer with only one bit turned on, the bit is given as an integer parameter.
#define BIT(x) (1 << x)