include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(mock_tm1638 STATIC mock/tm1638_mock.cpp mock/Trame.cpp mock/TrameManager.cpp)
target_link_libraries(mock_tm1638 tm1638 GTest::gtest_main)
target_include_directories(mock_tm1638 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/mock)

add_executable(test_scheduler scheduler_test.cpp)
target_link_libraries(test_scheduler scheduler GTest::gtest_main)

add_executable(test_tm1638 tm1638_test.cpp)
target_link_libraries(test_tm1638 tm1638 mock_tm1638 GTest::gtest_main)


enable_testing()
add_test(NAME SchedulerTest COMMAND test_scheduler)
add_test(NAME TM1638Test COMMAND test_tm1638)

include(GoogleTest)
gtest_discover_tests(test_scheduler)
gtest_discover_tests(test_tm1638)
