

add_executable(accumulator_tests accumulator_tests.cpp)
target_link_libraries(accumulator_tests PRIVATE GTest::gmock_main)