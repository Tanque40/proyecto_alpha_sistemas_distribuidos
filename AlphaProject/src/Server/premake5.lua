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
}


includedirs {
	"src/",
	"../Lib/",
}

links {
	"pthread"
}


filter "configurations:Debug"
runtime "Debug"
symbols "On"
