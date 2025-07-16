include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(unity)


add_executable(test_scheduler scheduler_test.c)
target_link_libraries(test_scheduler scheduler unity)

add_executable(test_tm1638 tm1638_test.c tm1638_mock.c)
target_link_libraries(test_tm1638 tm1638 unity)

enable_testing()
add_test(NAME SchedulerTest COMMAND test_scheduler)
add_test(NAME TM1638Test COMMAND test_tm1638)
