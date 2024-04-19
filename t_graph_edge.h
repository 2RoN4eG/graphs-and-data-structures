#ifndef T_GRAPH_EDGE_H
#define T_GRAPH_EDGE_H

#include "t_defines.h"
#include <iostream>


struct t_graph_edge
{
public:
    t_graph_edge();
    t_graph_edge(const t_vertex_id from, const t_vertex_id to);
    t_graph_edge(const t_vertex_id from, const t_vertex_id to, const t_graph_edge_weight weight);
    t_graph_edge(const t_edge_id id, const t_vertex_id from, const t_vertex_id to, const t_graph_edge_weight weight);

public:
    t_edge_id _id {};

    t_vertex_id _from_id {};

    t_vertex_id _to_id {};

    t_graph_edge_weight _weight {};
};

inline std::ostream& operator<<(std::ostream& stream, const t_graph_edge& edge)
{
    stream << "edge { id: " <<  edge._id << ", from_id: " << edge._from_id << ", to_id: " << edge._to_id << ", _weight: " << edge._weight << " }";

    return stream;
}

using t_graph_edges = std::vector<t_graph_edge>;

#endif // T_GRAPH_EDGE_H
