workspace "AlphaProject"
architecture "ARM64"

configurations {
    "Debug"
}

includeDir = {}
includeDir["GLFW"] = "vendor/GLFW/include"
includeDir["GLEW"] = "vendor/GLEW/include"
includeDir["ImGUI"] = "vendor/ImGUI"
includeDir["SHA256"] = "vendor/SHA256/include"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AlphaProject/vendor/GLFW"
include "AlphaProject/src/Core"
include "AlphaProject/src/Client"

project "Server"
location "AlphaProject/src/server"
kind "ConsoleApp"
language "C++"
cppdialect "C++latest"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

pchheader "AlphaProject/src/lib/appch.h"
pchsource "AlphaProject/src/lib/glpch.cpp"

files {
    "%{prj.location}/**.h",
    "%{prj.location}/**.cpp",
    "AlphaProject/vendor/ImGUI/*.h",
    "AlphaProject/vendor/ImGUI/*.cpp",
    "AlphaProject/vendor/ImGUI/backends/imgui_impl_glfw.h",
    "AlphaProject/vendor/ImGUI/backends/imgui_impl_glfw.cpp",
    "AlphaProject/vendor/ImGUI/backends/imgui_impl_opengl3.h",
    "AlphaProject/vendor/ImGUI/backends/imgui_impl_opengl3.cpp",
}

includedirs {
    "%{includeDir.GLFW}",
    "%{includeDir.GLEW}",
    "%{includeDir.ImGUI}",
    "%{includeDir.SHA256}",
    "AlphaProject/src"
}

links {
    "GLEW",
    "GLFW",
    "Cocoa.framework",
    "OpenGL.framework",
    "IOKit.framework"
}
