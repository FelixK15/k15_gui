@echo off
echo Searching for Visual Studio installation...
setlocal enableextensions enabledelayedexpansion

set FOUND_PATH=0
set VS_PATH=
::check whether this is 64bit windows or not
reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set OS=32BIT || set OS=64BIT

IF %OS%==64BIT set REG_FOLDER=HKLM\SOFTWARE\WOW6432Node\Microsoft\VisualStudio\
IF %OS%==32BIT set REG_FOLDER=HKLM\SOFTWARE\Microsoft\VisualStudio\

::Go to end if nothing was found
IF %REG_FOLDER%=="" GOTO DECISION

::try to get get visual studio path from registry for different versions
FOR /l %%G IN (10, 1, 14) DO (
	set REG_PATH=%REG_FOLDER%%%G.0
	set REG_COMMAND=reg query !REG_PATH! /v InstallDir

	!REG_COMMAND! >nul 2>nul

	::if errorlevel is 0, we found a valid installDir
	if !errorlevel! == 0 (
		::issue reg command again but evaluate output
		FOR /F "tokens=3" %%V IN ('!REG_COMMAND!') DO (
			set VS_PATH=%%V
			set FOUND_PATH=1
			goto DECISION
		)
	)
)

:DECISION
::check if a path was found
IF !FOUND_PATH!==0 (
	echo Could not find valid Visual Studio installation.
) ELSE (
	echo Starting build process...
	set CL_PATH=!VS_PATH!..\..\VC\bin\cl.exe
	set CL_OPTIONS=/Od /TP
	set BUILD_COMMAND=!CL_PATH! example.c %CL_OPTIONS%
	call !BUILD_COMMAND!
) 