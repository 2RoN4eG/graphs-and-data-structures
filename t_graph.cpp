#include "t_graph.h"

#include <iostream>

t_graph::t_graph()
    : t_graph({})
{
}

t_graph::t_graph(const size_t amount)
{
    _verteces.reserve(amount);
}

size_t t_graph::verteces() const
{
    return _verteces.size();
}

size_t t_graph::edges() const
{
    return _edges.size();
}

t_vertex_id t_graph::create_vertex(const t_vertex_id vertex_id)
{
    _verteces.emplace_back(vertex_id);

    return vertex_id;
}

void t_graph::link_vertex_with(const t_vertex_id vertex_id, const t_vertex_id neighbor_id)
{
    _verteces[vertex_id].link_with(neighbor_id);

    _edges.emplace_back(vertex_id, neighbor_id);
}

const t_graph_vertex_ids& t_graph::get_linked_vertex_ids(const t_vertex_id vertex_id) const
{
    return _verteces[vertex_id].get_linked_vertex_ids();
}

void t_graph::print_info() const
{
    std::cout << "verteces " << _verteces.size() << std::endl;
    std::cout << "paths " << _edges.size() << std::endl;
}

void print(const std::vector<bool> &are_visited)
{
    for (size_t index {}; index < are_visited.size(); ++ index)
    {
        const bool is_visited = are_visited[index];

        std::cout << "index: " << index << ", is_visited: " << (is_visited ? "true" : "false") << std::endl;
    }
}

void check(const std::vector<bool>& are_visited, const bool must_be)
{
    for (size_t index{}; index < are_visited.size(); ++index)
    {
        const bool is_visited = are_visited[index];

        if (is_visited != must_be)
        {
            throw std::runtime_error{"vertex's { index: " + std::to_string(index) +
                                     " } is_visited { " +
                                     (is_visited ? "true" : "false") +
                                     " } does not equal with must_be { " +
                                     (must_be ? "true" : "false") + " }"};
        }
    }
}
