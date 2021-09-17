
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(Huffmancoder LANGUAGES CXX)

find_package(Catch2 REQUIRED)


add_executable(Huffmancoder lib/main.cpp)

target_compile_features(Huffmancoder PUBLIC cxx_std_17)

install(TARGETS Huffmancoder DESTINATION bin)

install(PROGRAMS demo DESTINATION bin)



add_library(huffman_tree SHARED lib/huffmantree.cpp)

add_executable(test_graph app/test_graph.cpp)

target_include_directories(test_graph PUBLIC lib)

target_link_libraries(test_graph Catch2::Catch2)

target_link_libraries(test_graph huffman_tree)

target_compile_features(test_graph PUBLIC cxx_std_17)