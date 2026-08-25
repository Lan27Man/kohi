#!/bin/bash

echo "Compiling shaders..."

$VULKAN_SDK/bin/glslc -fshader-stage=vert assets/shaders/BuiltIn.MaterialShader.vert.glsl -o assets/shaders/BuiltIn.MaterialShader.vert.spv

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

$VULKAN_SDK/bin/glslc -fshader-stage=frag assets/shaders/BuiltIn.MaterialShader.frag.glsl -o assets/shaders/BuiltIn.MaterialShader.frag.spv

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

echo "Done."
