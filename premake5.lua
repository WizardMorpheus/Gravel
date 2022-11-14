workspace "Gravel"
	architecture "x64"
	startproject "GBox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir  = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "Gravel/vendor/GLFW/include"

include "Gravel/vendor/GLFW"


project "Gravel"
	location "Gravel"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputDir .. "/%{prj.name}")


	pchheader "grvpch.h"
	pchsource "Gravel/src/grvpch.cpp"


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.location}/src",
		"%{prj.location}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"GRAVEL_PLATFORM_WINDOWS",
			"GRAVEL_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/GBox")
		}

	filter "configurations:Debug"
		defines "GRAVEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GRAVEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRAVEL_DIST"
		optimize "On"
		
project "Gbox"
	location "GravelBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.location}/src/**.h",
		"%{prj.location}/src/**.cpp"
	}

	includedirs
	{
		"Gravel/vendor/spdlog/include",
		"Gravel/src"
	}

	links 
	{
		"Gravel"
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"GRAVEL_PLATFORM_WINDOWS"
		}


	filter "configurations:Debug"
		defines "GRAVEL_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GRAVEL_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GRAVEL_DIST"
		optimize "On"