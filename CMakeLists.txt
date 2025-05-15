cmake_minimum_required(VERSION 3.10.0)
project(AiDS3 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(program main.cpp adjacencylist.cpp adjacencymatrix.cpp edgelist.cpp graph.cpp gui.cpp)

