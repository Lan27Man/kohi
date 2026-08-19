@ECHO OFF

REM Run from root directory!
IF NOT EXIST "%cd%\bin\assets\shaders\" MKDIR "%cd%\bin\assets\shaders"

ECHO "Compiling shaders..."

%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/BuiltIn.MaterialShader.vert.glsl -o bin/assets/shaders/BuiltIn.MaterialShader.vert.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/BuiltIn.MaterialShader.frag.glsl -o bin/assets/shaders/BuiltIn.MaterialShader.frag.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "Copying assets..."

xcopy "assets" "bin\assets" /h /i /c /k /e /r /y /d

ECHO "Done."
