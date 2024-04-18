cmake_minimum_required(VERSION 3.5)

project(Graphs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Graphs main.cpp
    t_dfs.h             t_dfs.cpp
    t_graph.h           t_graph.cpp
    t_value.h           t_value.cpp
    t_bfs.h             t_bfs.cpp
    t_merge_sorting.h   t_merge_sorting.cpp
    t_rb_tree.h         t_rb_tree.cpp
    t_weighted_graph.h  t_weighted_graph.cpp
    t_wgfs.h            t_wgfs.cpp
    t_a_star.h          t_a_star.cpp
    t_graph_vertex.h    t_graph_vertex.cpp
    t_defines.h         t_defines.cpp
    t_graph_edge.h t_graph_edge.cpp
)

include(GNUInstallDirs)
install(TARGETS Graphs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
