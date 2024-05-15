cmake_minimum_required (VERSION 3.12)

project ("MorphText")

add_executable (MorphText MorphText/Lookup.h)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

