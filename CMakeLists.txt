cmake_minimum_required (VERSION 3.10)

project (laser_emulator)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
include_directories("${gmock_SOURCE_DIR}/include"
                    "${gtest_SOURCE_DIR}/include")

add_subdirectory (lib)
add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (googletest)
