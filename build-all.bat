@ECHO OFF
REM Build Everything

ECHO "Building Everything..."

REM Engine
make -f "engine/Makefile.engine.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

REM Testbed
make -f "testbed/Makefile.testbed.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

REM Unit Tests
make -f "tests/Makefile.tests.windows.mak" all
IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "All assemblies built successfully."

@REM ECHO "Post Build Tasks"

@REM CALL "post-build.bat"

@REM ECHO "Post Build Tasks completed successfully."
