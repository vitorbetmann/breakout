To use this template, make sure to change set(RAYLIB_DIR $ENV{HOME}/\_dev/raylib) to your own
raylib location

to compile natively, from inside the root dir, run cmake -S . -B build
to compile for web, from inside the root dir, run emcmake cmake -S . -B build_web [-DCMAKE_BUILD_TYPE=Release]

from inside the build/build_web dir, run ninja

If your game has no assets, remove the flag: --preload-file ../assets@assets from set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS})

before building a folder, just do scan-build cmake -S . -B build (or cmake .. if inside build already) and ninja to build it
