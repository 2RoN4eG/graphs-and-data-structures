#ifndef T_GRAPH_VERTEX_H
#define T_GRAPH_VERTEX_H

#include "t_value.h"
#include "t_defines.h"


struct t_2d_position
{
public:
    t_2d_position(const t_axis x, const t_axis y)
        : _x { x }
        , _y { y }
    {
    }

    t_2d_position()
        : t_2d_position({}, {})
    {
    }

public:
    t_axis _x;
    t_axis _y;
};

class t_graph_vertex
{
public:
    t_graph_vertex();
    t_graph_vertex(const t_vertex_id& id);
    t_graph_vertex(const t_vertex_id& id, const t_axis x, const t_axis y);

    void link_with(const t_vertex_id vertex_id);
    void unlink_with(const t_vertex_id& vertex_id);
    void clear_linked_ids();

    void register_edge_id(const t_edge_id edge_id);

    inline const t_graph_edge_ids& edge_ids() const {
        return _edge_ids;
    }

    const t_graph_vertex_ids& get_linked_vertex_ids() const;
    const size_t get_linked_vertex_size() const;

    t_graph_vertex(const t_graph_vertex& other) = default;
    t_graph_vertex& operator=(const t_graph_vertex& other)  = default;

    t_graph_vertex(t_graph_vertex&& other) = default;
    t_graph_vertex& operator=(t_graph_vertex&& other) = default;

public:
    t_vertex_id _id {};

    t_2d_position _position;

    mutable t_graph_vertex_ids _linked_vertex_ids;

    mutable t_graph_edge_ids _edge_ids;
};

using t_graph_verteces = std::vector<t_graph_vertex>;

#endif // T_GRAPH_VERTEX_H
