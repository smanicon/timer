add_library(scheduler STATIC scheduler.c)
target_include_directories(scheduler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
