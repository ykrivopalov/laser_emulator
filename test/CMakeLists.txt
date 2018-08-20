include(GoogleTest)
 
add_executable(tests laser_emulator.cpp)
target_link_libraries(tests gtest_main liblaser_emulator)
 
gtest_discover_tests(tests)
