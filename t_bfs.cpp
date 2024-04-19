#include "t_bfs.h"

#include <queue>

t_bfs::t_bfs() {}

void t_bfs::operator()(const t_graph &graph, const t_vertex_id initial_vertex_id) {
    std::vector<bool> are_visited(graph.verteces(), {});
    check(are_visited, {});
    
    std::queue<t_vertex_id> queue;

    queue.push(initial_vertex_id);
    are_visited[initial_vertex_id] = true;

    while (!queue.empty())
    {
        const t_vertex_id vertex_id = queue.front();
        queue.pop();

        // const t_vertex vertex = graph.get_vertex_by_id(vertex_id);
        
        for (const t_vertex_id& linked_vertex_id : graph.get_vertex_ids(vertex_id))
        {
            if (are_visited[linked_vertex_id])
            {
                continue;
            }

            are_visited[linked_vertex_id] = true;

            queue.emplace(linked_vertex_id);
        }
    }

    check(are_visited, true);
}
