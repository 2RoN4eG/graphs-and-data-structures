#include "t_graph_edge.h"

t_graph_edge::t_graph_edge()
    : t_graph_edge({}, {}, {}, {})
{
}

t_graph_edge::t_graph_edge(const t_vertex_id from, const t_vertex_id to)
    : t_graph_edge({}, from, to, {})
{
}

t_graph_edge::t_graph_edge(const t_vertex_id from, const t_vertex_id to, const t_graph_edge_weight weight)
    : t_graph_edge({}, from, to, weight)
{
}

t_graph_edge::t_graph_edge(const t_edge_id id, const t_vertex_id from, const t_vertex_id to, const t_graph_edge_weight weight)
    : _id { id }
    , _from_id { from }
    , _to_id { to }
    , _weight { weight }
{
}
