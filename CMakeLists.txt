cmake_minimum_required(VERSION 3.10)
project(task_2_2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra --pedantic")


add_executable(main.out project/task/main.cpp)
target_include_directories(main.out PRIVATE project/binary_tree/)

add_executable(contest.out project/contest/contest.cpp)
