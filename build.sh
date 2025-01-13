#!/bin/bash

BUILD_DIR="build"

# Check if the build directory exists
if [ -d "$BUILD_DIR" ]; then
  echo "$BUILD_DIR already exists. Removing it"
  rm -r "$BUILD_DIR"
else
  echo "$BUILD_DIR does not exist."
fi

# Create the build directory
mkdir "$BUILD_DIR"
echo "Directory $BUILD_DIR created."

# Compile the program
clang++ src/main.cpp \
        -Iext/glad/include \
        -Iext/glfw/include \
        -o build/out

# Run the compiled program
./build/out
