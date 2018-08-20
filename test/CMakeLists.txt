include(GoogleTest)

include_directories(${PROJECT_SOURCE_DIR}/googletest/googletest/gtest/gtest.h)
include_directories(${PROJECT_SOURCE_DIR}/googletest/googlemock/gmock/gmock.h)
 
add_executable(tests laser_emulator.cpp protocol.cpp)
target_link_libraries(tests gmock_main liblaser_emulator)
 
gtest_discover_tests(tests)
