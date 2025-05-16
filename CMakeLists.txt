cmake_minimum_required(VERSION 3.15)  # Bumped for better modern features
project(AiDS3 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create executable first
add_executable(program)

# Target properties
target_compile_features(program PRIVATE cxx_std_23)

# Source files (now using explicit relative paths from project root)
target_sources(program PRIVATE
    src/main.cpp
    src/adjacencylist.cpp
    src/adjacencymatrix.cpp
    src/edgelist.cpp
    src/graph.cpp
    src/gui.cpp
)

# Include directories (modern way)
target_include_directories(program PRIVATE
    include
    src
)

# Optional: Better build type handling
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Optional: Install targets
install(TARGETS program DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)