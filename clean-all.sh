#!/bin/bash
# Build script for cleaning everything.
set echo on

echo "Cleaning Everything..."

make -f engine/Makefile.engine.linux.mak clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

make -f testbed/Makefile.testbed.linux.mak clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

make -f tests/Makefile.tests.linux.mak clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
echo "Error: " $ERRORLEVEL && exit
fi

echo "All assemblies cleaned successfully."
