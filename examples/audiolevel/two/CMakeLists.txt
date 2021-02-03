cmake_minimum_required(VERSION 3.5)
project(two C CXX)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_FOR_OPENGL_EMULATOR 1)

include(../../CMakeLists.cmake.in)
include(../../examples.cmake.in)

if (DEFINED BUILD_FOR_OPENGL_EMULATOR)
    add_executable(two two.cpp ../../../src/AudioLevelView.cpp)
    target_link_libraries(two ${LIBS} ${teensy_x86_stubs_LIBS} ${teensy_st7735_linux_stubs_LIBS} ${teensy_st7735_linux_extras_opengl_LIBS})
else()
    teensy_add_executable(two two.cpp)
endif()