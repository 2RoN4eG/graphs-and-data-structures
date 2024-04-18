#ifndef T_DFS_H
#define T_DFS_H

#include "t_graph.h"

#include <string>
#include <iostream>

// Depth First Search
class t_dfs
{
public:
    t_dfs();
    
    void operator()(const t_graph& graph, const t_vertex_id& initial_vertex_id);

protected:
};

#endif // T_DFS_H
