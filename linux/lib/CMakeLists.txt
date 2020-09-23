cmake_minimum_required(VERSION 3.2.2)

project(AllocatorLibrary)

add_library(AllocatorLibrary Allocator.h)
set_property(TARGET AllocatorLibrary PROPERTY CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")
