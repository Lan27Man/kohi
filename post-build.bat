@ECHO OFF

REM Run from root directory!
IF NOT EXIST "%cd%\bin\assets\shaders\" MKDIR "%cd%\bin\assets\shaders"

ECHO "Compiling shaders..."

ECHO "assets/shaders/BuiltIn.ObjectShader.vert.glsl -> bin/assets/shaders/BuiltIn.ObjectShader.vert.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/BuiltIn.ObjectShader.vert.glsl -o bin/assets/shaders/BuiltIn.ObjectShader.vert.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "assets/shaders/BuiltIn.ObjectShader.frag.glsl -> bin/assets/shaders/BuiltIn.ObjectShader.frag.spv"
%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/BuiltIn.ObjectShader.frag.glsl -o bin/assets/shaders/BuiltIn.ObjectShader.frag.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "Copying assets..."

ECHO xcopy "assets" "bin\assets" /h /i /c /k /e /r /y
xcopy "assets" "bin\assets" /h /i /c /k /e /r /y

ECHO "Done."
