#ifndef T_RB_TREE_H
#define T_RB_TREE_H

#include <vector>

enum t_color
{
    t_red, t_black
};

template <typename t_value>
struct t_rb_node {
    t_color _color;
    t_value _value {};

    t_rb_node<t_value>* _lhs {};
    t_rb_node<t_value>* _rhs {};

public:
    t_rb_node()
        : _color { t_color::t_black }
        , _value {}
        , _lhs {}
        , _rhs {}
    {
    }

    t_rb_node(const t_color color, const t_value& value, t_rb_node<t_value>& none)
        : _color { color }
        , _lhs { &none }
        , _rhs { &none }
    {
    }

    t_rb_node(const t_value& value, t_rb_node<t_value>& none)
        : _color { t_color::t_red }
        , _value { value }
        , _lhs { &none }
        , _rhs { &none }
    {
    }
};

template <typename t_value>
class t_rb_tree
{
public:
    t_rb_tree()
    {
        _nodes.reserve(8);
    }

    t_rb_node<t_value>& find_inserting_place() {
    }

    bool emplace(const t_value& value) {
        if (!_root) {
            _root = &*_nodes.emplace(value, _none);
        }

        find_inserting_place();
    }

private:
    t_rb_node<t_value> _none;

    std::vector<t_rb_node<t_value>> _nodes;

    t_rb_node<t_value>* _root {};
};

#endif // T_RB_TREE_H
