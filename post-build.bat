@ECHO OFF

ECHO "Compiling shaders..."

%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/BuiltIn.MaterialShader.vert.glsl -o assets/shaders/BuiltIn.MaterialShader.vert.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/BuiltIn.MaterialShader.frag.glsl -o assets/shaders/BuiltIn.MaterialShader.frag.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

%VULKAN_SDK%\bin\glslc.exe -fshader-stage=vert assets/shaders/BuiltIn.UIShader.vert.glsl -o assets/shaders/BuiltIn.UIShader.vert.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

%VULKAN_SDK%\bin\glslc.exe -fshader-stage=frag assets/shaders/BuiltIn.UIShader.frag.glsl -o assets/shaders/BuiltIn.UIShader.frag.spv

IF %ERRORLEVEL% NEQ 0 (
    ECHO Error: %ERRORLEVEL% && EXIT
)

ECHO "Done."
