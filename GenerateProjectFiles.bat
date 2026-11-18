@echo off
setlocal EnableExtensions DisableDelayedExpansion

rem Use the project next to this script. Set UE_ROOT to override its engine association.
pushd "%~dp0" || exit /b 1

set "PROJECT_FILE="
for %%F in (*.uproject) do (
    if exist "%%~fF" if not exist "%%~fF\" (
        if defined PROJECT_FILE (
            echo [Error] More than one .uproject file was found next to this script.
            goto :fail
        )
        set "PROJECT_FILE=%%~fF"
    )
)

if not defined PROJECT_FILE (
    echo [Error] No .uproject file was found next to this script.
    goto :fail
)

echo Project: "%PROJECT_FILE%"
if defined UE_ROOT goto :use_engine_override

rem Use the same registered command as Generate Visual Studio project files in Explorer.
powershell.exe -NoProfile -NonInteractive -Command ^
    "try { $generator = Start-Process -FilePath $env:PROJECT_FILE -Verb rungenproj -WindowStyle Hidden -Wait -PassThru -ErrorAction Stop; if ($null -eq $generator) { throw 'No generator process was returned.' }; exit $generator.ExitCode } catch { Write-Error $_; exit 1 }"
if not "%ERRORLEVEL%"=="0" (
    echo         Check the Unreal Engine association or set UE_ROOT to the engine install folder.
    goto :fail
)
goto :success

:use_engine_override
set "BUILD_BAT=%UE_ROOT%\Engine\Build\BatchFiles\Build.bat"
if not exist "%BUILD_BAT%" (
    echo [Error] Unreal Engine not found: "%BUILD_BAT%"
    echo         Set UE_ROOT to your engine install folder and try again.
    goto :fail
)

echo Engine : "%UE_ROOT%"
call "%BUILD_BAT%" -projectfiles -project="%PROJECT_FILE%" -game -rocket -progress
if not "%ERRORLEVEL%"=="0" goto :fail

:success
echo Project files generated successfully.
popd
exit /b 0

:fail
echo Failed to generate project files.
popd
exit /b 1
