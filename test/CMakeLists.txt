include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(unity)

add_library(mock_tm1638 mock/tm1638_mock.c)
target_link_libraries(mock_tm1638 tm1638 unity)
target_include_directories(mock_tm1638 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/mock)

include(GenerateUnityMain.cmake)

add_executable(test_scheduler scheduler_test.c)
target_link_libraries(test_scheduler scheduler unity)
generate_main_test(test_scheduler)

add_executable(test_tm1638 tm1638_test.c)
target_link_libraries(test_tm1638 tm1638 mock_tm1638 unity)
generate_main_test(test_tm1638)


enable_testing()
add_test(NAME SchedulerTest COMMAND test_scheduler)
add_test(NAME TM1638Test COMMAND test_tm1638)
