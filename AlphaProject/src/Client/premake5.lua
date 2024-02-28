project "Client-AlphaProject"
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
    "../Core/src",
    "../../%{includeDir.GLFW}",
    "../../%{includeDir.GLEW}",
    "../../%{includeDir.ImGUI}",
    "../../%{includeDir.stb_image}"
}

links {
    "Core-AlphaProject",
}

filter "configurations:Debug"
runtime "Debug"
symbols "On"
