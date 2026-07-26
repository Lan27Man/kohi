@ECHO OFF
REM Clean Everything

ECHO "Cleaning Everything..."

REM Engine
make -f "engine/Makefile.engine.windows.mak" clean

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

REM Testbed
make -f "testbed/Makefile.testbed.windows.mak" clean

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

REM Unit Tests
make -f "tests/Makefile.tests.windows.mak" clean

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "All assemblies cleaned successfully."
