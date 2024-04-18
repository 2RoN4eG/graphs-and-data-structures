#include "t_graph_vertex.h"

#include <iostream>

t_graph_vertex::t_graph_vertex()
    : t_graph_vertex { {}, {}, {} }
{
}

t_graph_vertex::t_graph_vertex(const t_vertex_id& id)
    : t_graph_vertex { id, {}, {} }
{
}

t_graph_vertex::t_graph_vertex(const t_vertex_id& id, const t_axis x, const t_axis y)
    : _id { id }
    , _position { x, y }
{
}

void t_graph_vertex::link_with(const t_vertex_id vertex_id)
{
    _linked_vertex_ids.emplace_back(vertex_id);

    std::sort(_linked_vertex_ids.begin(), _linked_vertex_ids.end());
}

void t_graph_vertex::unlink_with(const t_vertex_id& vertex_id)
{
    std::cerr << "unlink vertex { id: " << _id << ", linked: " << _linked_vertex_ids.size() << " } with vertex { id: " << vertex_id << " }" << std::endl;
    
    auto finding_linked_vertex_id_predicate = [&vertex_id](const t_graph_vertex& vertex)
    {
        return vertex._id == vertex_id;
    };

    if (auto it = std::ranges::find_if(_linked_vertex_ids, finding_linked_vertex_id_predicate); it != _linked_vertex_ids.end())
    {
        _linked_vertex_ids.erase(it);

        return;
    }

    throw std::runtime_error { "vertex { " + std::to_string(_id) + " } is not linked with vertex { id: " + std::to_string(vertex_id) + " }" };

    // std::cerr << "id: " << _id << " linked with " << _linked_vertex_ids.size() << " verteces" << std::endl;
}

void t_graph_vertex::clear_linked_ids()
{
    _linked_vertex_ids.clear();
}

void t_graph_vertex::register_edge_id(const t_edge_id edge_id)
{
    _edge_ids.emplace_back(edge_id);
}

const t_graph_vertex_ids& t_graph_vertex::get_linked_vertex_ids() const
{
    return _linked_vertex_ids;
}

const size_t t_graph_vertex::get_linked_vertex_size() const
{
    return _linked_vertex_ids.size();
}
