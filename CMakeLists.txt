cmake_minimum_required (VERSION 3.12)

project ("MorphText")

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

