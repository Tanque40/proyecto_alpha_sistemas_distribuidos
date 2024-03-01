project "Core-AlphaProject"
kind "StaticLib"
language "C++"
cppdialect "C++latest"
staticruntime "on"

targetdir("../../../bin/" .. outputdir .. "/%{prj.name}")
objdir("../../../bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "appch.h"
pchsource "src/appch.cpp"

includedirs {
	"src/",
	"../../%{includeDir.GLFW}",
	"../../%{includeDir.GLEW}",
	"../../%{includeDir.ImGUI}",
	"../../%{includeDir.stb_image}"
}

files {
	"src/**.h",
	"src/**.cpp",
	"../../vendor/stb_image/**.h",
	"../../vendor/stb_image/**.cpp",
	"../../vendor/ImGUI/*.h",
	"../../vendor/ImGUI/*.cpp",
	"../../vendor/ImGUI/backends/imgui_impl_glfw.h",
	"../../vendor/ImGUI/backends/imgui_impl_glfw.cpp",
	"../../vendor/ImGUI/backends/imgui_impl_opengl3.h",
	"../../vendor/ImGUI/backends/imgui_impl_opengl3.cpp",
}

defines {
	"_CRT_SECURE_NO_WARNINGS",
	"GLFW_INCLUDE_NONE"
}

links {
	"GLFW",
	"GLEW",
	"Cocoa.framework",
	"OpenGL.framework",
	"IOKit.framework"
}

filter "configurations:Debug"
runtime "Debug"
symbols "on"
