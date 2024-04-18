#ifndef T_WEIGHTED_GRAPH_H
#define T_WEIGHTED_GRAPH_H

#include "t_value.h"
#include "t_graph.h"
#include "t_graph_vertex.h"
#include "t_defines.h"

#include <iostream>

struct t_vertex_comparator
{
public:
    bool operator()(const t_graph_vertex& lhs, const t_graph_vertex& rhs) const
    {
        return lhs._id < rhs._id;
    }
};

// std::set не используется в силу того, что поиск необходимой вершины очень медленный за время O(log N)
// std::vector используется с переизбытком памяти но организует доступ к вертексу за время O(1)

// using t_weighted_graph_edges = std::vector<t_weighted_graph_edge>;


struct t_size
{
    size_t _width {};

    size_t _height {};
};

class t_graph_weighted
{
public:
    t_graph_weighted(const size_t w, const size_t h);

    size_t verteces() const;
    size_t edges() const;

    size_t area() const;

    void create_vertex(const t_vertex_id vertex_id) = delete;
    void destroy_vertex(const t_vertex_id vertex_id) = delete;

    void create_vertex(const t_vertex_id vertex_id, int x, int y);
    void destroy_verteces(const std::vector<t_vertex_id>& vertex_ids);

    inline const t_graph_vertex& get_vertex(const t_vertex_id vertex_id) const {
        const t_graph_vertex& vertex = _verteces[vertex_id];

        if (vertex._id != vertex_id)
        {
            throw std::runtime_error { " vertex's id { " + std::to_string(vertex_id) + " } is not equeal with vertex_id { " + std::to_string(vertex._id) + " }" };
        }

        return vertex;
    }

    inline const t_graph_edge& get_edge(const t_edge_id edge_id) const
    {
        const t_graph_edge& edge = _edges[edge_id];

        if (edge._id != edge_id)
        {
            throw std::runtime_error { " vertex's id { " + std::to_string(edge_id) + " } is not equeal with vertex_id { " + std::to_string(edge._id) + " }" };
        }

        return edge;
    }

    void create_edge(const t_vertex_id from_id, const t_vertex_id to_id, const t_graph_edge_weight weight = t_graph_edge_weight { 1 });
    void destroy_edge(const t_vertex_id vertex_id, const t_vertex_id with_vertex_id);

    const t_graph_edge_weight get_weight_by_from_to_ids(const t_vertex_id from_id, const t_vertex_id to_id) const = delete;
    const t_graph_edge_weight get_weight_by_edge_id(const t_edge_id edge_id) const;

    const t_graph_vertex_ids& get_linked_vertex_ids(const t_vertex_id vertex_id) const = delete;

    inline const t_vertex_id get_next_vertex_id(const t_edge_id edge_id) const
    {
        const t_graph_edge& edge = get_edge(edge_id);

        return edge._to_id;
    }

    inline const t_graph_vertex_ids& get_edge_ids_by_from_id(const t_vertex_id vertex_id) const
    {
        const t_graph_vertex& vertex = get_vertex(vertex_id);

        return vertex.edge_ids();
    }


    const bool does_exist(const t_vertex_id vertex_id) const;

    void print_info() const;

    void check(const t_vertex_id vertex_id) const;

    const t_width width() const { return _size._width; }

    const t_height height() const { return _size._height; }

protected:
    t_size _size;

    t_value_generator<t_vertex_id> _vertex_id_generator;
    t_graph_verteces _verteces;

    t_value_generator<t_edge_id> _edge_id_generator;
    t_graph_edges _edges;
};

#endif // T_WEIGHTED_GRAPH_H
