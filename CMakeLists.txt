cmake_minimum_required (VERSION 3.12)

project ("MorphText")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
set(CMAKE_CXX_STANDARD 23)

#add_executable (MorphText 
#	MorphText/Lookup.hpp
##	MorphText/MorphText.cpp
#	MorphText/MorphText.hpp
#)

configure_file(config.h.in config.h)
include_directories(${CMAKE_CURRENT_BINARY_DIR})



# Add sources for dll generation
set(SOURCES
	MorphText/Lookup.hpp
	MorphText/MorphText.cpp
	MorphText/MorphText.hpp
)

# Create a shared library (.dll)
add_library(MorphText SHARED ${SOURCES})

# Include directories (if needed)
target_include_directories(MorphText PUBLIC include)

# Link libraries (if needed)
#target_link_libraries(MorphText PUBLIC some_other_library)