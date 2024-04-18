#ifndef T_DEFINES_H
#define T_DEFINES_H

#include <_types.h>
#include <vector>

using t_width                   = u_int32_t;
using t_height                  = u_int32_t;
using t_depth                   = u_int32_t;

using t_vertex_id         = u_int32_t;
using t_graph_vertex_ids        = std::vector<t_vertex_id>;

using t_axis                    = int32_t;

using t_edge_id           = u_int32_t;
using t_graph_edge_ids          = std::vector<t_vertex_id>;

using t_graph_edge_weight       = size_t;

using t_heuristic_value         = u_int32_t;

#endif // T_DEFINES_H
