#include "classes.h"

s_max_comp::s_max_comp(f_comp_table &_f_comp_table)
{
    int32_t **f_table = _f_comp_table.get_table();
    uint32_t state_count = _f_comp_table.get_table_size();

    for (uint32_t i = 0; i < state_count; i++) {
        for (uint32_t j = 0; j < state_count; j++) {
            printf("%2d ", f_table[i][j]);
        }
        printf("\r\n");
    }

    this->max_classes.push_back(std::vector<int32_t>());
    this->max_classes[0].push_back(state_count);

    std::vector<int32_t> tmp;

    for (uint32_t i = 1; i < state_count; i++) {
        for (uint32_t j = state_count - i; j < state_count; j++) {
            if (f_table[j][state_count - 1 - i]) {
                tmp.push_back(j + 1);
            }
        }
        tmp.clear();
    }
}
