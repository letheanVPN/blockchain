call utils\build\extras\win\configure_local_paths.cmd

;; MSVC version-specific paths
SET LOCAL_BOOST_LIB_PATH=%LOCAL_BOOST_PATH%\lib64-msvc-14.2
SET QT_MSVC_PATH=%QT_PREFIX_PATH%

SET ACHIVE_NAME_PREFIX=lethean-gui-bundle-win-testnet-x64
SET MY_PATH=%~dp0
SET SOURCES_PATH=%MY_PATH:~0,-13%

SET TESTNET_DEF=-D TESTNET=TRUE
SET TESTNET_LABEL=testnet


SET PARAM=%~1
IF "%PARAM%"=="--skip-build" ( GOTO skip_build )

@echo on

set BOOST_ROOT=%LOCAL_BOOST_PATH%
set BOOST_LIBRARYDIR=%LOCAL_BOOST_LIB_PATH%

@echo "---------------- PREPARING BINARIES ---------------------------"
@echo "---------------------------------------------------------------"

cd %SOURCES_PATH%
set HUNTER_ROOT=%HOMEPATH%\.hunter
@echo "---------------- BUILDING APPLICATIONS ------------------------"
@echo "---------------------------------------------------------------"




rmdir build /s /q
mkdir build
cd build
cmake %TESTNET_DEF% -D OPENSSL_ROOT_DIR="%OPENSSL_ROOT_DIR%"  -DCMAKE_CONFIGURATION_TYPES:STRING="Release" -D CMAKE_PREFIX_PATH="%QT_MSVC_PATH%" -D BUILD_GUI=TRUE -D STATIC=FALSE -G "Visual Studio 17 2022" -T host=x64 ..
IF %ERRORLEVEL% NEQ 0 (
  goto error
)

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" x86_amd64
)
echo on
cd %SOURCES_PATH%\build

msbuild version.vcxproj /p:SubSystem="CONSOLE,5.02"  /p:Configuration=Release /t:Build
IF %ERRORLEVEL% NEQ 0 (
  goto error
)

msbuild src/Lethean.vcxproj /p:SubSystem="WINDOWS,5.02" /p:Configuration=Release /t:Build

IF %ERRORLEVEL% NEQ 0 (
  goto error
)


@echo on
echo "sources are built successfully"


:skip_build
cd %SOURCES_PATH%/build

set build_zip_filename=%ACHIVE_NAME_PREFIX%.zip
set build_zip_path=%SOURCES_PATH%\%build_zip_filename%

del /F /Q %build_zip_path%

cd src\release



@echo on


mkdir bunch

copy /Y lethean-gui-server.exe bunch
copy /Y *.pdb bunch

copy /Y "%OPENSSL_ROOT_DIR%\bin\libcrypto-1_1-x64.dll" bunch
copy /Y "%OPENSSL_ROOT_DIR%\bin\libssl-1_1-x64.dll" bunch

windeployqt.exe bunch\lethean-gui-server.exe

cd bunch

zip -r %build_zip_path% *
IF %ERRORLEVEL% NEQ 0 (
  goto error
)


cd %SOURCES_PATH%\build
IF %ERRORLEVEL% NEQ 0 (
  goto error
)

@echo "---------------------------------------------------------------"
@echo "---------------------------------------------------------------"

goto success

:error
echo "BUILD FAILED"
exit /B %ERRORLEVEL%

:success
echo "BUILD SUCCESS"

cd ..

EXIT /B %ERRORLEVEL%


:: functions

:sha256
@setlocal enabledelayedexpansion
@set /a count=1
@for /f "skip=1 delims=:" %%a in ('CertUtil -hashfile %1 SHA256') do @(
  @if !count! equ 1 set "hash=%%a"
  @set /a count+=1
)
@(
 @endlocal
 @set "%2=%hash: =%
)
@exit /B 0
