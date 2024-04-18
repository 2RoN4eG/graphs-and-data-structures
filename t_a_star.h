#ifndef T_A_ASTERIX_H
#define T_A_ASTERIX_H

#include "t_weighted_graph.h"


class t_a_star
{
public:
    t_a_star();
    
    void operator()(const t_graph_weighted& graph, const t_vertex_id from, const t_vertex_id to);
    
    std::vector<t_vertex_id> get_way() const;
};

t_graph_weighted make_2d_weighted_graph(t_width width, t_height height);

t_graph_weighted make_2d_halled_graph_10_x_10();

#endif // T_A_ASTERIX_H
