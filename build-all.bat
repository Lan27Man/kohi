@ECHO OFF
REM Build Everything

ECHO "Building Everything..."

REM Engine
make -f "Makefile.engine.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

REM Testbed
make -f "Makefile.testbed.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "All assemblies built successfully."
