cmake_minimum_required(VERSION 3.11)

project(prng)

# Library target
add_library(prng INTERFACE)
target_include_directories(prng INTERFACE "include")
target_compile_features(prng INTERFACE cxx_std_11)

# Top-level build
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	add_subdirectory("test")
endif ()
