#ifndef T_GRAPH_H
#define T_GRAPH_H

#include "t_graph_vertex.h"
#include "t_graph_edge.h"
#include <vector>

// using t_graph_edge = std::pair<t_graph_vertex_id, t_graph_vertex_id>;
// using t_graph_edges = std::vector<t_graph_edge>;

class t_graph
{
public:
    t_graph();
    t_graph(const size_t amount);

    size_t verteces() const;

    size_t edges() const;
    
    t_vertex_id create_vertex(const t_vertex_id value);
    
    void link_vertex_with(const t_vertex_id vertex_id, const t_vertex_id linked_with_id);
    
    const t_graph_vertex_ids& get_linked_vertex_ids(const t_vertex_id vertex_id) const;

    void print_info() const;

protected:
    t_graph_verteces _verteces;

    t_graph_edges _edges;
};

// void t_print_vertex(const t_vertex& vertex);

void print(const std::vector<bool>& are_visited);

void check(const t_graph& graph, const bool must_be);

void check(const std::vector<bool>& are_visited, const bool must_be);

#endif // T_GRAPH_H
