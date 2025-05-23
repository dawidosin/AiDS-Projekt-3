cmake_minimum_required(VERSION 3.15)
project(AiDS3 VERSION 0.1.0 LANGUAGES CXX)

# Set C++ version
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable
add_executable(program
    src/main.cpp
    src/adjacencylist.cpp
    src/adjacencymatrix.cpp
    src/edgelist.cpp
    src/graph.cpp
    src/gui.cpp
)

# Use C++23 features
target_compile_features(program PRIVATE cxx_std_23)

# Include directories
target_include_directories(program PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Place executable directly in the build/ directory
set_target_properties(program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_NAME "program"
)

# Default to Release build if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Install rule (optional, for packaging)
install(TARGETS program DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)
