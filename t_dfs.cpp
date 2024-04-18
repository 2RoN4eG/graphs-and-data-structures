#include "t_dfs.h"

#include <stack>

t_dfs::t_dfs() {}

void t_dfs::operator()(const t_graph &graph, const t_vertex_id &initial_vertex_id) {
    std::vector<bool> are_visited(graph.verteces(), {});
    check(are_visited, {});
    
    std::stack<t_vertex_id> stack;

    stack.push(initial_vertex_id);
    are_visited[initial_vertex_id] = true;

    while (!stack.empty())
    {
        const t_vertex_id vertex_id = stack.top();
        stack.pop();
        
        for (const t_vertex_id linked_vertex_id : graph.get_linked_vertex_ids(vertex_id))
        {
            if (are_visited[linked_vertex_id])
            {
                continue;
            }

            are_visited[linked_vertex_id] = true;

            stack.push(linked_vertex_id);
        }
    }

    check(are_visited, true);
}
