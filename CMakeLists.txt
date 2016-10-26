cmake_minimum_required(VERSION 2.8.12)
project(time_tests)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
set(SOURCE_FILES clock_gettime_res.c)
add_executable(clock_gettime_res clock_gettime_res.c)
add_executable(ptp_clock_check ptp_clock_check.c)
target_link_libraries(clock_gettime_res rt)
target_link_libraries(ptp_clock_check rt)