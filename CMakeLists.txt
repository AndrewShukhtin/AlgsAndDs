cmake_minimum_required(VERSION 3.10)
project(shortestPath)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra --pedantic")

set(IGRAPH_DIR project/IGraph)
set(LIST_GRAPH_DIR project/ListGraph)

set(GRAPHS_INCLUDE_DIRS
                        ${IGRAPH_DIR}
                        ${LIST_GRAPH_DIR})

add_executable(main.out project/main.cpp)
target_include_directories(main.out PRIVATE ${GRAPHS_INCLUDE_DIRS})

add_executable(contest.out project/Contest/Contest.cpp)