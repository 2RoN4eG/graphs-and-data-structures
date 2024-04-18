#include <iostream>

#include "t_graph.h"
#include "t_value.h"
#include "t_dfs.h"
#include "t_bfs.h"
#include "t_merge_sorting.h"
#include "t_a_star.h"


using namespace std;

void test_graph()
{
    t_graph graph;
    t_value_generator<t_vertex_id> generator;
    
    const t_vertex_id vertex_1_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_2_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_3_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_4_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_5_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_6_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_7_id = graph.create_vertex(generator.get_value_and_generate_next());

    graph.link_vertex_with(vertex_1_id, vertex_2_id);
    graph.link_vertex_with(vertex_1_id, vertex_3_id);
    graph.link_vertex_with(vertex_1_id, vertex_4_id);
    graph.link_vertex_with(vertex_1_id, vertex_5_id);

    graph.link_vertex_with(vertex_2_id, vertex_1_id);
    graph.link_vertex_with(vertex_2_id, vertex_4_id);
    graph.link_vertex_with(vertex_2_id, vertex_5_id);

    graph.link_vertex_with(vertex_3_id, vertex_1_id);
    graph.link_vertex_with(vertex_3_id, vertex_6_id);
    graph.link_vertex_with(vertex_3_id, vertex_7_id);

    graph.link_vertex_with(vertex_4_id, vertex_1_id);
    graph.link_vertex_with(vertex_4_id, vertex_2_id);
    graph.link_vertex_with(vertex_4_id, vertex_5_id);

    graph.link_vertex_with(vertex_5_id, vertex_1_id);
    graph.link_vertex_with(vertex_5_id, vertex_2_id);
    graph.link_vertex_with(vertex_5_id, vertex_4_id);

    graph.link_vertex_with(vertex_6_id, vertex_3_id);
    graph.link_vertex_with(vertex_6_id, vertex_7_id);

    graph.link_vertex_with(vertex_7_id, vertex_3_id);
    graph.link_vertex_with(vertex_7_id, vertex_6_id);

    graph.print_info();

    ////////////////////////////////////////////////////////////////////////////////
    /// DFS
    ////////////////////////////////////////////////////////////////////////////////

    t_dfs dfs;

    {
        try {
            dfs(graph, vertex_1_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            dfs(graph, vertex_2_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            dfs(graph, vertex_3_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            dfs(graph, vertex_4_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            dfs(graph, vertex_5_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            dfs(graph, vertex_6_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            dfs(graph, vertex_7_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////
    /// BFS
    ////////////////////////////////////////////////////////////////////////////////

    t_bfs bfs;

    {
        try {
            bfs(graph, vertex_1_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            bfs(graph, vertex_2_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            bfs(graph, vertex_3_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            bfs(graph, vertex_4_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            bfs(graph, vertex_5_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            bfs(graph, vertex_6_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }

    {
        try {
            bfs(graph, vertex_7_id);
        }
        catch (const std::exception& exception) {
            std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
        }
    }
}

void test_graph_second()
{
    //          [ 1 ]
    //         /     \
    //        / 2     \ 8
    //       /         \
    //    [ 2 ]       [ 3 ]
    //    /   \       /   \
    // [ 4 ] [ 5 ] [ 6 ] [ 7 ]
    //   |
    // [ 8 ]

    t_graph graph;
    t_value_generator<t_vertex_id> generator;
    
    const t_vertex_id vertex_1_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_2_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_3_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_4_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_5_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_6_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_7_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_8_id = graph.create_vertex(generator.get_value_and_generate_next());

    graph.link_vertex_with(vertex_1_id, vertex_2_id);
    graph.link_vertex_with(vertex_1_id, vertex_3_id);

    graph.link_vertex_with(vertex_2_id, vertex_1_id);
    graph.link_vertex_with(vertex_2_id, vertex_4_id);
    graph.link_vertex_with(vertex_2_id, vertex_5_id);

    graph.link_vertex_with(vertex_3_id, vertex_1_id);
    graph.link_vertex_with(vertex_3_id, vertex_6_id);
    graph.link_vertex_with(vertex_3_id, vertex_7_id);

    graph.link_vertex_with(vertex_4_id, vertex_2_id);
    graph.link_vertex_with(vertex_4_id, vertex_8_id);

    graph.link_vertex_with(vertex_5_id, vertex_2_id);

    graph.link_vertex_with(vertex_6_id, vertex_3_id);

    graph.link_vertex_with(vertex_7_id, vertex_3_id);

    graph.link_vertex_with(vertex_8_id, vertex_4_id);

    graph.print_info();

    ////////////////////////////////////////////////////////////////////////////////
    /// DFS
    ////////////////////////////////////////////////////////////////////////////////

    t_dfs dfs;

    try {
        dfs(graph, vertex_1_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_2_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_3_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_4_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_5_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_6_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_7_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_8_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////////
    /// BFS
    ////////////////////////////////////////////////////////////////////////////////

    t_bfs bfs;

    try {
        bfs(graph, vertex_1_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_2_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_3_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_4_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_5_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_6_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_7_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_8_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }
}

template <size_t amount_of_verteces>
struct stack_item {
    
    t_vertex_id _vertex_id {};
    
    t_graph_edge_weight _weight {};

    std::array<bool, amount_of_verteces> _verteces;
};

void test_graph_third()
{
    //          [ 1 ]
    //         /     \
    //      4 /     8 \
    //       /         \
    //    [ 2 ]       [ 3 ]
    //  1 / 6 \     7 / 1 \
    // [ 4 ] [ 5 ] [ 6 ] [ 7 ]
    //    \               /
    //     \             /
    //      \           /
    //     3 \       2 /
    //        \       /
    //         \     /
    //          \   /
    //          [ 8 ]

    // Берем вершину 1, помечаем ее как посещенную { 1, 0, 0, 0, 0, 0, 0, 0 } и пути { 2, 3 } заносим в стек считая цену посещения каждой вершины { 2 -> 0 + 4 = 4, 7 -> 0 + 8 = 8 }
    // В стеке вершины { { 2, 4 }, { 3, 8 } } и массив посещений { 1, 0, 0, 0, 0, 0, 0, 0 }

    // Берем вершину 3 из стека и помечаем массив посещенных вершин { 1, 0, 1, 0, 0, 0, 0, 0 } и пути { 6, 7 } заносим в стек считая цену посещения каждой вершины { 6 -> 8 + 7 = 15, 7 -> 8 + 1 = 9 }
    // В стеке вершины { { 2, 4 }, { 6, 15 }, { 7, 9 } } и массив посещений { 1, 0, 1, 0, 0, 0, 0, 0 }

    // Берем вершину 7 из стека и помечаем массив посещенных вершин { 1, 0, 1, 0, 0, 0, 1, 0 } и пути { 8 } заносим в стек считая цену посещения каждой вершины { 8 -> 11 }
    // В стеке вершины { { 2, 4 }, { 6, 15 }, { 8, 11 } } и массив посещений { 1, 0, 1, 0, 0, 0, 1, 0 }

    // В данном случае мы достигли вершины назначения 8 выходя из вершины 1, сверяем значение пути с минимальным, и обновляем состояние посещений и цену посещения

    // Берем вершину 6 из стека и помечаем массив посещенных вершин { 1, 0, 1, 0, 0, 1, 1, 0 } и пути {} заносим в стек считая цену посещения каждой вершины {}
    // В стеке вершины { { 2, 4 } } и массив посещений { 1, 0, 0, 0, 0, 0, 0, 0 }

    // Берем вершину 2 из стека и помечаем массив посещенных вершин { 1, 1, 0, 0, 0, 0, 0, 0 } и пути { 4, 5 } заносим в стек считая цену посещения каждой вершины { 4 -> 4 + 1 = 5, 4 + 6 = 10 }
    // В стеке вершины { { 4, 5 }, { 5, 10 } } и массив посещений { 1, 1, 0, 0, 0, 0, 0, 0 }

    // Для вершины 5 будет спаведливо действия как и для верщины 6
    // В стеке вершины { { 4, 5 } } и массив посещений { 1, 1, 0, 0, 0, 0, 0, 0 }

    // Берем вершину 4 из стека и помечаем массив посещенных вершин { 1, 1, 0, 1, 0, 0, 0, 0 } и пути { 8 } заносим в стек считая цену посещения каждой вершины { 4 -> 5 + 3 = 8 }
    // В стеке вершины { { 8, 8 } } и массив посещений { 1, 1, 0, 1, 0, 0, 0, 0 }

    // Тут можно вывести несколько реализаций:
    // 1. Стоимость посещений можно складываеть в массив тем самым наглядно демонстрировать как мы двигаемся
    // 2. Ввести дополнительный массив с индексами движения до точки назначения

    //          [ 1 ]
    //         /     \
    //      4 /     8 \
    //       /         \
    //    [ 2 ]       [ 3 ]
    //  1 / 6 \     7 / 1 \
    // [ 4 ] [ 5 ] [ 6 ] [ 7 ]
    //    \   1 \ 1 /     /
    //     \    [ 9 ]    /
    //      \     |     /
    //     3 \  1 |  2 /
    //        \   |   /
    //         \  |  /
    //          \ | /
    //          [ 8 ]

    // * 9ая вершина была добавлена после написания алгоритма { 8, 12, 17, 11 }

    // while (_stack.size()) {
    //     if (t_vertex {}.get_linked_vertex_ids().empty()) {
    //         // do nothing
    //         continue;
    //     }
    //
    //     if () {
    //     }
    // }

    t_graph graph;
    t_value_generator<t_vertex_id> generator;
    
    const t_vertex_id vertex_1_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_2_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_3_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_4_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_5_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_6_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_7_id = graph.create_vertex(generator.get_value_and_generate_next());
    const t_vertex_id vertex_8_id = graph.create_vertex(generator.get_value_and_generate_next());

    graph.link_vertex_with(vertex_1_id, vertex_2_id);
    graph.link_vertex_with(vertex_1_id, vertex_3_id);

    graph.link_vertex_with(vertex_2_id, vertex_1_id);
    graph.link_vertex_with(vertex_2_id, vertex_4_id);
    graph.link_vertex_with(vertex_2_id, vertex_5_id);

    graph.link_vertex_with(vertex_3_id, vertex_1_id);
    graph.link_vertex_with(vertex_3_id, vertex_6_id);
    graph.link_vertex_with(vertex_3_id, vertex_7_id);

    graph.link_vertex_with(vertex_4_id, vertex_2_id);
    graph.link_vertex_with(vertex_4_id, vertex_8_id);

    graph.link_vertex_with(vertex_5_id, vertex_2_id);

    graph.link_vertex_with(vertex_6_id, vertex_3_id);

    graph.link_vertex_with(vertex_7_id, vertex_3_id);
    graph.link_vertex_with(vertex_7_id, vertex_8_id);

    graph.link_vertex_with(vertex_8_id, vertex_4_id);
    graph.link_vertex_with(vertex_8_id, vertex_7_id);

    graph.print_info();

    ////////////////////////////////////////////////////////////////////////////////
    /// DFS
    ////////////////////////////////////////////////////////////////////////////////

    t_dfs dfs;

    try {
        dfs(graph, vertex_1_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_2_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_3_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_4_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_5_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_6_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_7_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        dfs(graph, vertex_8_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "dfs exception's what is: " << exception.what() << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////////
    /// BFS
    ////////////////////////////////////////////////////////////////////////////////

    t_bfs bfs;

    try {
        bfs(graph, vertex_1_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_2_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_3_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_4_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_5_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_6_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_7_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }

    try {
        bfs(graph, vertex_8_id);
    }
    catch (const std::exception& exception) {
        std::cerr << "bfs exception's what is: " << exception.what() << std::endl;
    }
}

void test_a_star() {
    t_graph_weighted graph = make_2d_weighted_graph(6, 5);

    t_a_star a_star {};
    try {
        a_star(graph, t_vertex_id { 0 }, t_vertex_id { 28 });
    }
    catch (const std::exception& exception) {
        std::cerr << "a_star exception's what is: " << exception.what() << std::endl;
    }
}

void test_a_star_10x10() {
    t_graph_weighted graph = make_2d_halled_graph_10_x_10();

    t_a_star a_star {};
    try {
        a_star(graph, t_vertex_id { 0 }, t_vertex_id { 77 });
    }
    catch (const std::exception& exception) {
        std::cerr << "a_star exception's what is: " << exception.what() << std::endl;
    }
}

void test_a_star_20x20() {
    t_graph_weighted graph = make_2d_weighted_graph(20, 20);

    t_a_star a_star {};
    try {
        a_star(graph, t_vertex_id { 0 }, t_vertex_id { 399 });
    }
    catch (const std::exception& exception) {
        std::cerr << "a_star exception's what is: " << exception.what() << std::endl;
    }
}


void test_a_star_random(size_t width, size_t height, size_t percent)
{
    t_graph_weighted graph = make_2d_weighted_graph(width, height);

    t_graph_vertex_ids to_destroy {};
    for (size_t _ {}; _ < (width * height * percent / 100); ++ _) {
        const t_vertex_id generated_id = std::rand() % (width * height - 1);

        if (generated_id == 0) {
            continue;
        }

        if (generated_id == graph.area() - 1) {
            continue;
        }
        
        to_destroy.emplace_back(t_vertex_id { generated_id });
    }
    graph.destroy_verteces(to_destroy);

    t_a_star a_star {};

    try {
        a_star(graph, t_vertex_id { 0 }, t_vertex_id (width * height - 1));
    }
    catch (const std::exception& exception) {
        std::cerr << "a_star exception's what is: " << exception.what() << std::endl;
    }
}

int main()
{
    test_graph();
    test_graph_second();
    test_a_star();
    test_a_star_10x10();
    test_a_star_20x20();

    test_a_star_random(100,       100, 30);
    test_a_star_random(10,       1000, 30);
    test_a_star_random(1000,       10, 30);
    test_a_star_random(1000,     1000, 30);
    test_a_star_random(5000,     5000, 30);
    test_a_star_random(10000,   10000, 30);
    test_a_star_random(15000,   15000, 30);
    test_a_star_random(25000,   25000, 30);

    ////////////////////////////////////////////////////////////////////////////////
    /// merge sorting
    ////////////////////////////////////////////////////////////////////////////////

    using t_array = std::vector<int>;
    t_array array { 4, 2, 7, 1, 0 };

    t_merge_sort(array);
    print(array);

    cout << "Hello World!" << endl;
    return 0;
}
