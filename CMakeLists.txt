# Project-Setup
cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Release")
project(RenderingEngine)
set(COMPILER_OPTIONS "-DLOG_USE_COLOR -O3")
set(LINKER_FLAGS "-lm -lglfw3 -lX11 -ldl -lfreetype -pthread -lchipmunk")

# Source files
file(GLOB_RECURSE SRC_SANDBOX apps/sandboxDemo/src/*.c)
file(GLOB_RECURSE SRC_WRATH apps/wrathGLDemo/src/*.c)
file(GLOB_RECURSE SRC_POWDER apps/powderTrainDemo/src/*.c)
file(GLOB_RECURSE SRC_2D engine-core/2D/src/*.c)
file(GLOB_RECURSE SRC_3D engine-core/3D/src/*.c)
file(GLOB_RECURSE SRC_ENGINE engine-core/general/src/*.c)
file(GLOB_RECURSE SRC_VENDOR engine-core/vendor/src/*.c)

# Static libraries
add_library(2D_Engine STATIC ${SRC_2D} ${SRC_ENGINE} ${SRC_VENDOR})
add_library(3D_Engine STATIC ${SRC_3D} ${SRC_ENGINE} ${SRC_VENDOR})

# Include directories for the libraries
target_include_directories(2D_Engine PUBLIC engine-core/2D/include)
target_include_directories(2D_Engine PUBLIC engine-core/general/include)
target_include_directories(2D_Engine PUBLIC engine-core/vendor/include)
target_include_directories(3D_Engine PUBLIC engine-core/3D/include)
target_include_directories(3D_Engine PUBLIC engine-core/general/include)
target_include_directories(3D_Engine PUBLIC engine-core/vendor/include)

# Compiler flags for the libraries
target_compile_options(2D_Engine PUBLIC ${COMPILER_OPTIONS})
target_compile_options(3D_Engine PUBLIC ${COMPILER_OPTIONS})

# Executables
add_executable(sandboxDemo apps/sandboxDemo/sandboxDemo.c ${SRC_SANDBOX})
add_executable(wrathGLDemo apps/wrathGLDemo/wrathGLDemo.c ${SRC_WRATH})
add_executable(powderTrainDemo apps/powderTrainDemo/powderTrainDemo.c ${SRC_POWDER})

# Compiler flags for the executables
target_compile_options(sandboxDemo PUBLIC ${COMPILER_OPTIONS})
target_compile_options(wrathGLDemo PUBLIC ${COMPILER_OPTIONS})
target_compile_options(powderTrainDemo PUBLIC ${COMPILER_OPTIONS})

# Include directories for the executables
target_include_directories(sandboxDemo PUBLIC apps/sandboxDemo/include)
target_include_directories(wrathGLDemo PUBLIC apps/wrathGLDemo/include)
target_include_directories(powderTrainDemo PUBLIC apps/powderTrainDemo/include)

# Link against static libraries
target_link_libraries(sandboxDemo PUBLIC 2D_Engine)
target_link_libraries(wrathGLDemo PUBLIC 3D_Engine)
target_link_libraries(powderTrainDemo PUBLIC 2D_Engine)

# Linker flags
target_link_libraries(sandboxDemo PUBLIC ${LINKER_FLAGS})
target_link_libraries(wrathGLDemo PUBLIC ${LINKER_FLAGS})
target_link_libraries(powderTrainDemo PUBLIC ${LINKER_FLAGS})