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
IncludeDir["Glad"] = "Gravel/vendor/Glad/include"
IncludeDir["ImGui"] = "Gravel/vendor/imgui"

include "Gravel/vendor/GLFW"
include "Gravel/vendor/Glad"
include "Gravel/vendor/imgui"



project "Gravel"
	location "Gravel"
	kind "SharedLib"
	language "C++"

	toolset "v143"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines 
		{
			"GRAVEL_PLATFORM_WINDOWS",
			"GRAVEL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/GBox/\"")
		}

	filter "configurations:Debug"
		defines "GRAVEL_DEBUG"
		symbols "On"
		--sets to /MDd
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "GRAVEL_RELEASE"
		optimize "On"
		--sets to /MD
		staticruntime "off"
		runtime "Release"

	filter "configurations:Dist"
		defines "GRAVEL_DIST"
		optimize "On"
		--sets to /MD
		staticruntime "off"
		runtime "Release"
		
project "Gbox"
	location "GravelBox"
	kind "ConsoleApp"
	language "C++"

	toolset "v143"

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

		staticruntime "off"
		runtime "Debug"

	filter "configurations:Release"
		defines "GRAVEL_RELEASE"
		optimize "On"

		staticruntime "off"
		runtime "Release"

	filter "configurations:Dist"
		defines "GRAVEL_DIST"
		optimize "On"

		staticruntime "off"
		runtime "Release"