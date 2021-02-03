cmake_minimum_required(VERSION 3.5)
project(cvlevel_basic C CXX)

set(CMAKE_CXX_STANDARD 11)
set(BUILD_FOR_OPENGL_EMULATOR 1)

include(../../CMakeLists.cmake.in)
include(../cvlevelexamples.cmake.in)
include(../../examples.cmake.in)

if (DEFINED BUILD_FOR_OPENGL_EMULATOR)
    add_executable(cvlevel_basic
            cvlevelbasic.cpp
            ${TEENSY_AUDIO_DISPLAY_COMPONENTS_SRC}/CVLevelView.cpp)
    target_link_libraries(cvlevel_basic ${LIBS} ${teensy_x86_stubs_LIBS} ${teensy_st7735_linux_stubs_LIBS} ${teensy_st7735_linux_extras_opengl_LIBS})
else()
    teensy_add_executable(cvlevel_basic
            cvlevelbasic.cpp)
endif()