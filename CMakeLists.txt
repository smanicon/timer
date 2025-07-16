cmake_minimum_required(VERSION 3.15)
project(tm1638_timer_project C ASM)

add_subdirectory(lib/scheduler)
add_subdirectory(lib/tm1638)

if(NOT CMAKE_TOOLCHAIN_FILE)
  enable_testing()
  add_subdirectory(test)
else()
  add_subdirectory(src)
endif()
