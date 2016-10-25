cmake_minimum_required(VERSION 3.5)
project(time_experiments)


set(SOURCE_FILES clock_gettime_res.c)
add_executable(clock_gettime_res ${SOURCE_FILES})