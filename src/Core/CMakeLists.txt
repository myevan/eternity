cmake_minimum_required(VERSION 2.8)

project(Core)

add_library(Core Payload.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
