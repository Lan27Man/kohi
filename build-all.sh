#!/bin/bash
# Build script for rebuilding everything.
set echo on

echo "Building Everything..."

make -f engine/Makefile.engine.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

make -f testbed/Makefile.testbed.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

make -f tests/Makefile.tests.linux.mak all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

echo "All assemblies built successfully."

echo "Post Build tasks"

source post-build.sh

echo "Post Build Tasks completed successfully."
