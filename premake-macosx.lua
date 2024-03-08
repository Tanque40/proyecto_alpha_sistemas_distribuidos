workspace "AlphaProject"
architecture "ARM64"

configurations {
	"Debug"
}

flags {
	"MultiProcessorCompile"
}

includeDir = {}
includeDir["GLFW"] = "vendor/GLFW/include"
includeDir["GLEW"] = "vendor/GLEW/include"
includeDir["ImGUI"] = "vendor/ImGUI"
includeDir["SHA256"] = "vendor/SHA256/include"
includeDir["glm"] = "vendor/glm"
includeDir["stb_image"] = "vendor/stb_image"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AlphaProject/vendor/GLFW"
include "AlphaProject/src/Core"
include "AlphaProject/src/Client"
include "AlphaProject/src/Server"
