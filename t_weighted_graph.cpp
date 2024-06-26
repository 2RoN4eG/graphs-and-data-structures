#include "t_weighted_graph.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ranges>

#include "t_graph_vertex.h"
#include "t_graph_edge.h"

namespace
{

void t_print_verteces_command(const t_graph_verteces& verteces)
{
    for (const t_graph_vertex& vertex : verteces)
    {
        std::cout << "vertex { id: " << vertex._id
                  << ", x: " << vertex._position._x
                  << ", y: " << vertex._position._y
                  << " } linked with " << vertex.vertex_ids().size()
                  << std::endl;
    }
}

void t_print_edges_command(const t_graph_edges& edges)
{
    for (const t_graph_edge& edge : edges)
    {
        std::cout << "edge { from_id: " << edge._from_id
                  << ", to_id: " << edge._to_id
                  << ", weight: " << edge._weight
                  << " }"
                  << std::endl;
    }
}

struct t_finding_vertex_by_id
{
public:
    t_finding_vertex_by_id(const t_vertex_id vertex_id)
        : _vertex_id { vertex_id }
    {
    }

    bool operator()(const t_graph_vertex& vertex)
    {
        return _vertex_id == vertex._id;
    };

public:
    const t_vertex_id _vertex_id;
};

void print(const t_graph_vertex& vertex)
{
    std::cout << "id: " << vertex._id
              << " x: " << vertex._position._x
              << " y: " << vertex._position._y
              << std::endl;
}

struct t_finding_edge_by_vertex_id
{
public:
    t_finding_edge_by_vertex_id(const t_vertex_id vertex_id)
        : _vertex_id { vertex_id }
    {
    }

    bool operator()(const t_graph_edge& edge) const
    {
        return edge._from_id == _vertex_id || edge._to_id == _vertex_id;
    }

public:
    const t_vertex_id _vertex_id;
};

}


t_graph_weighted::t_graph_weighted(const size_t w, const size_t h)
    : _size { w, h }
{
    const size_t amount = area();

    _verteces.reserve(amount);

    const size_t quad_amount { 4 * amount };

    _edges.reserve(quad_amount);
}


void t_graph_weighted::create_vertex(const t_vertex_id vertex_id, int x, int y)
{
    _verteces.emplace_back(vertex_id, x, y);
}

void t_graph_weighted::destroy_verteces(const std::vector<t_vertex_id>& vertex_ids)
{
}


void t_graph_weighted::create_edge(const t_vertex_id from_id, const t_vertex_id to_id, const t_graph_edge_weight weight)
{
    const t_edge_id edge_id = _edge_id_generator.get_value_and_generate_next();

    _edges.emplace_back(edge_id, from_id, to_id, weight);

    t_graph_vertex& vertex = _verteces[from_id];

    if (vertex._id != from_id)
    {
        throw std::runtime_error { " from vertex's id is not equeal with from_id" };
    }

    vertex.link_edge_id(edge_id);
}

void t_graph_weighted::destroy_edge(const t_vertex_id from_id, const t_vertex_id to_id)
{
    // if (std::find(_verteces.begin(), _verteces.end(), from_id) == _verteces.end())
    // {
    //     throw std::runtime_error { "destroy_edge: from_id { " + std::to_string(from_id) + " } does not exist" };
    // }

    // if (std::find(_verteces.begin(), _verteces.end(), to_id) == _verteces.end())
    // {
    //     throw std::runtime_error { "destroy_edge: to_id { " + std::to_string(to_id) + " } does not exist" };
    // }

    t_graph_vertex& vertex = _verteces[from_id];

    if (vertex._id != from_id)
    {
        throw std::runtime_error { "destroy_edge: vertex id { " + std::to_string(vertex._id) + " } is not equal with id {" + std::to_string(from_id) + " }" };
    }
    
    vertex.unlink_vertex_id(to_id);
}


const bool t_graph_weighted::does_exist(const t_vertex_id vertex_id) const
{
    const t_graph_vertex& vertex = _verteces[vertex_id];

    return vertex._id == vertex_id;
}

void t_graph_weighted::validate(const t_vertex_id vertex_id) const
{
    // for (const t_vertex& vertex : _verteces)
    // {
    //     for (const t_vertex_id& linked_vertex_id : vertex.get_linked_vertex_ids())
    //     {
    //         if (vertex_id == linked_vertex_id)
    //         {
    //             std::cerr << "vertex_id: " << vertex_id << ", vertex " << vertex._id << ", x: " << vertex._x << ", y: " << vertex._y << ", linked with: ";

    //             for (const t_vertex_id& linked_vertex_id : vertex.get_linked_vertex_ids())
    //             {
    //                 std::cerr << linked_vertex_id << ", ";
    //             }
    //             std::cerr << std::endl;

    //             // throw std::runtime_error { "linked id is equal with vertex id" };
    //         }
    //     }
    // }
}
