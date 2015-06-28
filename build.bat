@echo off

set PROJ_DIR=%~dp0
set MSVC_VER=%1
set MSVC_GEN=""

if "%MSVC_VER%"=="12.0" (
	set MSVC_GEN="Visual Studio 12 2013"
)
if "%MSVC_VER%"=="14.0" (
	set MSVC_GEN="Visual Studio 14 2015"
)
if %MSVC_GEN%=="" (
	echo ERROR: Unsupported Visual Studio version
	exit /b 1
)

if "%ProgramFiles(x86)%"=="" (
	set MSVC_DIR="%ProgramFiles%\Microsoft Visual Studio %MSVC_VER%\VC\"
	set MSVC_VARS="%ProgramFiles%\Microsoft Visual Studio %MSVC_VER%\VC\vcvarsall.bat"
) ELSE (
	set MSVC_DIR="%ProgramFiles(x86)%\Microsoft Visual Studio %MSVC_VER%\VC\"
	set MSVC_VARS="%ProgramFiles(x86)%\Microsoft Visual Studio %MSVC_VER%\VC\vcvarsall.bat"
)

if not exist %MSVC_VARS% (
	echo ERROR: Could not find specified version of Visual Studio
	exit /b 1
)

call %MSVC_VARS%

if not exist "projects" (
	mkdir projects
)

cmake -G %MSVC_GEN% -Bprojects -H.

if not exist ./projects/minigui.sln (
	echo ERROR: Project files hasn't been generated.
	exit /b 1
)

msbuild /t:Clean,Rebuild /verbosity:m "projects/minigui.sln" 
exit /b 0