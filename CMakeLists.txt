cmake_minimum_required(VERSION 3.15)
project(AiDS3 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable with proper name and output location
add_executable(aids3-program
    src/main.cpp
    src/adjacencylist.cpp
    src/adjacencymatrix.cpp
    src/edgelist.cpp
    src/graph.cpp
    src/gui.cpp
)

# Target properties
target_compile_features(aids3-program PRIVATE cxx_std_23)

# Include directories
target_include_directories(aids3-program PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set output directory to build folder
set_target_properties(aids3-program PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build
    OUTPUT_NAME "program"
)

# Better build type handling
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Install targets
install(TARGETS aids3-program DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)