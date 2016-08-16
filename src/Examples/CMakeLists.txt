cmake_minimum_required(VERSION 2.8)

project(Examples)

find_package(Boost COMPONENTS system)

include_directories("${Boost_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/..")
link_directories("${PROJECT_SOURCE_DIR}/..")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(HelloCore HelloCore/Main.cpp)
target_link_libraries(HelloCore Core)

add_executable(HelloBoost HelloBoost/Main.cpp)
target_link_libraries(HelloBoost Core)
target_link_libraries(HelloBoost ${Boost_LIBRARIES})

add_custom_target(run_HelloCore
    COMMAND HelloCore
    DEPENDS HelloCore
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(run_HelloBoost
    COMMAND HelloBoost
    DEPENDS HelloBoost
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

