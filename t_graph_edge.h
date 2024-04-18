#ifndef T_GRAPH_EDGE_H
#define T_GRAPH_EDGE_H

#include "t_defines.h"
#include <iostream>


struct t_graph_edge
{
public:
    t_graph_edge()
        : t_graph_edge({}, {}, {}, {})
    {
    }

    t_graph_edge(const t_vertex_id from, const t_vertex_id to)
        : t_graph_edge({}, from, to, {})
    {
    }

    t_graph_edge(const t_vertex_id from, const t_vertex_id to, const t_graph_edge_weight weight)
        : t_graph_edge({}, from, to, weight)
    {
    }

    t_graph_edge(const t_edge_id id, const t_vertex_id from, const t_vertex_id to, const t_graph_edge_weight weight)
        : _id { id }
        , _from_id { from }
        , _to_id { to }
        , _weight { weight }
    {
    }

    friend bool operator==(const t_graph_edge& lhs, const t_graph_edge& rhs)
    {
        return lhs._from_id == rhs._from_id &&
               lhs._to_id == rhs._to_id &&
               lhs._weight == rhs._weight;
    }

    friend bool operator<(const t_graph_edge& lhs, const t_graph_edge& rhs)
    {
        return lhs._from_id == rhs._from_id && lhs._to_id < rhs._to_id;
    }

public:
    t_edge_id _id {};

    t_vertex_id _from_id {};

    t_vertex_id _to_id {};

    t_graph_edge_weight _weight {};
};

inline std::ostream& operator<<(std::ostream& stream, const t_graph_edge& edge)
{
    stream << "edge { from_id: " << edge._from_id << ", to_id: " << edge._to_id << ", _weight: " << edge._weight << " }";

    return stream;
}

struct t_graph_edge_comparator
{
public:
    bool operator()(const t_graph_edge& lhs, const t_graph_edge& rhs) const
    {
        if (lhs._from_id == rhs._from_id)
        {
            return lhs._to_id < rhs._to_id;
        }

        return lhs._from_id < rhs._from_id;
    }

    bool operator()(const t_graph_edge& edge, const t_vertex_id vertex_id) const
    {
        return edge._from_id == vertex_id || edge._to_id == vertex_id;
    }
};

using t_graph_edges = std::vector<t_graph_edge>;

#endif // T_GRAPH_EDGE_H
