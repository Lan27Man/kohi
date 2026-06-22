@ECHO OFF
REM Build Everything.

ECHO "Building everything..."

IF NOT EXIST bin\ MKDIR bin

PUSHD engine
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && exit
)

PUSHD testbed
CALL build.bat
POPD
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && exit
)

ECHO "All assemblies built successfully."
