cmake_minimum_required(VERSION 3.1)
project(lodashcpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lodashcpp STATIC lodash.hpp)