@echo off

set library_name=nymphaea

:Done

echo Enter command to setup the %library_name% library
echo Enter 'help' to show list of commands
echo.

set /p user_input=

IF "%user_input%" == ""         GOTO PrintHelp
IF "%user_input%" == "help"     GOTO PrintHelp
IF "%user_input%" == "compile"  GOTO Compile
IF "%user_input%" == "gen_include"  GOTO GenerateInclude
IF "%user_input%" == "exit"     EXIT

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
echo   compile           Compiles the %library_name% library.
echo   gen_include       Copies all headers of the library into the include directory.
echo   clean             Removes binaries, includes and solution files.
echo   exit              Exit from this program.
echo.

GOTO Done

::
:: Compile
::

:Compile
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
:: Fetch headers
::

:GenerateInclude

set headers_output_directory=include\%library_name%

echo.
if not exist "%headers_output_directory%" mkdir %headers_output_directory%

xcopy "src\**.h" "%headers_output_directory%" /E

echo.
echo Fetched all headers to %headers_output_directory%
echo.

GOTO Done