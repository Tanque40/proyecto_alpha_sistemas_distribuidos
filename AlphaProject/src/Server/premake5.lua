project "Server-AlphaProject"
kind "ConsoleApp"
language "C++"
cppdialect "C++latest"
staticruntime "on"

targetdir("../../../bin/" .. outputdir .. "/%{prj.name}")
objdir("../../../bin-int/" .. outputdir .. "/%{prj.name}")

files {
	"src/**.h",
	"src/**.cpp",
	"../Assets/**.*",
}

includedirs {
	"src/",
	"../Core/src",
	"../../%{includeDir.GLFW}",
	"../../%{includeDir.GLEW}",
	"../../%{includeDir.ImGUI}",
	"../../%{includeDir.stb_image}"
}

links {
	"Core-AlphaProject",
	"GLFW",
	"GLEw",
	"Cocoa.framework",
	"OpenGL.framework",
	"IOKit.framework",
}

filter "configurations:Debug"
runtime "Debug"
symbols "On"
