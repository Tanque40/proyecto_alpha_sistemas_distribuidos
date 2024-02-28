workspace "AlphaProject"
architecture "ARM64"

configurations {
    "Debug"
}

includeDir = {}
includeDir["GLFW"] = "AlphaProject/vendor/GLFW/include"
includeDir["GLEW"] = "AlphaProject/vendor/GLEW/include"
includeDir["ImGUI"] = "AlphaProject/vendor/ImGUI"
includeDir["SHA256"] = "AlphaProject/vendor/SHA256/include"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AlphaProject/vendor/GLFW"

project "Server"
location "AlphaProject/src/server"
kind "ConsoleApp"
language "C++"
cppdialect "C++latest"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
    "%{prj.location}/**.h",
    "%{prj.location}/**.cpp",
}

includedirs {
    "%{includeDir.GLFW}",
    "%{includeDir.GLEW}",
    "%{includeDir.ImGUI}",
    "%{includeDir.SHA256}",
    "AlphaProject/src"
}

project "Client"
location "AlphaProject/src/client"
kind "ConsoleApp"
language "C++"
cppdialect "C++latest"
staticruntime "on"

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files {
    "%{prj.location}/**.h",
    "%{prj.location}/**.cpp",
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

filter "configurations:Debug"
runtime "Debug"
symbols "On"
