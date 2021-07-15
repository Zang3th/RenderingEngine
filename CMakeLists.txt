# Project-Setup
cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Release")
project(RenderingEngine)

# Source files
file(GLOB_RECURSE SRC_SANDBOX apps/sandboxDemo/src/*.c)
file(GLOB_RECURSE SRC_WRATH apps/wrathGLDemo/src/*.c)
file(GLOB_RECURSE SRC_POWDER apps/powderTrainDemo/src/*.c)
file(GLOB_RECURSE SRC_2D engine-core/2D/src/*.c)
file(GLOB_RECURSE SRC_3D engine-core/3D/src/*.c)
file(GLOB_RECURSE SRC_ENGINE engine-core/general/src/*.c)
file(GLOB_RECURSE SRC_VENDOR engine-core/vendor/src/*.c)

# Executables
add_executable(sandboxDemo apps/sandboxDemo/sandboxDemo.c ${SRC_SANDBOX} ${SRC_2D} ${SRC_ENGINE} ${SRC_VENDOR})
add_executable(wrathGLDemo apps/wrathGLDemo/wrathGLDemo.c ${SRC_WRATH} ${SRC_3D} ${SRC_ENGINE} ${SRC_VENDOR})
add_executable(powderTrainDemo apps/powderTrainDemo/powderTrainDemo.c ${SRC_POWDER} ${SRC_2D} ${SRC_ENGINE} ${SRC_VENDOR})

# Compiler flags
target_compile_options(sandboxDemo PUBLIC "-DLOG_USE_COLOR -O3")
target_compile_options(wrathGLDemo PUBLIC "-DLOG_USE_COLOR -O3")
target_compile_options(powderTrainDemo PUBLIC "-DLOG_USE_COLOR -O3")

# Include directories
target_include_directories(sandboxDemo PUBLIC apps/sandboxDemo/include)
target_include_directories(sandboxDemo PUBLIC engine-core/2D/include)
target_include_directories(sandboxDemo PUBLIC engine-core/general/include)
target_include_directories(sandboxDemo PUBLIC engine-core/vendor/include)
target_include_directories(wrathGLDemo PUBLIC apps/wrathGLDemo/include)
target_include_directories(wrathGLDemo PUBLIC engine-core/3D/include)
target_include_directories(wrathGLDemo PUBLIC engine-core/general/include)
target_include_directories(wrathGLDemo PUBLIC engine-core/vendor/include)
target_include_directories(powderTrainDemo PUBLIC apps/powderTrainDemo/include)
target_include_directories(powderTrainDemo PUBLIC engine-core/2D/include)
target_include_directories(powderTrainDemo PUBLIC engine-core/general/include)
target_include_directories(powderTrainDemo PUBLIC engine-core/vendor/include)

# Linker flags
target_link_libraries(sandboxDemo PUBLIC "-lm -lglfw3 -lX11 -ldl -lfreetype -pthread -lchipmunk")
target_link_libraries(wrathGLDemo PUBLIC "-lm -lglfw3 -lX11 -ldl -lfreetype -pthread -lchipmunk")
target_link_libraries(powderTrainDemo PUBLIC "-lm -lglfw3 -lX11 -ldl -lfreetype -pthread -lchipmunk")