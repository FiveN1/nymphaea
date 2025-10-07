This folder contains all of the dependencies of Nymphaea.

The libraries are split into 2 types (pre-compiled & not pre-compiled)


PRE-COMPILED (include, lib)

The pre-compiled libraries sources are in the 'lib' folder, containing the .lib files.
And the headers are in the 'include' folder.

NOT PRE-COMPILED (build)

The not pre-compiled libraries are in the 'buld' folder.
They are built by premake.
each library has its own 'premake5.lua' file wich is used for the building of the library.


