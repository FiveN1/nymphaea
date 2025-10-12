
--
-- Nymphaea Library Project
--
-- premake5 project file
-- IMPORTANT: include only this file when linking with your premake project that uses this library!
--

project "nymphaea"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	-- compile dir
	targetdir ("%{wks.location}/bin/" .. output_directory .. "/%{prj.name}") -- output_directory variable expected!
	objdir ("%{wks.location}/bin-int/" .. output_directory .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.c"
	}
	-- pre-compiled header set
	pchheader "pch.h"
	pchsource "src/pch.c" -- pch přesunout do src?
	--
	includedirs {
		"src",
		"dependencies/include"
	}

	-- udelat neco jako podobnyho u includedirs kde mame pro kazdou knihovnu svuj vlastni dir ale pro lib
	libdirs {
		"dependencies/lib"
	}

	links {
		-- link projektů
        "GLFW",
        "Glad",	
		-- link knihoven (je to trochu divné ale jinak tyto soubory nebudou v compilované knihovně...)
		"GLFW.lib",
		"Glad.lib",
		-- debug verze freetype, release verze je v build/freetype/build/Release
		"msvcrt.lib", -- tohle není v lib/ !!
		"freetyped.lib",
		--
		"cglm.lib",
		-- assimp library and dependencies
		-- radši build
		"zlibstaticd.lib",
		"assimp-vc143-mtd.lib",
		--
        "opengl32.lib"
    }

	defines {
		"GLFW_INCLUDE_NONE",
		"NP_OPENGL_VERSION=4.6"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			"NP_PLATFORM_WINDOWS" -- přidat aby premake vytvořil .h soubor se všemi definicemi pro kompatibilitu s vscode
		}
	filter "configurations:Debug" 
		defines "NP_DEBUG"
		symbols "on"
	filter "configurations:Release" 
		defines "NP_RELEASE"
		optimize "on"

--
-- Dependencies
--

group "Dependencies"
	include "dependencies/build/GLFW"
    include "dependencies/build/Glad"
group ""
