include(FetchContent)

FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(unity)

enable_testing()

add_executable(test_scheduler scheduler_test.c)
target_link_libraries(test_scheduler scheduler unity)

add_test(NAME SchedulerTest COMMAND test_scheduler)
