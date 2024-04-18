#ifndef T_BFS_H
#define T_BFS_H

#include "t_graph.h"

#include <string>
#include <iostream>

// Breadth First Search
class t_bfs
{
public:
    t_bfs();
    
    void operator()(const t_graph& graph, const t_vertex_id initial_vertex_id);
};

#endif // T_BFS_H
