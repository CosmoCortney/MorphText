cmake_minimum_required (VERSION 3.12)
set(CMAKE_CXX_STANDARD 20)  # Use the desired C++ standard version
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=UTF-8")
elseif(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()
add_executable (MorphText "main.cpp" "MorphText.h" )

