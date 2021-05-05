cmake_minimum_required(VERSION 3.5)
project(teensy-audio-display-soundio-input-example C CXX)

set(CMAKE_CXX_STANDARD 11)

include(../CMakeLists.cmake.in)

include_directories(../../../src)

add_executable(input
        input.cpp
        ../../../src/AudioLevelView.cpp)
target_link_libraries(input ${LIBS} ${teensy_x86_stubs_LIBS} ${teensy_x86_sd_stubs_LIBS} ${teensy_audio_x86_stubs_LIBS} ${teensy_audio_x86_stubs_soundio_LIBS} ${teensy_st7735_linux_stubs_LIBS} ${teensy_st7735_linux_extras_opengl_LIBS})
target_link_libraries(input /usr/local/lib/libsoundio.a)
target_link_libraries(input
        "-framework CoreServices"
        "-framework CoreAudio"
        "-framework Foundation"
        "-framework AudioUnit")

