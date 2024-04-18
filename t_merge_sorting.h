#ifndef T_MERGE_SORTING_H
#define T_MERGE_SORTING_H

#include <iostream>
#include <vector>

template<typename t_value>
void t_implementation_merge_sorting(std::vector<t_value>& values, std::vector<t_value>& temporary, size_t since, size_t till) {
    if (since >= till) {
        return;
    }

    const size_t middle = (since + till) / 2;

    t_implementation_merge_sorting(values, temporary, since, middle);
    t_implementation_merge_sorting(values, temporary, middle + 1, till);

    int index = since;
    for (int lhs_index = since, rhs_index = middle + 1; lhs_index <= middle || rhs_index <= till;) {

        if (rhs_index > till || (lhs_index <= middle && values[lhs_index] < values[rhs_index])) {
            temporary[index] = values[lhs_index];
            ++lhs_index;
        }
        else {
            temporary[index] = values[rhs_index];
            ++rhs_index;
        }

        ++index;
    }

    for (int index = since; index <= till; ++index) {
        values[index] = temporary[index];
    }
}

template<typename t_value>
void t_merge_sort(std::vector<t_value>& values) {
    if (values.empty()) {
        return;
    }

    std::vector<t_value> temporary(values.size());
    t_implementation_merge_sorting(values, temporary, {}, values.size() - 1);
}

void print(std::vector<int>& values);

#endif // T_MERGE_SORTING_H
