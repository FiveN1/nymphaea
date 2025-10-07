
--
-- Nymphaea Library Workspace
--

workspace "nymphaea"
    architecture "x86_64"
	startproject "nymphaea"

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

--
-- nymphaea library project
--

include "nymphaea.lua"

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
        print("Removing include directory")
        os.rmdir("./include")
        print("Done")
    end
}