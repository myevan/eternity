cmake_minimum_required(VERSION 2.8)

project (Examples)

add_executable(HelloWorld Main.cpp)

add_custom_target(run
    COMMAND HelloWorld
    DEPENDS HelloWorld
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
