project(mlk_lib)

cmake_minimum_required(VERSION 2.8)


set(CMAKE_CXX_FLAGS "-std=c++0x")
set(SRC "src")
set(HDR "include")
set(LIST "")
include_directories(${HDR})


file(GLOB_RECURSE LIST "${HDR}/*.h")
add_library(mlk SHARED ${LIST})
set_target_properties(mlk PROPERTIES LINKER_LANGUAGE CXX)
