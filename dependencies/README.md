# Dependencies 
This folder contains all of Nymphaea dependencies.

## 📁 Build
This folder contains libraries that are compiled with nymphaea.

Premake is used as allways.
Each library has it's own premake5.lua file.

I would like to gradually move the pre-built libraries in here since it would be easier to build to diffrent platforms.

## 📁 Lib
This folder contains the pre-built library files, usually compiled with CMake.

## 📁 Include
This folder contains all of the library's headers.

This folder is added to the generated `include/` directory with the nymphaea heesders.


