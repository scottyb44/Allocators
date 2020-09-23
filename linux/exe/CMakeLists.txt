cmake_minimum_required (VERSION 3.0)

project (AllocatorExe)

add_executable(AllocatorExe allocator_main.cpp)
set_property(TARGET AllocatorExe PROPERTY CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-pthread")

include_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(AllocatorExe PRIVATE AllocatorLibrary)
