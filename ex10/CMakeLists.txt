cmake_minimum_required(VERSION 3.12)
project(ex10)

set(BUILD_DIR .)
message(${BUILD_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
add_custom_target(part2 COMMAND make -C ${BUILD_DIR})