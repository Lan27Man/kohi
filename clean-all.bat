@ECHO OFF
REM Clean Everything

ECHO "Cleaning Everything..."

REM Engine
make -f "Makefile.engine.windows.mak" clean

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

REM Testbed
make -f "Makefile.testbed.windows.mak" clean

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "All assemblies cleaned successfully."
