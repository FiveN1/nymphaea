
workspace "3D_demo"
    architecture "x86_64"
	startproject "3D_demo"

    configurations {
        "Debug",
        "Release"
    }

    flags {
		"MultiProcessorCompile"
	}
	buildoptions {
		--"-std=c99"
		--"-Wall",
		--"-Werror"
	}

output_directory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

nymphaea_directory = "../../"; -- coud be better.

project "3D_demo"
	kind "ConsoleApp"
	language "C"
	staticruntime "on"
	-- compile dir
    targetdir ("%{wks.location}/bin/" .. output_directory .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. output_directory .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.c"
	}
	
	includedirs {
		"src",
		-- Zahrnutí hlaviček (.h) nymphaea_lib
		nymphaea_directory .. "/src", -- zahrne pouze .h soubory
		nymphaea_directory .. "/dependencies/include" -- .h dalších knihoven
	}

	links {
		"nymphaea"
    }

	defines {
		--"GLFW_INCLUDE_NONE",
		--"NP_OPENGL_VERSION=4.6"
	}

	filter "system:windows"
		systemversion "latest"
		defines {
			--"NP_PLATFORM_WINDOWS" -- přidat aby premake vytvořil .h soubor se všemi definicemi pro kompatibilitu s vscode
		}
	filter "configurations:Debug" 
		defines "NP_DEBUG"
		symbols "on"
	filter "configurations:Release" 
		defines "NP_RELEASE"
		optimize "on"

include "../../nymphaea.lua"

-- Problém je ten že tady je třeba také zahrnovat všehcny hlavičky... (GLFW, atd...)
-- proto chci vytvořit program který vytvoří koppi s stejnými cestami ale pouze hlavičkové soubory.
-- bude to menší a stačí pouze zahrnout tu hlavní cestu?? (nebo ne?)
-- -- protože to není ta cesta.

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        print("Removing binaries")
        os.rmdir("./bin")
        print("Removing intermediate binaries")
        os.rmdir("./bin-int")
        print("Removing project files")
        os.rmdir("./.vs")
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done")
    end
}