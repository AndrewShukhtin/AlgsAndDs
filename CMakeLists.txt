cmake_minimum_required(VERSION 3.10)
project(graph_representation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra --pedantic")

set(IGRAPH_DIR project/IGraph)
set(LIST_GRAPH_DIR project/ListGraph)
set(MATRIX_GRAPH_DIR project/MatrixGraph)
set(SET_GRAPH_DIR project/SetGraph)
set(ARC_GRAPH_DIR project/ArcGraph)

set(GRAPHS_INCLUDE_DIRS
                        ${IGRAPH_DIR}
                        ${LIST_GRAPH_DIR}
                        ${MATRIX_GRAPH_DIR}
                        ${SET_GRAPH_DIR}
                        ${ARC_GRAPH_DIR})

set(GRAPHS_HEADERS
                    ${IGRAPH_DIR}/IGraph.hpp
                    ${LIST_GRAPH_DIR}/ListGraph.hpp
                    ${MATRIX_GRAPH_DIR}/MatrixGraph.hpp
                    ${SET_GRAPH_DIR}/SetGraph.hpp
                    ${ARC_GRAPH_DIR}/ArcGraph.hpp)

set(GRAPHS_SRC
                    ${LIST_GRAPH_DIR}/ListGraph.cpp
                    ${MATRIX_GRAPH_DIR}/MatrixGraph.cpp
                    ${SET_GRAPH_DIR}/SetGraph.cpp
                    ${ARC_GRAPH_DIR}/ArcGraph.cpp)

add_library(GraphsLib STATIC ${GRAPHS_HEADERS} ${GRAPHS_SRC})
target_include_directories(GraphsLib PUBLIC ${GRAPHS_INCLUDE_DIRS})

add_executable(main.out project/main.cpp)
target_link_libraries(main.out GraphsLib)