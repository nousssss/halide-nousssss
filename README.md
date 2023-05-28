# PFE Challenge

## Requirements
- GCC (GNU Compiler Collection).
- G++ (GNU Compiler Collection).
- Halide.

## Building LLVM and Halide from Source
To build Halide, I first built LLVM following the instructions on the ReadMe page;
 
I checked out the release/15.x branch and launched:
 
```bash
$ cmake -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_ENABLE_PROJECTS="clang;lld;clang-tools-extra" \
        -DLLVM_TARGETS_TO_BUILD="X86;ARM;NVPTX;AArch64;Hexagon;WebAssembly" \
        -DLLVM_ENABLE_TERMINFO=OFF -DLLVM_ENABLE_ASSERTIONS=ON \
        -DLLVM_ENABLE_EH=ON -DLLVM_ENABLE_RTTI=ON -DLLVM_BUILD_32_BITS=OFF \
        -S llvm-project/llvm -B llvm-build
```

Then I launched the build process by running:
```
$ cmake --build llvm-build -j20
```
 
To make the build faster I added the `-j 20` option to build in parallel.
 
After installing LLVM and setting the ENV variables for Halide, I did the same thing:
 
```bash
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_DIR=$LLVM_ROOT/lib/cmake/llvm -S . -B build
$ cmake --build build -j20
```
 
The result of this is a build folder containing the header file 'Halide.h' and the shared compiled library 'libHalide.so'.
 
To compile a Halide program I just need to instruct the linked to use the shared library (as per Halide tutorials):
```bash
$ g++ main.cpp -g -I Halide/build/include -L Halide/build/src -lHalide -lpthread -ldl -o app -std=c++17
```
To run the generated binary:
```bash
$ LD_LIBRARY_PATH=Halide/build/src/ ./app
```
 
 ## Using the Script
To use the script that compares the C code and Halide code results, follow these steps:

1. Make sure you have set the environment variables `HALIDE_INCLUDE_PATH` and `HALIDE_SHARED_LIB_PATH` appropriately. If Halide is built systemwide, you don't need to set these variables.

2. Compile and run the script (make sure that the script and the source files are in the same folder)

```bash
$ git clone https://github.com/nousssss/halide-nousssss
$ cd halide-nousssss/code/
$ HALIDE_INCLUDE_PATH=/path/to/halide/headers/folder HALIDE_SHARED_LIB_PATH=/path/to/halide/libs/folder python3 script.py
```
