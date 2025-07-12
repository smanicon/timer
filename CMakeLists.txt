cmake_minimum_required(VERSION 3.15)
project(tm1638_timer_project C ASM)

add_subdirectory(lib/scheduler)

if(NOT CMAKE_TOOLCHAIN_FILE)
  add_subdirectory(test)
else()
  add_subdirectory(src)
endif()
