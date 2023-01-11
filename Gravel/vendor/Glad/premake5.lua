project "GLAD"
	kind "StaticLib"
	language "C"

	toolset "v143"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-intermediates/" .. outputDir .. "/%{prj.name}")

	files
    {
    "include/glad/glad.h",
    "include/KHR/khrplatform.h",
    "src/glad.c"
    }

    includedirs
    {
        "include"
    }

filter "system:linux"
    pic "On"

    systemversion "latest"
    staticruntime "On"


filter "system:windows"
    systemversion "latest"
    staticruntime "On"
    
   

filter "configurations:Debug"
    runtime "Debug"
    symbols "On"

filter "configurations:Release"
    runtime "Release"
    optimize "On"