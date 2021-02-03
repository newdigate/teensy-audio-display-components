cmake_minimum_required(VERSION 3.5)
project(audio_level_examples CXX)

set(CMAKE_CXX_STANDARD 11)

set(TEENSY_AUDIO_DISPLAY_COMPONENTS_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

add_subdirectory(basic)
add_subdirectory(multiple)
add_subdirectory(two)