#include "t_a_star.h"

#include "t_weighted_graph.h"
#include "t_value.h"
#include "t_defines.h"

#include <queue>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

void print_graph(const t_graph_weighted& graph, const std::vector<size_t>& are_visited, const std::vector<t_vertex_id>& road);

void print_processed_currents(const t_graph_weighted& graph, const std::vector<size_t>& are_visited);

void print_processed_nexts(const t_graph_weighted& graph, const std::vector<size_t>& are_visited);

void print_visited_costs(const t_graph_weighted& graph, const std::vector<t_graph_edge_weight>& visiting_costs);

void print_visited_distances(const t_graph_weighted& graph, const std::vector<t_heuristic_value>& visiting_costs);

namespace
{
t_heuristic_value minimum_axis_distance(const t_graph_weighted& graph, const t_vertex_id from_id, const t_vertex_id to_id)
{
    const t_graph_vertex& from = graph.get_vertex(from_id);
    const t_graph_vertex& to = graph.get_vertex(to_id);

    return std::min( std::abs(from._position._x - to._position._x), std::abs(from._position._y - to._position._y) );
}

t_heuristic_value maximum_axis_distance(const t_graph_weighted& graph, const t_vertex_id from_id, const t_vertex_id to_id)
{
    const t_graph_vertex& from = graph.get_vertex(from_id);
    const t_graph_vertex& to = graph.get_vertex(to_id);

    return std::max( std::abs(from._position._x - to._position._x), std::abs(from._position._y - to._position._y) );
}

t_heuristic_value manhattan_distance(const t_graph_weighted& graph, const t_vertex_id from_id, const t_vertex_id to_id)
{
    const t_graph_vertex& from = graph.get_vertex(from_id);
    const t_graph_vertex& to = graph.get_vertex(to_id);

    return std::abs(from._position._x - to._position._x) + std::abs(from._position._y - to._position._y);
}

t_heuristic_value real_distance(const t_graph_weighted& graph, const t_vertex_id from_id, const t_vertex_id to_id)
{
    const t_graph_vertex& from = graph.get_vertex(from_id);
    const t_graph_vertex& to = graph.get_vertex(to_id);

    return std::sqrtf( std::powf(from._position._x - to._position._x, 2) + std::powf(from._position._y - to._position._y, 2) );
}

t_heuristic_value heuristic(const t_graph_weighted& graph, const t_vertex_id from_id, const t_vertex_id to_id)
{
    return manhattan_distance(graph, from_id, to_id);
}

struct t_vertex_id_distance_cost
{
public:
    t_vertex_id_distance_cost(const t_vertex_id vertex_id, const t_heuristic_value distance, const t_heuristic_value cost)
        : _vertex_id { vertex_id }
        , _distance { distance }
        , _cost { cost }
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, const t_vertex_id_distance_cost& to_vertex)
    {
        stream << to_vertex._vertex_id << " distance " << to_vertex._distance << " cost " << to_vertex._cost;
        return stream;
    }

public:
    t_vertex_id _vertex_id {};

    // priority { _distance + _cost }

    t_heuristic_value _distance {};

    t_heuristic_value _cost {};
};

struct t_distance_and_cost_comparator
{
    bool operator()(const t_vertex_id_distance_cost& lhs, const t_vertex_id_distance_cost& rhs) const
    {
        if (lhs._distance == rhs._distance)
        {
            return lhs._cost > rhs._cost;
        }

        return lhs._distance > rhs._distance;
    }
};

struct t_maximum_distance_cost
{
    bool operator()(const t_vertex_id_distance_cost& lhs, const t_vertex_id_distance_cost& rhs) const
    {
        if (lhs._distance == rhs._distance)
        {
            return lhs._cost > rhs._cost;
        }

        return lhs._distance > rhs._distance;
    }
};

struct t_distance_and_cost_hash
{
    std::size_t operator()(const t_vertex_id_distance_cost& distance_and_cost) const
    {
        return distance_and_cost._vertex_id;
    }
};

// Custom equality function for Points
struct t_distance_and_cost_equal
{
    bool operator()(const t_vertex_id_distance_cost& lhs, const t_vertex_id_distance_cost& rhs) const
    {
        return lhs._vertex_id == rhs._vertex_id;
    }
};

struct t_finding_vertex_predicate
{
    t_finding_vertex_predicate(const t_vertex_id& vertex_id)
        : _vertex_id { vertex_id }
    {
    }

    bool operator()(const t_vertex_id_distance_cost& distance_and_cost)
    {
        return _vertex_id == distance_and_cost._vertex_id;
    };

    bool operator()(const t_vertex_id& vertex_id)
    {
        return _vertex_id == vertex_id;
    };

    t_vertex_id _vertex_id;
};

class t_priority_queue
    : public std::priority_queue<t_vertex_id_distance_cost, std::vector<t_vertex_id_distance_cost>, t_maximum_distance_cost>
{
public:
    t_priority_queue(size_t amount)
        : _contains(amount, {})
    {
        std::cout << "_contains size is " << _contains.size() << std::endl;
    }

    bool does_contain(const t_vertex_id vertex_id) const
    {
        return _contains[vertex_id];
    }

    const t_vertex_id pop()
    {
        const t_vertex_id vertex_id = std::priority_queue<t_vertex_id_distance_cost, std::vector<t_vertex_id_distance_cost>, t_maximum_distance_cost>::top()._vertex_id;

        std::priority_queue<t_vertex_id_distance_cost, std::vector<t_vertex_id_distance_cost>, t_maximum_distance_cost>::pop();

        _contains[vertex_id] = {};

        return vertex_id;
    }

    void push(const t_vertex_id vertex_id, const t_heuristic_value distance, const t_heuristic_value cost)
    {
        std::priority_queue<t_vertex_id_distance_cost, std::vector<t_vertex_id_distance_cost>, t_maximum_distance_cost>::emplace(vertex_id, distance, cost);

        _contains[vertex_id] = true;
    }

private:
    std::vector<bool> _contains {};
};

size_t get_edge_amount(size_t w, size_t h) {
    return (w - 2) * (h - 2) * 4 +      // Кол-во соседей для четырех переходов
           (w - 2 + h - 2) * 3 * 2 +    // Кол-во соседей для трех переходов
           4 * 2;                       // Кол-во соседей для двух переходов
}

t_graph_weighted make_3d_weighted_graph(const t_width width, const t_height height, const t_depth depth)
{
    // Edge amount:
    // (w - 2) * (h - 2) * (d - 2) * 4 +
    // (w - 2 + h - 2) * 3 * 2 +
    // 4 * 2 * 2

    // std::cout << "edges amount: " << get_edge_amount(10, 10) << std::endl;

    t_graph_weighted graph { width, height };

    t_value_generator<t_vertex_id> vertex_id_generator {};
    for (t_vertex_id z {}; z < depth; ++ z)
    {
        for (t_vertex_id y {}; y < height; ++ y)
        {
            for (size_t x {}; x < width; ++ x)
            {
                const t_vertex_id vertex_id = vertex_id_generator.get_value_and_generate_next();

                graph.create_vertex(vertex_id, x, y);
            }
        }
    }

    for (t_vertex_id z {}; z < depth; ++ z)
    {
        for (t_vertex_id y {}; y < height; ++ y)
        {
            for (t_vertex_id x {}; x < width; ++ x)
            {
                const t_vertex_id from_id { (x + y * width) * z };

                std::cout << "from_id " << from_id << std::endl;

                // if (x) {
                //     graph.create_edge(from_id, x - 1 + (y * width), 1);
                // }

                // if (x != width - 1) {
                //     graph.create_edge(from_id, x + 1 + (y * width), 1);
                // }

                // if (y) {
                //     graph.create_edge(from_id, x + (y - 1) * width, 1);
                // }

                // if (y != height - 1) {
                //     graph.create_edge(from_id, x + (y + 1) * width, 1);
                // }

                // if (z) {
                //     graph.create_edge(from_id, x - 1 + (y * width) * z, 1);
                // }

                // if (z != depth - 1) {
                //     graph.create_edge(from_id, (x + (y + 1) * width) * z, 1);
                // }
            }
        }
    }

    graph.destroy_verteces({});

    return graph;
}

struct t_context
{
};
}

// left  : [ x - 1 + w * y   ] => (x - 1, y) => 1 + 1 * 6 - 1   =>  6
// right : [ x + 1 + w * y   ] => (x + 1, y) => 1 + 1 * 6 + 1   =>  8

// top   : [ x + w * (y - 1) ] => (x, x - 1) => 1 + (1 - 1) * 6 =>  1
// bottom: [ x + w * (y + 1) ] => (x, x + 1) => 1 + (1 + 1) * 6 => 13

// Size: 6 x 5

// [  0 ] [  1 ] [  2 ] [  3 ] [  4 ] [  5 ]
// [  6 ] [  7 ] [  8 ] [  9 ] [ 10 ] [ 11 ]
// [ 12 ] [ 13 ] [ 14 ] [ 15 ] [ 16 ] [ 17 ]
// [ 18 ] [ 19 ] [ 20 ] [ 21 ] [ 22 ] [ 23 ]
// [ 24 ] [ 25 ] [ 26 ] [ 27 ] [ 28 ] [ 29 ]

// [7] left  : 6

// [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ]
// [ 0 ] [ 1 ] [ 2 ] [ 3 ] [ 4 ] [ 5 ]

t_a_star::t_a_star() {}

void t_a_star::operator()(const t_graph_weighted& graph, const t_vertex_id from_id, const t_vertex_id to_id)
{
    t_priority_queue                    frontier { graph.area() };

    std::vector<size_t>                 debug_processed_nexts        (graph.area(), {});
    std::vector<size_t>                 debug_processed_currents     (graph.area(), {});
    std::vector<t_graph_edge_weight>    visited_costs                (graph.area(), std::numeric_limits<t_graph_edge_weight>::max());
    std::vector<t_heuristic_value>      debug_visited_distances      (graph.area(), {});
    std::vector<t_heuristic_value>      debug_merged_distances_costs (graph.area(), {});
    std::vector<t_vertex_id>            visited_froms                (graph.area(), t_vertex_id {});

    size_t debug_popped_verteces_amount   {};
    size_t debug_pushed_verteces_amount   {};
    size_t debug_skipped_cost_is_greater  {};
    size_t debug_skipped_already_in_queue {};
    size_t debug_weight_requested_times   {};
    size_t debug_calculated_cost_times    {};

    frontier.push(from_id, size_t {}, size_t {});

    visited_costs [from_id] = {};
    visited_froms [from_id] = from_id;

    const auto begin = std::chrono::high_resolution_clock::now();

    while (!frontier.empty())
    {
        const t_vertex_id vertex_id = frontier.pop();

        ++ debug_popped_verteces_amount;

        // times for debug purpose
        ++ debug_processed_currents[vertex_id];

        if (vertex_id == to_id)
        {
            break;
        }

        for (const t_edge_id edge_id : graph.get_edge_ids_by_from_id(vertex_id))
        {
            const t_graph_edge_weight weight = graph.get_weight_by_edge_id(edge_id);

            ++ debug_weight_requested_times;

            const t_graph_edge_weight cost = visited_costs[vertex_id] + weight;

            ++ debug_calculated_cost_times;

            const t_vertex_id next_id = graph.get_next_vertex_id(edge_id);

            // std::cout << "vertex_id: " << vertex_id << ", next_id: " << next_id << ", edge_id: " << edge_id << ", cost: " << cost << ", weight: " << weight << std::endl;

            if (cost >= visited_costs[next_id])
            {
                ++ debug_skipped_cost_is_greater;

                // std::cout << "current_id " << std::setw(2) << current_id
                //           << " cost " << visiting_costs[current_id]
                //           << " came from " << came_from[current_id]
                //           << " skip next_id " << next_id
                //           << " cost " << cost
                //           << " cost to next " << visiting_costs[next_id]
                //           << std::endl;

                continue;
            }

            // this is not really necessary
            if (frontier.does_contain(next_id))
            {
                ++ debug_skipped_already_in_queue;

                // std::cout << "current_id " << std::setw(2) << current_id
                //           << " cost " << visiting_costs[current_id]
                //           << " came from " << came_from[current_id]
                //           << " skip next_id " << next_id
                //           << " cost " << cost
                //           << " cost to next_id " << visiting_costs[next_id]
                //           << " - already exist"
                //           << std::endl;

                continue;
            }

            // times for debug purpose
            ++ debug_processed_nexts[next_id];

            const t_heuristic_value distance = heuristic(graph, vertex_id, to_id);

            frontier.push(next_id, distance, cost);

            ++ debug_pushed_verteces_amount;

            visited_froms[next_id] = vertex_id;

            visited_costs[next_id] = cost;

            debug_visited_distances[next_id] = distance;

            debug_merged_distances_costs[next_id] = distance + cost;
        }
    }

    const auto end = std::chrono::high_resolution_clock::now();

    auto nanos   = std::chrono::duration_cast<std::chrono::nanoseconds>  (end - begin);
    auto micros  = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
    auto millis  = std::chrono::duration_cast<std::chrono::milliseconds> (end - begin);
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>      (end - begin);
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>      (end - begin);

    t_vertex_id vertex_id = to_id;
    std::vector<t_vertex_id> road { vertex_id };
    while (vertex_id != from_id)
    {
        vertex_id = visited_froms[vertex_id];
        // std::cout << "" << vertex_id << " ";
        road.emplace_back(vertex_id);
    }

    // std::cout << "way (size: " << road.size() << "): " << vertex_id << ", path: ";
    // for (const t_vertex_id vertex_id : road)
    // {
    //     std::cout << "" << vertex_id << " ";
    // }
    // std::cout << std::endl;

    // print_processed_currents(graph, debug_processed_currents);
    // print_processed_nexts(graph, debug_processed_nexts);
    // print_visited_costs(graph, visited_costs);
    // print_visited_distances(graph, debug_visited_distances);
    // print_visited_distances(graph, debug_merged_distances_costs);
    // print_graph(graph, debug_processed_currents, road);

    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "debug: graph size (area)         : " << graph.width() << " x " << graph.height() << " ( " << graph.area() << " )" << std::endl;
    std::cout << "debug: pushed verteces           : " << debug_pushed_verteces_amount                  << std::endl;
    std::cout << "debug: popped verteces           : " << debug_popped_verteces_amount                  << std::endl;
    std::cout << "debug: left in queue             : " << frontier.size()                               << std::endl;
    std::cout << "debug: calculated costs          : " << debug_calculated_cost_times                   << std::endl;
    std::cout << std::endl;

    std::cout << "debug: skipped: cost is greater  : " << debug_skipped_cost_is_greater                 << std::endl;
    std::cout << "debug: skipped: already in queue : " << debug_skipped_already_in_queue                << std::endl;
    std::cout << std::endl;

    std::cout << "elapced minutes                  : " << minutes.count() % 60                          << std::endl;
    std::cout << "elapced seconds                  : " << seconds.count() % 60                          << std::endl;
    std::cout << "elapced millis                   : " << millis.count()  % 1000                        << std::endl;
    std::cout << "elapced micros                   : " << micros.count()  % 1000                        << std::endl;
    std::cout << "elapced nanos                    : " << nanos.count()   % 1000                        << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

std::vector<t_vertex_id> t_a_star::get_way() const
{
    return {};
}


void print_visited_costs(const t_graph_weighted& graph, const std::vector<t_graph_edge_weight>& visiting_costs)
{
    const size_t width  = graph.width();
    const size_t height = graph.height();

    std::cout << std::endl;
    std::cout << "visiting costs for graph { " << "width: " << width << " height: " << height << " }" << std::endl;

    for (size_t y {}; y < height; ++ y)
    {
        for (size_t x {}; x < width; ++ x)
        {
            const size_t index { x + y * width };

            t_graph_edge_weight cost = visiting_costs[index];

            if (cost == std::numeric_limits<t_graph_edge_weight>::max())
            {
                std::cout << "[    ]" << " ";
            }
            else
            {
                std::cout << "[ " << std::setw(2) << visiting_costs[index] << " ]" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void print_processed_nexts(const t_graph_weighted& graph, const std::vector<size_t>& are_visited) {
    const size_t width  = graph.width();
    const size_t height = graph.height();

    std::cout << std::endl;
    std::cout << "processed nexts for graph { " << "width: " << width << " height: " << height << " }" << std::endl;

    for (size_t y {}; y < height; ++ y)
    {
        for (size_t x {}; x < width; ++ x)
        {
            const size_t index { x + y * width };

            if (are_visited[index])
            {
                std::cout << "[ " << std::setw(2) << are_visited[index] << " ]" << " ";
            }
            else
            {
                std::cout << "[    ]" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void print_processed_currents(const t_graph_weighted& graph, const std::vector<size_t>& are_visited) {
    const size_t width  = graph.width();
    const size_t height = graph.height();

    std::cout << std::endl;
    std::cout << "processed currents for graph { " << "width: " << width << " height: " << height << " }" << std::endl;

    for (size_t y {}; y < height; ++ y)
    {
        for (size_t x {}; x < width; ++ x)
        {
            const size_t index { x + y * width };

            if (are_visited[index])
            {
                std::cout << "[ " << std::setw(2) << are_visited[index] << " ]" << " ";
            }
            else
            {
                std::cout << "[    ]" << " ";
            }
        }
        std::cout << std::endl;
    }
}

void print_graph(const t_graph_weighted& graph, const std::vector<size_t>& are_visited, const std::vector<t_vertex_id>& road)
{
    // print_are_visited(graph, are_visited);

    const t_width width = graph.width();
    const t_height height = graph.height();

    std::cout << std::endl;
    std::cout << "w: " << width << " h: " << height << std::endl;

    for (t_height y {}; y < height; ++ y)
    {
        for (t_width x {}; x < width; ++ x)
        {
            const t_vertex_id vertex_id { x + y * width };

            const bool is_road_part = (std::ranges::count_if(road, t_finding_vertex_predicate { t_vertex_id { vertex_id } }));

            if (are_visited[vertex_id])
            {
                // std::cout << "[ " << (is_way_part ? "+" : "") << /* << " " << std::setw(4) << (y * w + x) */ << " ]" << " ";
                std::cout << "[ " << (is_road_part ? "+" : " ") << " ]" << " ";
            }
            else if (graph.does_exist(t_vertex_id { vertex_id }))
            {
                std::cout << "  .  " << " ";
            }
            else
            {
                std::cout << "     " << " ";
            }
        }
        std::cout << std::endl;
    }
}

void print_visited_distances(const t_graph_weighted& graph, const std::vector<t_heuristic_value>& are_visited) {
    const size_t width  = graph.width();
    const size_t height = graph.height();

    std::cout << std::endl;
    std::cout << "visited distances for graph { " << "width: " << width << " height: " << height << " }" << std::endl;

    for (size_t y {}; y < height; ++ y)
    {
        for (size_t x {}; x < width; ++ x)
        {
            const size_t index { x + y * width };

            if (are_visited[index])
            {
                std::cout << "[ " << std::setw(2) << are_visited[index] << " ]" << " ";
            }
            else
            {
                std::cout << "[    ]" << " ";
            }
        }
        std::cout << std::endl;
    }
}


t_graph_weighted make_2d_weighted_graph(t_width width, t_height height)
{
    // Edge amount: (w - 2) * (h - 2) * 4 + (w - 2) * 3 * 2 + (h - 2) * 3 * 2 + 4 * 2

    // std::cout << "edges amount: " << get_edge_amount(10, 10) << std::endl;

    t_graph_weighted graph { width, height };

    t_value_generator<t_vertex_id> vertex_id_generator {};

    for (t_vertex_id y {}; y < height; ++ y)
    {
        for (size_t x {}; x < width; ++ x)
        {
            const t_vertex_id vertex_id = vertex_id_generator.get_value_and_generate_next();

            graph.create_vertex(vertex_id, x, y);
        }
    }

    for (t_vertex_id y {}; y < height; ++ y)
    {
        for (t_vertex_id x {}; x < width; ++ x)
        {
            const t_vertex_id from_id { x + y * width };

            if (x)
            {
                graph.create_edge(from_id, x - 1 + (y * width), 1);
            }

            if (x != width - 1)
            {
                graph.create_edge(from_id, x + 1 + (y * width), 1);
            }

            if (y)
            {
                graph.create_edge(from_id, x + (y - 1) * width, 1);
            }

            if (y != height - 1)
            {
                graph.create_edge(from_id, x + (y + 1) * width, 1);
            }
        }
    }

    graph.destroy_verteces({});

    return graph;
}

t_graph_weighted make_2d_halled_graph_10_x_10()
{
    t_graph_weighted graph = make_2d_weighted_graph(t_width { 10 }, t_height { 10 });

    // 0: [  !0 ] [   1 ] [   2 ] [   3 ] [   4 ] [   5 ]         [  07 ] [  08 ] [  09 ]
    // 1: [  10 ] [  11 ] [  12 ] [  13 ] [  14 ] [  15 ]         [  17 ] [  18 ] [  19 ]
    // 2: [  20 ] [  21 ] [  22 ] [  23 ] [  24 ] [  25 ]         [  27 ] [  28 ] [  29 ]
    // 3: [  30 ] [  31 ] [  32 ] [  33 ] [  34 ] [  35 ]         [  37 ] [  38 ] [  39 ]
    // 4: [  40 ] [  41 ] [  42 ] [  43 ] [  44 ] [  45 ]         [  47 ] [  48 ] [  49 ]
    // 5: [  50 ] [  51 ] [  52 ] [  53 ] [  54 ] [  55 ]         [  57 ] [  58 ] [  59 ]
    // 6: [  60 ] [  61 ] [  62 ] [  63 ] [  64 ] [  65 ]         [  67 ] [  68 ] [  69 ]
    // 7: [  70 ] [  71 ] [  72 ] [  73 ] [  74 ] [  75 ]         [ *77 ] [  78 ] [  79 ]
    // 8: [  80 ] [  81 ] [  82 ] [  83 ] [  84 ]                 [  87 ] [  98 ] [  89 ]
    // 9: [  90 ] [  91 ] [  92 ] [  93 ] [  94 ] [  95 ] [  96 ] [  97 ] [  98 ] [  99 ]

    // without wall: 77 67 57 47 37 27 17 7 6 5 4 3 2 1 0
    // with wall   : 77 87 97 96 95 94 84 74 64 54 44 34 33 32 31 21 11 1 0 (steps: )

    graph.destroy_verteces({
                            t_vertex_id { 85 },
                            t_vertex_id {  6 },
                            t_vertex_id { 16 },
                            t_vertex_id { 26 },
                            t_vertex_id { 36 },
                            t_vertex_id { 46 },
                            t_vertex_id { 56 },
                            t_vertex_id { 66 },
                            t_vertex_id { 66 },
                            t_vertex_id { 76 },
                            t_vertex_id { 86 }
    });

    return graph;
}
