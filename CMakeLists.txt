cmake_minimum_required (VERSION 3.12)

project ("MorphText")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set_property(TARGET PROPERTY CXX_STANDARD 23)

add_executable (MorphText MorphText/Lookup.h)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

