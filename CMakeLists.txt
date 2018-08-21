cmake_minimum_required (VERSION 3.10)

project (laser_emulator)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
endif ()

set (CMAKE_CXX_STANDARD 14)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
include_directories("${gmock_SOURCE_DIR}/include"
                    "${gtest_SOURCE_DIR}/include")

add_subdirectory (lib)
add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (googletest)
