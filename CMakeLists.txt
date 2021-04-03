cmake_minimum_required(VERSION 3.17)
project(NJU_CS_Graph_Theory)

set(CMAKE_CXX_STANDARD 11)

add_executable(Hungarian Hungarian.cpp)
add_executable(Hopcroft_Karp Hopcroft_Karp.cpp)
add_executable(Hopcroft_Karp_max_weight Hopcroft_Karp_max_weight.cpp)