# Nymphaea
(repo under construction!)

A C Library for creating C applications.

## How to use?
to use this library in your project you have two options: pre-compile the whole library or use it as is.

#### Use as is:
This requieres you to use premake in your project.
Simply copy the whole repository to your 'dependencies/build' folder in your project and include the 'nymphaea.lua' file in your premake worlspace.
You will also have to link the library by adding "nymphaea" to your links {}.
Then you will need to run 'build.bat' and type gen_include and a include directory will appear.
You will need to include this directory in your included files of the project.
You will also need to include the include files of this library dependencies (will automate this later)
And thats it!

#### Use pre-compiled:
run 'build.bat' type 'compile'.
- this will compile the library into 'nymphaea.lib' file found in the newly generated 'bin' folder.
then type 'gen_include' also in 'build.bat'.
- this will create an include directory that you can paste in your included files folder of your project.

