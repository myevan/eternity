cmake_minimum_required(VERSION 2.8)

project(Examples)

add_executable(HelloWorld Main.cpp)

add_custom_target(run
    COMMAND HelloWorld
    DEPENDS HelloWorld
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

target_link_libraries(HelloWorld Core)

include_directories("${PROJECT_SOURCE_DIR}/../..")
link_directories("${PROJECT_SOURCE_DIR}/../..")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
