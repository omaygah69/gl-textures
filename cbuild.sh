#!/bin/bash

# Compiler and flags
CXX=g++
CXXFLAGS="-Iglad -Iinclude"
LIBS="-lglfw -lGL -ldl -lpthread -lm -lX11"
SRC="main.cpp loadshader.cpp buffers.cpp glad.c stb.cpp"
OUT="build/main"

build() {
    mkdir -p build
    echo "[INFO] Building..."
    $CXX -o $OUT $SRC $CXXFLAGS $LIBS
    if [ $? -eq 0 ]; then
        echo "[SUCCESS] Build successful: $OUT"
    else
        echo "[FAILED] Build failed"
        exit 1
    fi
}

buildstb(){
    echo "[INFO] Building stb..."
    $CXX -o stb stb.cpp -Iinclude
    if [ $? -eq 0 ]; then
        echo "[SUCCESS] Build successful: ./stb"
    else
        echo "[FAILED] Build failed"
        exit 1
    fi
}

buildandrun() {
    build
    echo "[INFO] Running..."
    ./$OUT
}

clean() {
    echo "[INFO] Cleaning build files..."
    rm -rf build
    echo "[SUCCESS] Clean complete"
}

help() {
    echo "Usage: $0 {build|run|clean}"
    echo "  build       Compile the project"
    echo "  run         Build and run"
    echo "  clean       Remove build directory"
}

# Entry point
case "$1" in
    build) build ;;
    run) buildandrun ;;
    clean) clean ;;
    buildstb) buildstb ;;
    *) help ;;
esac
