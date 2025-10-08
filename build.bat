@echo off

set library_name=nymphaea

:Done

echo Enter command to setup the %library_name% library
echo Enter 'help' to show list of commands
echo.

set /p user_input=

IF "%user_input%" == ""             GOTO PrintHelp
IF "%user_input%" == "help"         GOTO PrintHelp
IF "%user_input%" == "compile_d"    GOTO CompileDebug
IF "%user_input%" == "compile"      GOTO CompileDebug
IF "%user_input%" == "compile_r"    GOTO CompileRelease
IF "%user_input%" == "include"      GOTO GenerateInclude
IF "%user_input%" == "exit"         EXIT

::
:: PREMAKE COMMANDS
::

echo.
premake\premake5.exe "%user_input%"
echo.
GOTO Done

::
:: HELP
::

:PrintHelp

echo.
echo Enter 'build.bat action' where action is one of the following:
echo.
echo   compile_d/compile Compiles the %library_name% library in a Debug confoguration using vs2022 solution.
echo   compile_r         Compiles the %library_name% library in a Release confoguration using vs2022 solution.
echo   include           Creates an include directory for use in your projects.
echo   clean             Removes binaries, includes and solution files.
echo   exit              Exit from this program.
echo.
echo Premake commands:
echo.
:: premake commands
echo   codelite          Generate CodeLite project files
echo   gmake             Generate GNU makefiles for Linux
echo   vs2005            Generate Visual Studio 2005 project files
echo   vs2008            Generate Visual Studio 2008 project files
echo   vs2010            Generate Visual Studio 2010 project files
echo   vs2012            Generate Visual Studio 2012 project files
echo   vs2013            Generate Visual Studio 2013 project files
echo   vs2015            Generate Visual Studio 2015 project files
echo   vs2017            Generate Visual Studio 2017 project files
echo   vs2019            Generate Visual Studio 2019 project files
echo   vs2022            Generate Visual Studio 2022 project files
echo   xcode4            Generate Apple Xcode 4 project files
echo.
echo NOTE: this batch file will run any premake command.
echo.

GOTO Done

::
:: Generate include
::

:GenerateInclude

set headers_output_directory=include\

echo.
if not exist "%headers_output_directory%" mkdir %headers_output_directory%
:: copy nymphaea header files
:: NOTE: pch.h will also be copied (REMOVE THIS!)
xcopy "src\**.h" "%headers_output_directory%" /E
:: copy nymphaea dependencies
xcopy "dependencies\include\**.*" "%headers_output_directory%" /E

echo.
echo Fetched all headers to %headers_output_directory%
echo.

GOTO Done

::
:: Compile Debug
::

:CompileDebug
echo.

premake\premake5.exe vs2022

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
)

set solutionFile="%library_name%.sln"
msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%

echo.

GOTO Done

::
:: Compile Release
::

:CompileRelease
echo.

premake\premake5.exe vs2022

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
)

set solutionFile="%library_name%.sln"
msbuild /t:Build /p:Configuration=Release /p:Platform=x64 %solutionFile%

echo.

GOTO Done