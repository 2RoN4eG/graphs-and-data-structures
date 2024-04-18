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
                  << " } linked with " << vertex.get_linked_vertex_ids().size()
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
    const size_t verteces = area();

    _verteces.reserve(verteces);

    // _edges.resize(verteces * 4, {});
}

size_t t_graph_weighted::verteces() const { return _verteces.size(); }

size_t t_graph_weighted::edges() const { return _edges.size(); }

size_t t_graph_weighted::area() const { return _size._width * _size._height; }


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

    vertex.register_edge_id(edge_id);
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

    vertex.unlink_with(to_id);
}

// const t_graph_edge_weight t_graph_weighted::get_weight_by_from_to_ids(const t_vertex_id from_id, const t_vertex_id to_id) const
// {
//     // auto finding_from_to_predicate = [&from_id, &to_id](const t_graph_edge& edge)
//     // {
//     //     return edge._from_id == from_id && edge._to_id == to_id;
//     // };

//     // if (t_graph_edges::iterator iterator = std::find_if(_edges.begin(), _edges.end(), finding_from_to_predicate); iterator != _edges.end())
//     // {
//     //     return iterator->_weight;
//     // }

//     // throw std::runtime_error { "get_weight_by_from_to_ids: edge { from_id: " + std::to_string(from_id) + ", to_id: " + std::to_string(to_id) + " } does not exist" };

//     throw std::runtime_error { "" };
// }

const t_graph_edge_weight t_graph_weighted::get_weight_by_edge_id(const t_edge_id edge_id) const
{
    const t_graph_edge& edge = _edges[edge_id];

    if (edge._id != edge_id)
    {
        throw std::runtime_error { "destroy_edge: vertex id { " + std::to_string(edge._id) + " } is not equal with id {" + std::to_string(edge_id) + " }" };
    }

    return edge._weight;
}


// const t_graph_vertex_ids& t_graph_weighted::get_linked_vertex_ids(const t_vertex_id vertex_id) const
// {
//     const t_graph_vertex& vertex = _verteces[vertex_id];

//     if (vertex._id != vertex_id)
//     {
//         throw std::runtime_error { "get_linked_vertex_ids: vertex id { " + std::to_string(vertex._id) + " } is not equal with " + std::to_string(vertex_id) };
//     }

//     t_graph_vertex_ids linked_with_ids = vertex.get_linked_vertex_ids();

//     return linked_with_ids;
// }

const bool t_graph_weighted::does_exist(const t_vertex_id vertex_id) const
{
    return std::find_if(_verteces.begin(), _verteces.end(), t_finding_vertex_by_id { vertex_id }) != _verteces.end();
}

void t_graph_weighted::print_info() const
{
    std::cout << "verteces: " << _verteces.size() << " edges: " << _edges.size() << std::endl;
}

void t_graph_weighted::check(const t_vertex_id vertex_id) const
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
