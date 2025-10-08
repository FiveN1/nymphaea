# Nymphaea
(repo under construction!)

A C Library for creating C applications.

## How to use?
to use this library in your project you have two options: pre-compile the whole library or use it as is.

#### Use as linked library:
> [!NOTE]
> This requieres you to use premake in your project.

Simply include the `nymphaea.lua` in your premake5.lua file and link it by adding `"nymphaea"` to your `links {}`
To use the headers of this library you will need to run `build.bat` and type `gen_include` to create the `include/` directory that you will need to include in your project.
You will also need to include the include files of this library dependencies (will automate this later)

#### Use as compiled library:
run `build.bat` and type `compile`.
- this will compile the library into `nymphaea.lib` file found in the newly generated `bin/` folder.
then type 'gen_include' also in 'build.bat'.
- this will create an include directory that you can paste in your included files folder of your project.

