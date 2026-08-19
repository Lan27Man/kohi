#!/bin/bash

# Run from root directory!
mkdir -p /bin/assets
mkdir -p /bin/assets/shaders

echo "Compiling shaders..."

$VULKAN_SDK/bin/glslc -fshader-stage=vert assets/shaders/BuiltIn.MaterialShader.vert.glsl -o bin/assets/shaders/BuiltIn.MaterialShader.vert.spv

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

$VULKAN_SDK/bin/glslc -fshader-stage=frag assets/shaders/BuiltIn.MaterialShader.frag.glsl -o bin/assets/shaders/BuiltIn.MaterialShader.frag.spv

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

echo "Copying assets..."

echo cp -R "assets" "bin"
cp -R "assets" "bin"

echo "Done."
